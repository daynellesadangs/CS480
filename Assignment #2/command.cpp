/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #2, Experimental Shell
*
* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)
*
* FileName: command.cpp
***********************************************************************/

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include "xsh.h"

// Grab username of current user and use it as the shell prompt.
std::string getPrompt(){
    const char* username = std::getenv("USER");

    // If the USER environment variable exists, return "username% "
    if (username != nullptr){
        return std::string(username) + "% ";
    }
    return "xsh% ";
}

// Parse the user's command line input into a ParsedCommand object.
ParsedCommand parseInput(const std::string& input){
    ParsedCommand result;

    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> currentCommand;

    // Read each word/token from the user's input
    while (ss >> token){

        // Check for pipes in command line input to separate commands
        if (token == "|"){
            result.hasPipe = true;

            // Invalid if there is no command before the pipe or if the command has more than 2 tokens
            if (currentCommand.empty() || currentCommand.size() > 2){
                return result;
            }

            // Store the command before the pipe and start collecting the next command
            result.commands.push_back(currentCommand);
            currentCommand.clear();
        }
        else{
            // Add normal words/arguments to the current command
            currentCommand.push_back(token);
        }
    }

    // Ensure last command is valid and store it
    if (currentCommand.empty() || currentCommand.size() > 2){
        return result;
    }

    result.commands.push_back(currentCommand);

    // Recognize "exit" as a valid exit command
    if (result.commands.size() == 1 && result.commands[0].size() == 1 && result.commands[0][0] == "exit"){
        result.isExit = true;
        result.isValid = true;
        result.hasPipe = false;
        return result;
    }

    // If a pipe was found, there must be at least two commands
    if (result.hasPipe && result.commands.size() < 2){
        return result;
    }

    // If all checks passed, the parsed command is valid
    result.isValid = true;
    return result;
}

/************************[ EOF: command.cpp ]***************************/