#include "ResourceManager.h"
#include "../../assets/cube.h"

void ResourceManager::LoadAllAssets() {
    // Register Cube
    // We can iterate over the array if we want to register all objects in the file
    // For now, we know there is one object "Cube"
    
    // Note: obj2ngl generates names based on the object name in the .obj file.
    // Here it is "Cube".
    
    RegisterModel("Cube", &obj_Cube);
    
    // If we had more assets, we would include them and register them here.
}
