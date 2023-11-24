#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
using std::getline;
#include <map>
using std::map;



class ConfigManager {

    public:
    ConfigManager();
    ConfigManager(const string& filename);
    ConfigManager(const ConfigManager& copyConfigManager);

    bool loadConfig();
    bool saveConfig();
    string getValue(const string& key) const;
    void setValue(const string& key, const string& value);

    private:

    string filename;
    map<string, string> configValue;
};

#endif