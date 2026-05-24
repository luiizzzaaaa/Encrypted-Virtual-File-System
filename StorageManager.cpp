#include "StorageManager.h"
#include "File.h"
#include "Directory.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <vector>

StorageManager::StorageManager(const std::string& fileName) : storageFileName(fileName) {}

void StorageManager::serializeDirectory(std::shared_ptr<Directory> dir, std::ofstream& outFile) {
    if (!dir) return;

    for (const auto& entity : dir->getEntities()) {

        if (auto subDir = std::dynamic_pointer_cast<Directory>(entity)) {
            outFile << "DIR|" << subDir->getName() << "\n";
            serializeDirectory(subDir, outFile);
            outFile << "ENDDIR|\n";
        }
        else if (auto file = std::dynamic_pointer_cast<File>(entity)) {
            outFile << "FILE|" << file->getName() << "\n";
        }
    }
}

bool StorageManager::saveFileSystem(std::shared_ptr<Directory> rootDir) {
    std::ofstream outFile(storageFileName);
    if (!outFile.is_open()) {
        Logger::getInstance().logError("StorageManager: Nu am putut deschide fisierul pentru salvare (" + storageFileName + ")");
        return false;
    }

    outFile << "ROOT|" << rootDir->getName() << "\n";
    serializeDirectory(rootDir, outFile);
    
    outFile.close();
    Logger::getInstance().logInfo("StorageManager: Sistemul de fisiere a fost salvat cu succes pe disc.");
    return true;
}

std::shared_ptr<Directory> StorageManager::loadFileSystem() {
    std::ifstream inFile(storageFileName);

    if (!inFile.is_open()) {
        Logger::getInstance().logInfo("StorageManager: Nu s-a gasit fisier de salvare. Se creaza un root nou.");
        return std::make_shared<Directory>("root"); 
    }

    std::string line;
    std::shared_ptr<Directory> rootDir = nullptr;

    if (std::getline(inFile, line) && line.find("ROOT|") == 0) {
        std::string rootName = line.substr(5);
        rootDir = std::make_shared<Directory>(rootName);
    } else {
        return std::make_shared<Directory>("root");
    }

    std::vector<std::shared_ptr<Directory>> dirStack;
    dirStack.push_back(rootDir);

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        auto currentDir = dirStack.back();
        
        if (line.find("DIR|") == 0) {
            std::string dirName = line.substr(4);
            auto newDir = std::make_shared<Directory>(dirName);
            currentDir->addEntity(newDir);
            dirStack.push_back(newDir);
        } 
        else if (line == "ENDDIR|") {
            if (dirStack.size() > 1) {
                dirStack.pop_back();
            }
        }
        else if (line.find("FILE|") == 0) {
            std::string fileName = line.substr(5);
            auto newFile = std::make_shared<File>(fileName);
            currentDir->addEntity(newFile);
        }
    }

    inFile.close();
    Logger::getInstance().logInfo("StorageManager: Sistemul de fisiere a fost reconstruit de pe disc.");
    return rootDir;
}