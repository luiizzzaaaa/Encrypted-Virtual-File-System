#include "Session.h"
#include "Logger.h"

Session::Session()  {
    rootDir = std::make_shared<Directory>("root");
    currentDir = rootDir;

    auto adminUser = std::make_shared<User>("admin", "admin123");
    auto guestUser = std::make_shared<User>("guest", "default_pass");

    addUser(adminUser);
    addUser(guestUser);

    currentUser = guestUser;
}


Session& Session::getInstance() {
    static Session instance;
    return instance;
}

std::shared_ptr<Directory> Session::getCurrentDir() const {
    return currentDir;
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
        Logger::getInstance(). logInfo("User " + user->getUsername() + " logged in" );
    }
}