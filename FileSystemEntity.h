

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILESYSTEMENTITY_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILESYSTEMENTITY_H

#include <string>
#include <memory>

class FileSystemEntity : public std::enable_shared_from_this<FileSystemEntity> {

protected:
    std::string name;
    std::weak_ptr<FileSystemEntity> parent;

public:
    FileSystemEntity( const std::string &name);

    virtual ~FileSystemEntity() = default;

    virtual void printDetails(int indent = 0) const = 0;

    std::string getName() const;
    void setParent( std::shared_ptr<FileSystemEntity> p);
    std::shared_ptr<FileSystemEntity> getParent() const;

    virtual size_t getSize() const = 0;

};

#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILESYSTEMENTITY_H