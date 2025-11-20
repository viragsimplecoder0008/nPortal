#include "SimpleWorld.h"
#include "../../components/GraphicsSystem/GraphicsSystem.h"
#include "../../components/World/WorldFactory.h"
#include "../../components/ResourceManager/ResourceManager.h"

// Register the world
namespace {
    bool registered = [](){
        WorldFactory::Instance().RegisterWorld("SimpleWorld", []() {
            return std::make_unique<SimpleWorld>();
        });
        return true;
    }();
}

SimpleWorld::SimpleWorld() : angle(0) {}

SimpleWorld::~SimpleWorld() {}

void SimpleWorld::Load() {
    angle = 0;
}

void SimpleWorld::Unload() {
}

void SimpleWorld::Update(float) {
    // Rotation logic handled in physics tick
    angle += 1;
}

void SimpleWorld::Draw(GraphicsSystem* graphics) {
    // Draw Plane (Static)
    const ngl_object* plane = ResourceManager::Instance().GetModel("SimpleWorld_Plane");
    if (plane) {
        glPushMatrix();
        glScale3f(10, 10, 10); // Scale up the plane a bit if needed, though it's already 50x50
        graphics->DrawMesh(plane, false);
        glPopMatrix();
    }

    // Draw Cube (Rotating)
    const ngl_object* cube = ResourceManager::Instance().GetModel("SimpleWorld_Cube");
    if (cube) {
        glPushMatrix();
        glTranslatef(0, 5, 0); // Move it up a bit
        nglRotateY(angle.normaliseAngle());
        glScale3f(5, 5, 5);
        graphics->DrawMesh(cube, false);
        glPopMatrix();
    }
}
