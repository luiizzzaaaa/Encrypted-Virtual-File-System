#include "VirtualShell.h"
#include "Session.h"
#include "Directory.h"
#include "File.h"
#include <iostream>
#include <sstream>

VirtualShell::VirtualShell() : running(false) {}

void VirtualShell::start() {
    running = true;
    std::cout << "Welcome to Encrypted Virtual File System" << std::endl;
    std::cout << " Type 'help' to see available commands." << std::endl;

    std::string input;

    while (running) {
        Session& session = Session::getInstance();
        std::cout << session.getCurrentUser() << "@vfs:/"
                  << session.getCurrentDir()->getName() << "$ ";

        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input.empty()) continue;

        auto tokens = tokenize(input);
        std::string command = tokens[0];

        std::vector<std::string> args(tokens.begin() + 1, tokens.end());

        executeCommand( command, args );

    }

}

std::vector<std::string> VirtualShell::tokenize( const std::string& input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while ( ss >> token ) {
        tokens.push_back(token);
    }
    return tokens;
}




