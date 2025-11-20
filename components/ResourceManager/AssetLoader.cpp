#include "ResourceManager.h"
#include "../../assets/cube.h"
#include "../../assets/SimpleWorld_Cube.h"
#include "../../assets/SimpleWorld_Plane.h"

void ResourceManager::LoadAllAssets() {
    // Register Cube (TestLevel)
    RegisterModel("Cube", &obj_Cube);
    
    // Register SimpleWorld assets
    RegisterModel("SimpleWorld_Cube", &SimpleWorld::obj_Cube);
    RegisterModel("SimpleWorld_Plane", &SimpleWorld::obj_Plane);
}
