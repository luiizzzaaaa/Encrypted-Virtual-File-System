#include <iostream>
#include "VirtualShell.h"
#include "Session.h"
#include "StorageManager.h"
#include "Logger.h"

int main() {
    std::cout<<"Encrypted Virtual File System 1.0:";

    StorageManager storageManager("vfs_storage.dat");
    std::cout << "[SISTEM] Se incarca structura de directoare...\n";
    std::shared_ptr<Directory> loadedRoot = storageManager.loadFileSystem();
    Session::getInstance().setRootDir(loadedRoot);
    
    storageManager.loadUsers();

    std::cout << "[SISTEM] Se incarca structura de directoare: \n";

    Session& session = Session::getInstance();
    session.setRootDir(loadedRoot);

    Logger::getInstance().logInfo("Aplicatia VFS a pornit cu succes.");


    std::cout << "[SISTEM] Terminal pregatit. Pentru a inchide aplicatia, apasati Enter pe o linie goala sau tastati 'exit'.\n\n";

    try {
        VirtualShell shell;
        shell.start();
    }
    catch (const std::exception& e) {
        std::cerr << "\n[CRITICAL ERROR] Shell-ul s-a oprit neasteptat: " << e.what() << "\n";
        Logger::getInstance().logError("Eroare fatala in executia Shell-ului: " + std::string(e.what()));
    }


    std::cout << "\n[SISTEM] Se salveaza schimbarile pe disc. Nu inchideti aplicatia...\n";

    bool saveSuccess = storageManager.saveFileSystem(session.getRootDir());

    if (saveSuccess) {
        std::cout << "[SISTEM] Toate datele au fost salvate cu succes in 'vfs_storage.dat'!\n";
        std::cout << "[SISTEM] La urmatoarea pornire, structura ta va fi restaurata exact asa cum ai lasat-o.\n";
        Logger::getInstance().logInfo("Aplicatia VFS s-a inchis in siguranta. Date salvate.");
    } else {
        std::cout << "[SISTEM ERROR] Atentie! Datele nu au putut fi salvate pe disc.\n";
    }

    std::cout << "\nLa revedere!\n";
    return 0;
}