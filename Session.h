

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_SESSION_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_SESSION_H

#include "Directory.h"
#include <memory>
#include <string>

class Session {

private:
    std::shared_ptr<Directory> rootDir;
    std::shared_ptr<Directory> currentDir;

    std::string currentUser;

    Session();

public:
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    static Session& getInstance();

    std::shared_ptr<Directory> getRootDir() const;
    std::shared_ptr<Directory> getCurrentDir() const;
    void setCurrentDir(std::shared_ptr<Directory> dir);

    std::string getCurrentUser() const;
    void setCurrentUser(std::string& username);


};





#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_SESSION_H