#include "TestLevel.h"
#include "../../components/GraphicsSystem/GraphicsSystem.h"
#include "../../components/World/WorldFactory.h"
#include "../../components/ResourceManager/ResourceManager.h"

// Register the world
namespace {
    bool registered = [](){
        WorldFactory::Instance().RegisterWorld("TestLevel", []() {
            return std::make_unique<TestLevel>();
        });
        return true;
    }();
}

TestLevel::TestLevel() : angle(0) {}

TestLevel::~TestLevel() {}

void TestLevel::Load() {
    angle = 0;
}

void TestLevel::Unload() {
}

void TestLevel::Update(float) {
    // Rotation logic handled in physics tick
    angle += 1;
}

void TestLevel::Draw(GraphicsSystem* graphics) {
    glTranslatef(0, 0, 400);
    nglRotateY(angle.normaliseAngle());
    glScale3f(100, 100, 100);

    bool transformed = false;
    const ngl_object* cube = ResourceManager::Instance().GetModel("Cube");
    if (cube) {
        graphics->DrawMesh(cube, transformed);
    }
}
