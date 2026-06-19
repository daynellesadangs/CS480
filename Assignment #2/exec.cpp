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

static std::vector<char*> makeArgv(const std::vector<std::string>& command){
    std::vector<char*> argv;

    for (size_t i = 0; i < command.size(); i++){
        argv.push_back(const_cast<char*>(command[i].c_str()));
    }

    argv.push_back(nullptr);
    return argv;
}

int executeSingleCommand(const std::vector<std::string>& command){
    pid_t pid = fork();

    if (pid < 0){
        std::cerr << "fork failed" << std::endl;
        return 1;
    }
    if (pid == 0){
        std::vector<char*> argv = makeArgv(command);

        execvp(argv[0], argv.data());

        std::cerr << "exec failed: " << command[0]
                  << ": " << std::strerror(errno) << std::endl;

        _exit(1);
    }

    waitpid(pid, nullptr, 0);
    return 0;
}

int executePipeCommands(const std::vector<std::vector<std::string> >& commands){
    int numCommands = static_cast<int>(commands.size());

    std::vector<int> pipeFds;
    std::vector<pid_t> pids;

    for (int i = 0; i < numCommands - 1; i++){
        int fd[2];

        if (pipe(fd) == -1){
            std::cerr << "pipe failed" << std::endl;
            return 1;
        }

        pipeFds.push_back(fd[0]);
        pipeFds.push_back(fd[1]);
    }

    for (int i = 0; i < numCommands; i++){
        pid_t pid = fork();

        if (pid < 0){
            std::cerr << "fork failed" << std::endl;
            return 1;
        }
        if (pid == 0){
            if (i > 0){
                dup2(pipeFds[(i - 1) * 2], STDIN_FILENO);
            }
            if (i < numCommands - 1){
                dup2(pipeFds[(i * 2) + 1], STDOUT_FILENO);
            }

            for (size_t j = 0; j < pipeFds.size(); j++){
                close(pipeFds[j]);
            }

            std::vector<char*> argv = makeArgv(commands[i]);

            execvp(argv[0], argv.data());

            std::cerr << "exec failed: " << commands[i][0]
                      << ": " << std::strerror(errno) << std::endl;

            _exit(1);
        }

        pids.push_back(pid);
    }

    for (size_t i = 0; i < pipeFds.size(); i++){
        close(pipeFds[i]);
    }

    for (size_t i = 0; i < pids.size(); i++){
        waitpid(pids[i], nullptr, 0);
    }

    return 0;
}

/************************[ EOF: exec.cpp ]***************************/