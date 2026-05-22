#include "FileFactory.h"
#include "File.h"
#include "Directory.h"
#include "SymLink.h"
#include "Logger.h"
#include <iostream>

std::shared_ptr<FileSystemEntity> FileFactory::createEntity(EntityType type, const std::string& name, size_t defaultSize) {
    switch (type) {
        case EntityType::FILE :
            Logger::getInstance().logInfo("Creating a file: " + name);
            return std::make_shared<File>(name, defaultSize);

        case EntityType::DIRECTORY :
            Logger::getInstance().logInfo("Creating a director: " + name);
            return std::make_shared<Directory>(name);

        case EntityType::SYMLINK :
            Logger::getInstance().logInfo("Creating a SymLink: " + name);
            return std::make_shared<SymLink>(name,nullptr);

        default:
            std::cout << "Unknown entity type" << std::endl;
            return nullptr;
    }
}