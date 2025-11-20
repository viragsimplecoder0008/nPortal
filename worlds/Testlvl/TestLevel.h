#pragma once
#include "../../components/World/IWorld.h"
#include "../../nGL/gl.h"

class TestLevel : public IWorld {
public:
    TestLevel();
    ~TestLevel() override;
    void Load() override;
    void Unload() override;
    void Update(float deltaTime) override;
    void Draw(GraphicsSystem* graphics) override;

private:
    GLFix angle;
};
