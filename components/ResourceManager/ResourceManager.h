#pragma once

#include <map>
#include <string>
#include "../../nGL/gldrawarray.h"
#include "../../nGL/gl.h"

class ResourceManager {
public:
    static ResourceManager& Instance();

    void RegisterModel(const std::string& name, const ngl_object* model);
    const ngl_object* GetModel(const std::string& name);

    void RegisterTexture(const std::string& name, const TEXTURE* texture);
    const TEXTURE* GetTexture(const std::string& name);

    void LoadAllAssets(); // Called at startup to register everything

private:
    ResourceManager() = default;
    
    std::map<std::string, const ngl_object*> models;
    std::map<std::string, const TEXTURE*> textures;
};
