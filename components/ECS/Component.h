#pragma once

class GameObject;

class Component {
public:
    virtual ~Component() {}
    
    virtual void Start() {}
    virtual void Update(float) {}
    virtual void Draw() {}

    void SetOwner(GameObject* owner) { gameObject = owner; }
    GameObject* GetOwner() const { return gameObject; }

protected:
    GameObject* gameObject = nullptr;
};
