#ifndef dotenv_H
#define dotenv_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

class dotenv {
   public:
    explicit dotenv(const std::string &filepath) {
        load(filepath);
    }

    std::string get(const std::string &key, const std::string &defaultValue = "") const {
        auto it = envVariables.find(key);
        if (it != envVariables.end()) {
            return it->second;  // Found in .env file
        }
        const char *envValue = std::getenv(key.c_str());
        return envValue ? envValue : defaultValue;  // Fallback to system environment or default
    }

    void set(const std::string &key, const std::string &value) {
        envVariables[key] = value;

        setenv(key.c_str(), value.c_str(), 1);
    }

   private:
    std::unordered_map<std::string, std::string> envVariables;

    static std::string trim(const std::string &str) {
        auto start = str.find_first_not_of(" \t");
        auto end = str.find_last_not_of(" \t");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Load .env file
    void load(const std::string &filepath) {
        std::ifstream file(filepath);
        if (!file) {
            std::cerr << "Could not open " << filepath << " file" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;

            size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos) continue;  // Skip if no '=' is found

            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));

            if (!value.empty() && (value[0] == '"' || value[0] == '\'')) {
                value = value.substr(1, value.size() - 2);
            }

            envVariables[key] = value;

            setenv(key.c_str(), value.c_str(), 1);
        }
    }
};

#endif  // dotenv_H
