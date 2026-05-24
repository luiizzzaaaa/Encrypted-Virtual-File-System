#include "User.h"
#include <algorithm>

User::User(const std::string& username, const std::string& password)
    : username(username){

        this->passwordHash = simulateHash(password);

    this->userKey = passwordHash + "_" + username;
    }

std::string User::simulateHash( const std::string& password ) const {
    std::string hashed = password;
    std::reverse(hashed.begin(), hashed.end());
    return hashed+ "secure";
}

std::string User::getUsername() const {
    return username;
}

std::string User::getUserKey() const {
    return userKey;
}

bool User::validatePassword(const std::string& password) const {
    return simulateHash(password) == passwordHash;
}

User::User(const std::string& username, const std::string& passwordHash, const std::string& userKey)
    : username(username), passwordHash(passwordHash), userKey(userKey) {}