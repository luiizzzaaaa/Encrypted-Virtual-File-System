//
// Created by Luiza on 20.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_VIRTUALSHELL_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_VIRTUALSHELL_H

#include <string>
#include <vector>

class VirtualShell {

private:
    bool running;

    std::vector<std::string> tokenize(const std::string& input);
    void executeCommand(const std::string& command, const std::vector<std::string>& args);

    void cmdLs();
    void cmdMkdir(const std::vector<std::string>& args);
    void cmdCd(const std::vector<std::string>& args);
    void cmdHelp();

public:
    VirtualShell();
    void start();
 

};

#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_VIRTUALSHELL_H