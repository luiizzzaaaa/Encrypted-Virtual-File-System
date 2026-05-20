

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILEFACTORY_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILEFACTORY_H

#include "FileSystemEntity.h"
#include <string>
#include <memory>

enum class EntityType {
    FILE,
    DIRECTORY
};

class FileFactory {

public:
    static std::shared_ptr<FileSystemEntity> createEntity(EntityType type, const std::string&name, size_t defaultSize = 0);


};

#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILEFACTORY_H