//
// Created by Luiza on 22.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_LOGGER_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_LOGGER_H
#include <string>
#include <fstream>

class Logger {

private:
    std::ofstream logFile;

    Logger();
    ~Logger();

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();

    void logInfo(const std::string& message);
    void logError(const std::string& errorMsg);

};



#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_LOGGER_H