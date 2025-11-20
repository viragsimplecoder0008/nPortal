# Level Creation Workflow

This document outlines the process of importing a 3D model (OBJ format) into the nPortal engine and setting it up as a playable world.

## 1. Prepare the 3D Model
*   Create your level in Blender or another 3D modeling tool.
*   Ensure the model is triangulated or composed of quads (nGL supports both, but triangles are safer).
*   Export the scene as a Wavefront `.obj` file.
    *   Include Normals and UVs.
    *   **Important**: Separate distinct objects (walls, floor, props) using object names in Blender. The exporter should write `o ObjectName` lines.

## 2. Convert OBJ to Engine Headers
Use the `split_obj.py` tool to process the OBJ file. This tool splits the OBJ into separate files based on object names and converts each into a C++ header file compatible with nGL.

```bash
python3 nGL/tools/split_obj.py path/to/your_level.obj
```

This will generate `.h` files in the same directory as the input OBJ. For example, if your OBJ has objects named `Floor` and `Wall`, you will get `Floor.h` and `Wall.h`.

## 3. Move and Rename Assets
Move the generated header files to the `assets/` directory. It is good practice to rename them to avoid collisions (e.g., `Level1_Floor.h`).

```bash
mv Floor.h assets/Level1_Floor.h
mv Wall.h assets/Level1_Wall.h
```

## 4. Fix Namespace/Symbol Collisions (Optional but Recommended)
The generated headers define global variables like `obj_Floor`. If you have multiple levels with objects named "Floor", these will collide.
Wrap the content of the header in a namespace or rename the variables manually.

**Example `assets/Level1_Floor.h`:**
```cpp
namespace Level1 {
    // ... generated content ...
    static const ngl_object *objs_Floor_h[] __attribute__((unused)) = { &obj_Floor };
}
```

## 5. Register Assets
Open `components/ResourceManager/AssetLoader.cpp` and register the new models in `LoadAllAssets()`.

```cpp
#include "../../assets/Level1_Floor.h"
#include "../../assets/Level1_Wall.h"

void ResourceManager::LoadAllAssets() {
    // ... existing assets ...
    RegisterModel("Level1_Floor", &Level1::obj_Floor);
    RegisterModel("Level1_Wall", &Level1::obj_Wall);
}
```

## 6. Create the World Class
Create a new folder in `worlds/` (e.g., `worlds/Level1/`) and create a class that implements `IWorld`.

**`Level1.h`**:
```cpp
#pragma once
#include "../../components/World/IWorld.h"

class Level1 : public IWorld {
public:
    void Load() override;
    void Unload() override;
    void Update(float deltaTime) override;
    void Draw(GraphicsSystem* graphics) override;
};
```

**`Level1.cpp`**:
```cpp
#include "Level1.h"
#include "../../components/World/WorldFactory.h"
#include "../../components/ResourceManager/ResourceManager.h"

// Register with Factory
namespace {
    bool registered = [](){
        WorldFactory::Instance().RegisterWorld("Level1", []() { return std::make_unique<Level1>(); });
        return true;
    }();
}

void Level1::Load() { /* Setup logic */ }
void Level1::Unload() { /* Cleanup logic */ }
void Level1::Update(float dt) { /* Game logic */ }

void Level1::Draw(GraphicsSystem* graphics) {
    // Draw your registered models
    auto* floor = ResourceManager::Instance().GetModel("Level1_Floor");
    if (floor) graphics->DrawMesh(floor, false);
}
```

## 7. Load the World
You can now load the world using `WorldFactory::Instance().CreateWorld("Level1")` in your game logic (e.g., in `main.cpp` or a level manager).
