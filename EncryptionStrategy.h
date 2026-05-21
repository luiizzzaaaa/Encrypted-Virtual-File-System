
#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_ENCRYPTIONSTRATEGY_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_ENCRYPTIONSTRATEGY_H

#include <string>

class EncryptionStrategy {

public:
    virtual ~EncryptionStrategy() = default;
    virtual std::string encrypt(const std::string& data, const std::string& key) = 0;
    virtual std::string decrypt(const std::string& data, const std::string& key) = 0;

};

class XorEncryption : public EncryptionStrategy {

public:
    std::string encrypt(const std::string & data, const std::string& key) override {
        if (key.empty()) return data;
        std::string result = data;

        for ( size_t i = 0; i < data.size(); ++i ) {
            result[i] = data[i] ^ key[i % key.size()];
        }
        return result;

    }

    std::string decrypt(const std::string& data, const std::string& key) override {

        return encrypt(data, key);
    }

};



#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_CRYPTOENGINE_H