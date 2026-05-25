//
// Created by Luiza on 25.05.2026.
//

#ifndef ENCRYPTED_VIRTUAL_FILE_SYSTEM_HISTORY_MANAGER_H
#define ENCRYPTED_VIRTUAL_FILE_SYSTEM_HISTORY_MANAGER_H

#include <vector>
#include <iostream>
#include <type_traits>
#include <memory>
#include "Directory.h"

template <typename T>
class HistoryManager {
private:
    std::vector<T> history;
    size_t maxSize;

public:
    explicit HistoryManager(size_t size = 5) : maxSize(size) {}

    void add(const T& item) {
        if (history.size() >= maxSize) {
            history.erase(history.begin());
        }
        history.push_back(item);
    }

    void display() const {
        if (history.empty()) {
            std::cout << "  (Istoricul este gol)\n";
            return;
        }

        for (const auto& item : history) {
            if constexpr (std::is_same_v<T, std::shared_ptr<Directory>>) {
                std::cout << "  -> " << item->getName() << "\n";
            } else {
                std::cout << "  -> " << item << "\n";
            }
        }
    }

};


#endif //ENCRYPTED_VIRTUAL_FILE_SYSTEM_HISTORY_MANAGER_H