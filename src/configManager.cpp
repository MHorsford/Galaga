#include "configManager.h"


ConfigManager::ConfigManager() {}
ConfigManager::ConfigManager(const string& filename): filename(filename) {}
ConfigManager::ConfigManager(const ConfigManager& copyConfigManager): filename(copyConfigManager.filename), configValue(copyConfigManager.configValue) {}


bool ConfigManager::loadConfig(){
    ifstream file(filename);
    if (!file){
        return false;
    }
    string line;
    while (getline(file, line)){
        istringstream sstream(line);
        string key, value;
        if (getline(sstream, key, '=') && getline(sstream, value)){
            // map
            configValue[key] = value;
        }
    }
    return true;
    
}

bool ConfigManager::saveConfig(){
    ofstream file(filename);
    if (!file){
        return false;
    }
    for (const auto& pair : configValue){
        file << pair.first << "=" << pair.second << "\n";
    }
    return true;
}

void ConfigManager::setValue(const string& key, const string& value){
    configValue[key] = value;
}
string ConfigManager::getValue(const string& key) const {
    auto it = configValue.find(key);
    if (it != configValue.end()) {
        return it -> second;
    } else{
        return "";
    }
}
