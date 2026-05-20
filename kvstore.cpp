#include "kvstore.h"
#include <optional>
#include <string>
#include <fstream>
#include <iostream>

KVStore::KVStore(const std::string& db_name)
    : filename(db_name + ".log") {
    std::string line;
    std::ifstream file(filename);
    while (getline (file, line)) {
        apply_command(line);
    }
    file.close();
}

void KVStore::set(const std::string& key, const std::string& value) {
    store[key] = value;

    std::ofstream file(filename, std::ios::app);
    file << "SET " + key + " " + value + "\n";
    file.close();
}

std::optional<std::string> KVStore::get(const std::string& key) {
    auto value = store.find(key);

    if (value != store.end()) {
        return value->second;
    }

    return std::nullopt;
}

void KVStore::del(const std::string& key) {
    store.erase(key);

    std::ofstream file(filename, std::ios::app);
    file << "DEL " + key + "\n";
    file.close();
}

void KVStore::apply_command(const std::string& line) {
    if (line.rfind("SET ", 0) == 0) {
        std::string rest = line.substr(4);

        std::size_t space = rest.find(' ');
        if (space == std::string::npos) return;

        std::string key = rest.substr(0, space);
        std::string value = rest.substr(space + 1);

        store[key] = value;
    }

    else if (line.rfind("DEL ", 0) == 0) {
        std::string key = line.substr(4);
        store.erase(key);
    }
}