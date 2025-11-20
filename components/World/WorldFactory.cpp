#include "WorldFactory.h"

WorldFactory& WorldFactory::Instance() {
    static WorldFactory instance;
    return instance;
}

void WorldFactory::RegisterWorld(const std::string& name, WorldCreator creator) {
    creators[name] = creator;
}

std::unique_ptr<IWorld> WorldFactory::CreateWorld(const std::string& name) {
    auto it = creators.find(name);
    if (it != creators.end()) {
        return it->second();
    }
    return nullptr;
}
