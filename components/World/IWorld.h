#pragma once

class GraphicsSystem;

class IWorld {
public:
    virtual ~IWorld() {}
    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(GraphicsSystem* graphics) = 0;
};
