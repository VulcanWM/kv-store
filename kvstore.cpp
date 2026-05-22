#include "kvstore.h"
#include <optional>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

KVStore::KVStore(const std::string& db_name)
    : filename(db_name + ".log") {
    std::string line;
    std::ifstream file(filename);
    while (getline (file, line)) {
        apply_command(line);
    }
    file.close();
    compact();
}

void KVStore::set(const std::string& key, const std::string& value) {
    store[key] = value;

    std::ofstream file(filename, std::ios::app);
    file << "SET " << key << " " << value << "\n";
    file.close();
}

std::optional<std::string> KVStore::get(const std::string& key) const {
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

void KVStore::compact() {
    std::ifstream in(filename);
    std::vector<std::string> new_lines;
    // loop through it backwards
    // note the dels and sets (del doesn't need to be added to array)
    // the dels and sets before that don't need to be noted
    // the ones added to the new lines will be reversed then add

    if (in.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        std::vector<std::string> deleted_keys;
        std::vector<std::string> set_keys;
        while (std::getline(in, line)) {
            lines.push_back(line);
        }

        // loop through in reverse
        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            std::string current = *it;
            if (current.rfind("DEL ", 0) == 0) {
                std::string key = current.substr(4);
                if (std::count(deleted_keys.begin(), deleted_keys.end(), key) == 0) {
                    deleted_keys.push_back(key);
                }
            }
            if (current.rfind("SET ", 0) == 0) {
                std::string rest = current.substr(4);
                std::size_t space = rest.find(' ');

                std::string key = rest.substr(0, space);
                if (std::count(deleted_keys.begin(), deleted_keys.end(), key) == 0
    && std::count(set_keys.begin(), set_keys.end(), key) == 0){
                    new_lines.push_back(current);
                    set_keys.push_back(key);
                }
            }
        }
        in.close();
    }
    std::ofstream file(filename, std::ios::trunc);

    for (auto it = new_lines.rbegin(); it != new_lines.rend(); ++it) {
        std::string current = *it;
        file << current << "\n";
    }
    file.close();
}