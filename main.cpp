#include <iostream>
#include <string>
#include "kvstore.h"

int main() {
    KVStore store;
    std::string inp;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, inp);

        if (inp == "exit") break;

        // GET
        if (inp.rfind("GET ", 0) == 0) {
            std::string key = inp.substr(4);

            auto result = store.get(key);
            if (result.has_value()) {
                std::cout << result.value() << std::endl;
            } else {
                std::cout << "key not found" << std::endl;
            }
        }

        // SET
        else if (inp.rfind("SET ", 0) == 0) {
            std::string rest = inp.substr(4);

            std::size_t space = rest.find(' ');
            if (space == std::string::npos) {
                std::cout << "usage: set <key> <value>" << std::endl;
                continue;
            }

            std::string key = rest.substr(0, space);
            std::string value = rest.substr(space + 1);

            store.set(key, value);
            std::cout << "set" << std::endl;
        }

        // DEL
        else if (inp.rfind("DEL ", 0) == 0) {
            std::string key = inp.substr(4);
            store.del(key);
            std::cout << "deleted" << std::endl;
        }

        else {
            std::cout << "unknown command" << std::endl;
        }
    }

    return 0;
}