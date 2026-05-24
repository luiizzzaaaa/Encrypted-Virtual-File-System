#include "VirtualShell.h"
#include "Session.h"
#include "Directory.h"
#include "File.h"
#include "FileFactory.h"
#include "FileSystemException.h"
#include "Logger.h"
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
        std::string fullPath = "";
        std::shared_ptr<FileSystemEntity> temp = session.getCurrentDir();

        while (temp != nullptr) {
            fullPath = "/" + temp->getName() + fullPath;
            temp = temp->getParent();
        }

        std::cout << session.getCurrentUser()->getUsername() << "@vfs:" << fullPath << "$ ";

        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input.empty()) continue;

        auto tokens = tokenize(input);
        std::string command = tokens[0];
        std::vector<std::string> args(tokens.begin() + 1, tokens.end());

        Logger::getInstance().logInfo("command: " + command);

        try {
            executeCommand(command, args);
        }
        catch (const FileSystemException& e) {
            std::cout << "Error" << e.what() << std::endl;
            Logger::getInstance().logError("Error VFS: " + std::string(e.what()));

        }
        catch (const std::exception& e) {
            std::cout << "System Error" << e.what() << std::endl;
            Logger::getInstance().logError("Critical system error: " + std::string(e.what()));
        }

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
    } else if (command == "touch"){
        cmdTouch(args);
    }else if ( command == "cd" ) {
        cmdCd(args);
    }else if (command == "login") {
        cmdLogin(args);
    } else if (command == "useradd") {
        cmdUserAdd(args);
    }else if ( command == "exit") {
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
                <<" exit               - Close the app" << std::endl
                <<" useradd <user> <p> - Create a new user with a password." << std::endl
                <<" login <user>       - Log in as a different user." << std::endl;
}

void VirtualShell::cmdLs() {
    auto currentDir = Session::getInstance().getCurrentDir();
    const auto& children = currentDir->getEntities();

    if (children.empty()) {
        std::cout << "  (Folder gol)\n";
    } else {
        std::cout << "Continutul directorului '" << currentDir->getName() << "':\n";
        for (const auto& entity : children) {
            if (std::dynamic_pointer_cast<Directory>(entity)) {
                std::cout << "  [DIR]  " << entity->getName() << "\n";
            } else {
                std::cout << "  [FILE] " << entity->getName() << "\n";
            }
        }
    }
}

void VirtualShell::cmdMkdir(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << " You must specify a directory." << std::endl;
        return;
    }

    std::string dirName = args[0];
    auto newDir = FileFactory::createEntity(EntityType::DIRECTORY, dirName);

    if (newDir) {
        Session::getInstance().getCurrentDir()->addEntity(newDir);
        std::cout << " Creating directory " << dirName << std::endl;
    }
}

void VirtualShell::cmdTouch(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << " You must specify a file name." << std::endl;
        return;
    }

    std::string fileName = args[0];
    auto currentDir = Session::getInstance().getCurrentDir();
    bool exists = false;

    for (const auto& entity : currentDir->getEntities()) {
        if (entity->getName() == fileName) {
            exists = true;
            break;
        }
    }

    if (exists) {
        std::cout << " Error: An entity named '" << fileName << "' already exists." << std::endl;
    } else {
        auto newFile = FileFactory::createEntity(EntityType::FILE, fileName);
        if (newFile) {
            currentDir->addEntity(newFile);
            std::cout << " Creating file " << fileName << std::endl;
        }
    }
}

void VirtualShell::cmdCd(const std::vector<std::string>& args) {
    if (args.empty()) {
        throw FileSystemException("cd requires a target directory name");
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
        auto currentDir = session.getCurrentDir();
        bool found = false;

        for (const auto& entity : currentDir->getEntities()) {
            if (entity->getName() == target) {
                found = true;

                if (auto subDir = std::dynamic_pointer_cast<Directory>(entity)) {
                    session.setCurrentDir(subDir);
                } else {

                    throw FileSystemException("'" + target + "' is a file, not a directory.");
                }
                break;
            }
        }

        if (!found) {
            throw FileSystemException("Directory" + target + "' is not found.");
        }
    }
}

void VirtualShell::cmdUserAdd(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << " Usage: useradd <username> <password>\n";
        return;
    }

    std::string newUsername = args[0];
    std::string newPassword = args[1];

    if (Session::getInstance().getUser(newUsername) != nullptr) {
        std::cout << " Error: User '" << newUsername << "' already exists!\n";
        return;
    }

    auto newUser = std::make_shared<User>(newUsername, newPassword);
    Session::getInstance().addUser(newUser);

    std::cout << " User '" << newUsername << "' created successfully!\n";
    std::cout << " [SECRET] Generated UserKey: " << newUser->getUserKey() << "\n";
}

void VirtualShell::cmdLogin(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << " Usage: login <username>\n";
        return;
    }

    std::string targetUsername = args[0];
    std::cout << " Password for " << targetUsername << ": ";
    std::string enteredPassword;
    std::getline(std::cin, enteredPassword);

    auto targetUser = Session::getInstance().getUser(targetUsername);

    if (targetUser != nullptr) {
        if (targetUser->validatePassword(enteredPassword)) {
            Session::getInstance().setCurrentUser(targetUser);
            std::cout << " Successfully logged in as " << targetUsername << ".\n";
        } else {
            std::cout << " Access Denied: Incorrect password.\n";
        }
    } else {
        std::cout << " Error: User '" << targetUsername << "' not found!\n";
    }
}