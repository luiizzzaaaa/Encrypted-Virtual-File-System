
#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILESYSTEMEXCEPTION_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILESYSTEMEXCEPTION_H

#include <exception>
#include <string>

class FileSystemException : public std::exception {

private:
    std::string message;

public:
    explicit FileSystemException( const std::string& msg);

    const char* what() const noexcept override;


};




#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_FILESYSTEMEXCEPTION_H