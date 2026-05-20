#include "FileFactory.h"
#include "File.h"
#include "Directory.h"
#include <iostream>

std::shared_ptr<FileSystemEntity> FileFactory::createEntity(EntityType type, const std::string& name, size_t defaultSize) {
    switch (type) {
        case EntityType::FILE :
            return std::make_shared<File>(name, defaultSize);

        case EntityType::DIRECTORY :
            return std::make_shared<Directory>(name);

        default:
            std::cout << "Unknown entity type" << std::endl;
            return nullptr;
    }
}