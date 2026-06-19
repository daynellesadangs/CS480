/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #2, Experimental Shell
*
* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)
*
* FileName: exec.cpp
***********************************************************************/

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include "xsh.h"

// Convert a vector of C++ strings into the char* array format
static std::vector<char*> makeArgv(const std::vector<std::string>& command){
    std::vector<char*> argv;

    // Add each command word/argument to argv
    for (size_t i = 0; i < command.size(); i++){
        argv.push_back(const_cast<char*>(command[i].c_str()));
    }

    argv.push_back(nullptr);
    return argv;
}

// Execute one command with no pipes
int executeSingleCommand(const std::vector<std::string>& command){
    // Create a child process to run the command
    pid_t pid = fork();

    // fork() returns a negative value if it fails
    if (pid < 0){
        std::cerr << "fork failed" << std::endl;
        return 1;
    }
    // pid == 0 means this code is running in the child proces
    if (pid == 0){
        // Format command
        std::vector<char*> argv = makeArgv(command);

        // Replace the child process with the requested program
        execvp(argv[0], argv.data());

        // execvp() only returns if it fails, and exit the child process with an error code
        std::cerr << "exec failed: " << command[0]
                  << ": " << std::strerror(errno) << std::endl;

        _exit(1);
    }

    // Parent process waits for the child command to finish
    waitpid(pid, nullptr, 0);
    return 0;
}

// Execute multiple commands connected by pipes.
int executePipeCommands(const std::vector<std::vector<std::string> >& commands){
    int numCommands = static_cast<int>(commands.size());

    // Stores all pipe file descriptors
    std::vector<int> pipeFds;
    std::vector<pid_t> pids;

    // Create one pipe between each pair of commands.
    for (int i = 0; i < numCommands - 1; i++){
        int fd[2];

        // fd[0] is the read end, fd[1] is the write end
        if (pipe(fd) == -1){
            std::cerr << "pipe failed" << std::endl;
            return 1;
        }

        pipeFds.push_back(fd[0]);
        pipeFds.push_back(fd[1]);
    }

    // Create one child process for each command in the pipeline
    for (int i = 0; i < numCommands; i++){
        pid_t pid = fork();

        if (pid < 0){
            std::cerr << "fork failed" << std::endl;
            return 1;
        }
        // Child process: set up input/output redirection and run command
        if (pid == 0){
            // If this is not the first command, read input from the previous pipe
            if (i > 0){
                dup2(pipeFds[(i - 1) * 2], STDIN_FILENO);
            }
            // If this is not the last command, write output to the next pipe
            if (i < numCommands - 1){
                dup2(pipeFds[(i * 2) + 1], STDOUT_FILENO);
            }

            // After dup2(), close all original pipe file descriptors
            for (size_t j = 0; j < pipeFds.size(); j++){
                close(pipeFds[j]);
            }

            std::vector<char*> argv = makeArgv(commands[i]);

            // Replace this child process with the actual command
            execvp(argv[0], argv.data());

            std::cerr << "exec failed: " << commands[i][0]
                      << ": " << std::strerror(errno) << std::endl;

            _exit(1);
        }

        // Parent stores the child's process ID
        pids.push_back(pid);
    }

    // Parent closes all pipe file descriptors
    for (size_t i = 0; i < pipeFds.size(); i++){
        close(pipeFds[i]);
    }

    // Parent waits for every command in the pipeline to finish
    for (size_t i = 0; i < pids.size(); i++){
        waitpid(pids[i], nullptr, 0);
    }

    return 0;
}

/************************[ EOF: exec.cpp ]***************************/