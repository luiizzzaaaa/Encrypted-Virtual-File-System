#include "File.h"
#include <iostream>

File::File( const std::string& name, size_t size)
    :FileSystemEntity(name), size(size) {}

size_t File::getSize() const {
    return size;
}

void File::printDetails(int indent) const {
    for ( int i = 0; i < indent; ++i ) {
        std::cout << " ";
    }
    std::cout<< " FILE " << name << " (" << size << " bytes)"<< std::endl;
}