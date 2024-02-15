#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <fcntl.h> // for file descriptor manipulation functions

/*
 the data structure to hold the parsed command
 including any arguments and an optional output file for redirection
*/ 
struct ParsedCommand {
    std::vector<std::string> args; // stores command arguments
    std::string outputFile; // store the output file name for redirection, if any
};

// parses the user input into a ParsedCommand data structure above
ParsedCommand customParseInput(const std::string& input) {
    ParsedCommand command;
    std::string token;
    bool redirectOutput = false;
    bool inQuotes = false;
    for (size_t i = 0; i < input.length(); ++i) {
        char currentChar = input[i];
        // toggle inQuotes flag if a quote is encountered
        if (currentChar == '\"') {
            inQuotes = !inQuotes;
            continue; // skip adding the quote to the token
        }
        // handle space characters
        if (currentChar == ' ' && !inQuotes) {
            if (!token.empty()) {
                if (redirectOutput) {
                    command.outputFile = token;
                    break; // assuming only one output redirection per command
                } else {
                    command.args.push_back(token);
                    token.clear();
                }
            }
        } else if (currentChar == '>' && !inQuotes && token.empty()) {
            redirectOutput = true;
        } else {
            token += currentChar;
        }
    }
    // add the last token if it's not empty
    if (!token.empty()) {
        if (redirectOutput) {
            command.outputFile = token;
        } else {
            command.args.push_back(token);
        }
    }
    return command;
}

// converts a vector of std::string arguments to a vector of char* pointers required by execvp
std::vector<char*> convertArgs(const std::vector<std::string>& args) {
    std::vector<char*> cargs;
    for (const auto& arg : args) {
        cargs.push_back(const_cast<char*>(arg.c_str())); // safe cast since execvp doesn't modify arguments.
    }
    cargs.push_back(nullptr); // execvp expects a NULL-terminated array of arguments.
    return cargs;
}

/*

TODOs
    We converted the solution code into TODOs.
    The TODOs are in the order of the steps you should take to complete the assignment.

OVERVIEW
1. fork into a child process to execute the function.

2. Outside of the child process, wait using `waitpid` for the new process to finish.

*/
void do_fork(const ParsedCommand& command) {
    // TODO 1: Research how the fork system call works. Understand parent and child processes.

    // TODO 2: Use fork to create a child process and handle the outcomes.

    // TODO 2.1: Handle the child process case.

    // TODO 3: In the child process, check if output redirection is specified. See the structure of the ParsedCommand data structure we provide for you.

    // TODO 3.1: Open the specified file for output redirection.
    
    // TODO 5: Handle errors from open operation.
    
    // TODO 3.2: Redirect STDOUT to the opened file. See -> `dup2`

    // TODO 4: Convert command arguments and execute the command using execvp.
    
    // TODO 2.1: Handle the parent process case.
    
    // TODO 6: Wait for the child process to finish. See -> `waitpid`

    // TODO 7: Handle fork failure.

    // TODO 8: ...this would be after everything, but don't forget to close the file descriptor if it was opened. And then celebrate! You've just written a shell program!
}


// our old friend main(), this is entry for our shell program ;)
int main() {
    std::string input; // stores user input

    // our mina loop: prompt for input, parse, and execute commands until "exit" is entered
    while (std::cout << "412shell> " && std::getline(std::cin, input) && input != "exit") {
        ParsedCommand command = customParseInput(input); // parse the user input into a command
        do_fork(command);
    }

    return 0;
}
