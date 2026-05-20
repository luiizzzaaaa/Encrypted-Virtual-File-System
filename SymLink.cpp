#include "SymLink.h"
#include <iostream>

SymLink::SymLink(const std::string& name, std::shared_ptr<FileSystemEntity> targetEntity)
    : FileSystemEntity(name), target(targetEntity) {}

std::shared_ptr<FileSystemEntity> SymLink::getTarget() const {
    return target.lock();
}

size_t SymLink::getSize() const {
    return 0;
}

void SymLink::printDetails(int indent) const {
    for ( int i = 0 ; i < indent; ++i) std::cout<< " ";

    auto actualTarget = getTarget();
    if (actualTarget) {
        std::cout << " link " << name << " -> " << actualTarget->getName() <<std::endl;
    } else {
        std::cout << " link " << name << " -> broken link"<<std::endl;
    }
}

