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

void VirtualShell::executeCommand( const std::string& command, const std::vector<std::string>& args) {
    if ( command == "help") {
        cmdHelp();
    } else if (command == "ls" ) {
        cmdLs();
    } else if (command == "mkdir") {
        cmdMkdir(args);
    } else if ( command == "cd" ) {
        cmdCd(args);
    } else if ( command == "exit") {
        running = false;
        std::cout << " Exiting ";
    } else {
        std::cout << " Command not found: " << command<< ". Type 'help' for options." << std::endl;
    }

}

void VirtualShell::cmdHelp() {
    std::cout << "Available commands:" << std::endl
                <<" ls                 - List details of the current directory." << std::endl
                <<" mkdir <name>       - Create a directory." << std::endl
                <<" cd <name>          - Change the current directory.(use '..' for parent)" << std::endl
                <<" exit               - Close the app" << std::endl;
}

void VirtualShell::cmdLs() {
    Session::getInstance().getCurrentDir()->printDetails();
}

void VirtualShell::cmdMkdir(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << " You must specify a directory." << std::endl;
        return;
    }

    std::string dirName = args[0];
    auto newDir = std::make_shared<Directory>(dirName);

    Session::getInstance().getCurrentDir()->addEntity(newDir);
    std::cout << " Creating directory " << dirName << std::endl;
}

void VirtualShell::cmdCd(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout<< "Error: cd requires a target directory." << std::endl;
        return;
    }
    std::string target = args[0];
    Session& session = Session::getInstance();

    if (target == "..") {
        auto parent = session.getCurrentDir()->getParent();
        if (parent) {
            auto parentDir = std::dynamic_pointer_cast<Directory>(parent);
            if (parentDir) {
                session.setCurrentDir(parentDir);
            }
        } else {
            std::cout << " Alredy at root directory." << std::endl;
        }
    } else {
        std::cout << " inca n am fct child navigation" << std::endl;
    }
}




