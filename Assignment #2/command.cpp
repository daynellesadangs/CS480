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

std::string getPrompt(){
    const char* username = std::getenv("USER");

    if (username != nullptr){
        return std::string(username) + "% ";
    }
    return "xsh% ";
}

ParsedCommand parseInput(const std::string& input){
    ParsedCommand result;

    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> currentCommand;

    while (ss >> token){
        if (token == "|"){
            result.hasPipe = true;

            if (currentCommand.empty() || currentCommand.size() > 2){
                return result;
            }

            result.commands.push_back(currentCommand);
            currentCommand.clear();
        }
        else{
            currentCommand.push_back(token);
        }
    }

    if (currentCommand.empty() || currentCommand.size() > 2){
        return result;
    }

    result.commands.push_back(currentCommand);

    if (result.commands.size() == 1 && result.commands[0].size() == 1 && result.commands[0][0] == "exit"){
        result.isExit = true;
        result.isValid = true;
        result.hasPipe = false;
        return result;
    }

    if (result.hasPipe && result.commands.size() < 2){
        return result;
    }

    result.isValid = true;
    return result;
}

/************************[ EOF: command.cpp ]***************************/