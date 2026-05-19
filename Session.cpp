#include "Session.h"

Session::Session() : currentUser("guest") {
    rootDir = std::make_shared<Directory>("root");
    currentDir = rootDir;
}


Session& Session::getInstance() {
    static Session instance;
    return instance;
}

std::shared_ptr<Directory> Session::getCurrentDir() const {
    return currentDir;
}

std::shared_ptr<Directory> Session::getRootDir() const {
    return rootDir;
}

void Session::setCurrentDir(std::shared_ptr<Directory> dir) {
    if (dir) {
        currentDir = dir;
    }
}

std::string Session::getCurrentUser() const {
    return currentUser;
}

void Session::setCurrentUser(const std::string username) {
    currentUser = username;
}