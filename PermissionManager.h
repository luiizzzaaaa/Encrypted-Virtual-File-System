//
// Created by Luiza on 22.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_PERMISSIONMANAGER_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_PERMISSIONMANAGER_H

#include <string>
#include <map>
#include <memory>
#include "FileSystemEntity.h"


class PermissionManager {

private:
    std::map<std::string, std::map<std::string, std::string>> permissionRegistry;

    std::string getPermission( const std::string& entityPath, const std::string& username);

public:
    PermissionManager() = default;

    void grantPermission( const std::string& entityPath, const std::string& username, const std::string& perms);

    bool canRead(const std::string& entityPath, const std::string& username);
    bool canWrite(const std::string& entityPath, const std::string& username);
    bool canExecute(const std::string& entityPath, const std::string& username);


};





#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_PERMISSIONMANAGER_H