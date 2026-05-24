

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_DIRECTORY_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_DIRECTORY_H

#include "FileSystemEntity.h"
#include <vector>

class Directory : public FileSystemEntity {

private:
    std::vector<std::shared_ptr<FileSystemEntity>> children;

public:
    Directory(const std::string& name);

    void addEntity(std::shared_ptr<FileSystemEntity> entity);

    size_t getSize() const override;
    void printDetails(int indent = 0) const override;

    const std::vector<std::shared_ptr<FileSystemEntity>>& getEntities() const { return children; }



};


#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_DIRECTORY_H