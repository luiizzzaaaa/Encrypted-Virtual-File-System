//
// Created by Luiza on 21.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_USER_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_USER_H

#include <string>

class User {

private:
    std::string username;
    std::string passwordHash;
    std::string userKey;

    std::string simulateHash(const std::string& password) const;

public:
    User(const std::string& username, const std::string& password);

    std::string getUsername() const;
    std::string getUserKey() const;

    bool validatePassword( const std::string& password) const;

    User(const std::string& username, const std::string& passwordHash, const std::string& userKey);

    std::string getPasswordHash() const { return passwordHash; }

};




#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_USER_H