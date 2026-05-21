//
// Created by Luiza on 21.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_CRYPTOENGINE_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_CRYPTOENGINE_H

#include <string>
#include <memory>

template <typename Strategy>

class CryptoEngine {

private :
    Strategy strategy;

public:
    CryptoEngine() = default;

    std::string encryptData(const std::string& data, const std::string& key) {

        return strategy.encrypt(data, key);
    }

    std::string decryptData(const std::string& data, const std::string& key) {

        return strategy.decrypt(data, key);
    }

};


#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_CRYPTOENGINE_H