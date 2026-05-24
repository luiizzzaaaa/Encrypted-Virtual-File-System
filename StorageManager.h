

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_STORAGEMANAGER_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_STORAGEMANAGER_H


#include <string>
#include <memory>
#include "Directory.h"

class StorageManager {

private:
    std::string storageFileName;

    void serializeDirectory(std::shared_ptr<Directory> dir, std::ofstream& outFile);

public:
    explicit StorageManager(const std::string& fileName = "vfs_storage.dat");

    bool saveFileSystem(std::shared_ptr<Directory> rootDir);

    std::shared_ptr<Directory> loadFileSystem();
};



#endif