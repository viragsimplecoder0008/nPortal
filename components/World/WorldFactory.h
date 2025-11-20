#pragma once
#include "IWorld.h"
#include <string>
#include <functional>
#include <map>
#include <memory>

class WorldFactory {
public:
    using WorldCreator = std::function<std::unique_ptr<IWorld>()>;

    static WorldFactory& Instance();

    void RegisterWorld(const std::string& name, WorldCreator creator);
    std::unique_ptr<IWorld> CreateWorld(const std::string& name);

private:
    std::map<std::string, WorldCreator> creators;
};
