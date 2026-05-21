#include "Session.h"

Session::Session()  {
    rootDir = std::make_shared<Directory>("root");
    currentDir = rootDir;

    currentUser = std::make_shared<User>("guest", "default_pass");
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

std::shared_ptr<User> Session::getCurrentUser() const {
    return currentUser;
}

void Session::setCurrentUser( std::shared_ptr<User> user) {

    if (user) {
        currentUser = user;
    }
}