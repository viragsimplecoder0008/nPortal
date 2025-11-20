#include "ResourceManager.h"
#include "../Logger/Logger.h"

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::RegisterModel(const std::string& name, const ngl_object* model) {
    models[name] = model;
    Logger::printf("Registered model: %s\n", name.c_str());
}

const ngl_object* ResourceManager::GetModel(const std::string& name) {
    auto it = models.find(name);
    if (it != models.end()) {
        return it->second;
    }
    Logger::printf("Error: Model not found: %s\n", name.c_str());
    return nullptr;
}

void ResourceManager::RegisterTexture(const std::string& name, const TEXTURE* texture) {
    textures[name] = texture;
}

const TEXTURE* ResourceManager::GetTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}
