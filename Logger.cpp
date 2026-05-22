#include"Logger.h"
#include<iostream>

Logger::Logger() {

    logFile.open("vfs_system.log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file" << std::endl;
    } else {
        logFile<<" New Session VFS "<<std::endl;
    }

}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::logInfo(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "INFO: " << message << std::endl;
        logFile.flush();
    }
}

void Logger::logError(const std::string& errorMsg) {
    if (logFile.is_open()) {
        logFile << "ERROR: " << errorMsg << std::endl;
        logFile.flush();
    }
}

