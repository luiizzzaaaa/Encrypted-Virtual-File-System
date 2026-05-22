#include "PermissionManager.h"

void PermissionManager::grantPermission(const std::string& entityPath, const std::string& username, const std::string& perms) {
    permissionRegistry[entityPath][username] = perms;

}

std::string PermissionManager::getPermission(const std::string& entityPath, const std::string& username) {

    if ( username == "admin") return "rwx";

    if (permissionRegistry.find(entityPath) != permissionRegistry.end()) {
        if ( permissionRegistry[entityPath].find(username) != permissionRegistry[entityPath].end() ) {
            return permissionRegistry[entityPath][username];
        }
    }

    return "r-x " ;

}

bool PermissionManager::canRead(const std::string& entityPath, const std::string& username) {
    std::string perms = getPermission(entityPath, username);
    return perms.find('r') != std::string::npos;
}

bool PermissionManager::canWrite(const std::string& entityPath, const std::string& username) {
    std::string perms = getPermission(entityPath, username);
    return perms.find('w') != std::string::npos;
}

bool PermissionManager::canExecute(const std::string& entityPath, const std::string& username) {
    std::string perms = getPermission(entityPath, username);
    return perms.find('x') != std::string::npos;
}