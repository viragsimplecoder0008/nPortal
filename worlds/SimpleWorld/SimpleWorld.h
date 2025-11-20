#pragma once
#include "../../components/World/IWorld.h"
#include "../../nGL/gl.h"

class SimpleWorld : public IWorld {
public:
    SimpleWorld();
    ~SimpleWorld() override;
    void Load() override;
    void Unload() override;
    void Update(float deltaTime) override;
    void Draw(GraphicsSystem* graphics) override;

private:
    GLFix angle;
};
