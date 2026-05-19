#include "FileSystemEntity.h"

FileSystemEntity::FileSystemEntity(const std::string &name) : name(name) {}

std::string FileSystemEntity::getName() const {
    return name;
}

void FileSystemEntity::setParent( std::shared_ptr<FileSystemEntity> p) {
    parent = p;
}

std::shared_ptr<FileSystemEntity> FileSystemEntity::getParent() const {
    return parent.lock();
}