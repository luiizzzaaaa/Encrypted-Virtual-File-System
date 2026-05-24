

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_SESSION_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_SESSION_H

#include "Directory.h"
#include "User.h"
#include <memory>
#include <string>
#include <map>

class Session {

private:
    std::shared_ptr<Directory> rootDir;
    std::shared_ptr<Directory> currentDir;

    std::shared_ptr<User> currentUser;

    std::map<std::string, std::shared_ptr<User>> userRegistry;

    Session();

public:
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    static Session& getInstance();

    std::shared_ptr<Directory> getCurrentDir() const;
    void setCurrentDir(std::shared_ptr<Directory> dir);

    std::shared_ptr<User> getCurrentUser() const;
    void setCurrentUser(std::shared_ptr<User> user);


    std::shared_ptr<Directory> getRootDir() const { return rootDir; }
    void setRootDir(std::shared_ptr<Directory> root) { rootDir = root; currentDir = root; }

    std::shared_ptr<User> getUser(const std::string& username) {
        if (userRegistry.find(username) != userRegistry.end()) {
            return userRegistry[username];
        }
        return nullptr;
    }

    void addUser(std::shared_ptr<User> newUser) {
        userRegistry[newUser->getUsername()] = newUser;
    }

    const std::map<std::string, std::shared_ptr<User>>& getAllUsers() const { return userRegistry; }


};





#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_SESSION_H