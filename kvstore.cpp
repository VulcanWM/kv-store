#include "kvstore.h"
#include <optional>
#include <string>

void KVStore::set(const std::string& key, const std::string& value) {
    store[key] = value;
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
}