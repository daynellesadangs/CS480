/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #2, Experimental Shell

* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)

* FileName: main.cpp
***********************************************************************/

#include <iostream>
#include <string>
#include "xsh.h"

int main(){
    std::string userInput;

    while (std::cout << getPrompt() && std::getline(std::cin, userInput)){
        ParsedCommand command = parseInput(userInput);

        if (command.isExit){
            std::cout << "Exiting." << std::endl;
            return 0;
        }
        if (!command.isValid){
            std::cerr << "Invalid command or input." << std::endl;
        }
        else if (command.hasPipe){
            executePipeCommands(command.commands);
        }
        else{
            executeSingleCommand(command.commands[0]);
        }
    }
    std::cout << std::endl;
    return 0;
}

/************************[ EOF: main.cpp ]***************************/
