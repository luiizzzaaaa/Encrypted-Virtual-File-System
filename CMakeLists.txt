cmake_minimum_required(VERSION 3.20)
project(Encrypted_Virtual_File_System)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Encrypted_Virtual_File_System
        main.cpp
        FileSystemEntity.h
        FileSystemEntity.cpp
        File.h
        File.cpp
        Directory.h
        Directory.cpp
        Session.h
        Session.cpp
        VirtualShell.h
        VirtualShell.cpp
        main.cpp
        FileFactory.h
        FileFactory.cpp
        FileSystemException.h
        FileSystemException.cpp
        SymLink.h
        SymLink.cpp
)