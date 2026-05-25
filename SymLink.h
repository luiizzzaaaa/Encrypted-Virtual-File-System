
#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_SYMLINK_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_SYMLINK_H

#include "FileSystemEntity.h"
#include <iostream>

class SymLink : public FileSystemEntity {

private:
    std::weak_ptr<FileSystemEntity> target;

public:
    SymLink( const std::string& name, const std::shared_ptr<FileSystemEntity> targetEntity );

    std::shared_ptr<FileSystemEntity> getTarget() const;

    size_t getSize() const override;
    void printDetails(int indent = 0) const override;

};



#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_SYMLINK_H