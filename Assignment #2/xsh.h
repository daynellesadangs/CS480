
/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #2, Experimental Shell

* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)

* FileName: xsh.h
***********************************************************************/

#ifndef XSH_H
#define XSH_H

#include <string>
#include <vector>

struct ParsedCommand{
    bool isExit = false;
    bool isValid = false;
    bool hasPipe = false;

    std::vector<std::vector<std::string> > commands;
};

std::string getPrompt();

ParsedCommand parseInput(const std::string& input);

int executeSingleCommand(const std::vector<std::string>& command);
int executePipeCommands(const std::vector<std::vector<std::string> >& commands);

#endif

/************************[ EOF: xsh.h ]***************************/