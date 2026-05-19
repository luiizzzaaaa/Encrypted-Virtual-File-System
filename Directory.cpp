#include "Directory.h"
#include <iostream>

Directory::Directory(const std::string& name) : FileSystemEntity(name) {}

void Directory::addEntity( std::shared_ptr<FileSystemEntity> entity ) {
    if (entity) {
        entity->setParent(shared_from_this());
        children.push_back(entity);
    }
}

size_t Directory::getSize() const {
    size_t totalSize = 0;
    for (const auto& child : children) {
        totalSize += child->getSize();
    }
    return totalSize;
}


void Directory::printDetails( int indent) const {
    for ( int i = 0; i < indent; ++i )
        std::cout << ' ';

    std::cout << "Directory " << name << " (Total: " << getSize() << "bytes)" << std::endl;

    for ( const auto& child : children) {
        child->printDetails(indent + 2);
    }


}