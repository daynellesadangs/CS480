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

    // Keep showing the prompt and reading input until EOF or input fails
    while (std::cout << getPrompt() && std::getline(std::cin, userInput)){
        ParsedCommand command = parseInput(userInput);

        // If the user typed "exit", end the shell program
        if (command.isExit){
            std::cout << "Exiting." << std::endl;
            return 0;
        }
        // If the parser marked the command as invalid, show an error
        if (!command.isValid){
            std::cerr << "Invalid command/input." << std::endl;
        }
        // If the command contains a pipe, run the piped-command handler
        else if (command.hasPipe){
            executePipeCommands(command.commands);
        }
        // Else, run a single normal command
        else{
            executeSingleCommand(command.commands[0]);
        }
    }

    // Print a newline if input ends
    std::cout << std::endl;
    return 0;
}

/************************[ EOF: main.cpp ]***************************/