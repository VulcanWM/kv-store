#ifndef KVSTORE_KVSTORE_H
#define KVSTORE_KVSTORE_H

#include <string>
#include <unordered_map>
#include <optional>

class KVStore {
public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void del(const std::string& key);

private:
    std::unordered_map<std::string, std::string> store;
};

#endif //KVSTORE_KVSTORE_H