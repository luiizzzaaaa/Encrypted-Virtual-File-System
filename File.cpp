#include "File.h"
#include "EncryptionStrategy.h"
#include "CryptoEngine.h"
#include "Session.h"
#include <iostream>

File::File( const std::string& name, size_t initialSize)
    :FileSystemEntity(name) {

    if (initialSize > 0 ) {
        encryptedContent = std::string(initialSize, ' ');
    }
}

void File::writeContent(const std::string& rawText) {
    CryptoEngine<XorEncryption> engine;
    std::string userKey = Session::getInstance().getCurrentUser()->getUserKey();

    this->encryptedContent = engine.encryptData(rawText, userKey);
}

std::string File::readContent() const {
    CryptoEngine<XorEncryption> engine;
    std::string userKey = Session::getInstance().getCurrentUser()->getUserKey();

    return engine.decryptData(this->encryptedContent, userKey);
}

size_t File::getSize() const {
    return encryptedContent.size();
}

void File::printDetails(int indent) const {
    for ( int i = 0; i < indent; ++i ) {
        std::cout << " ";
    }
    std::cout<< " FILE " << name << " (" << getSize() << " bytes)"<< std::endl;
}