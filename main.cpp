#include <iostream>
#include "VirtualShell.h"
#include "Session.h"
#include "StorageManager.h"
#include "Logger.h"

int main() {

    std::cout<<"Encrypted virtual file system 1.0:";


    StorageManager storageManager("vfs_storage.dat");
    std::cout << "[SISTEM] directory uploading \n";

    std::shared_ptr<Directory> loadedRoot = storageManager.loadFileSystem();
    Session::getInstance().setRootDir(loadedRoot);
    storageManager.loadUsers();

    Session& session = Session::getInstance();
    Logger::getInstance().logInfo("vfs started:");

    std::cout << "[SISTEM] Terminal pregatit. Pentru a inchide aplicatia tastati 'exit'.\n\n";

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