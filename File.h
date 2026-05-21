//
// Created by Luiza on 19.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILE_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILE_H

#include "FileSystemEntity.h"
#include <vector>
#include <string>

class File : public FileSystemEntity {

private:
    std::string encryptedContent;

public:
    File(const std::string& name, size_t initialSize = 0);

    void writeContent(const std::string& rawText);
    std::string readContent() const;

    size_t getSize() const override;
    void printDetails(int indent = 0) const override;

};




#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILE_H