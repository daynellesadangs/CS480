
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

std::string getPrompt();

bool isExitCommand(const std::string& input);

std::vector<std::vector<std::string> > parseInput(const std::string& input);

bool isValidCommand(const std::vector<std::vector<std::string> >& commands);
bool hasPipe(const std::vector<std::vector<std::string> >& commands);

int executeSingleCommand(const std::vector<std::string>& command);
int executePipeCommands(const std::vector<std::vector<std::string> >& commands);

#endif

/************************[ EOF: xsh.h ]***************************/