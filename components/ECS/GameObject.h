#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "Component.h"
#include "Transform.h"

class GameObject {
public:
    Transform transform;

    virtual ~GameObject() = default;

    virtual void Start() {
        for (auto& comp : components) {
            comp->Start();
        }
    }

    virtual void Update(float deltaTime) {
        for (auto& comp : components) {
            comp->Update(deltaTime);
        }
    }

    virtual void Draw() {
        for (auto& comp : components) {
            comp->Draw();
        }
    }

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->SetOwner(this);
        T* ptr = comp.get();
        components.push_back(std::move(comp));
        ptr->Start(); // Optionally call Start immediately or wait
        return ptr;
    }

    template <typename T>
    T* GetComponent() {
        for (auto& comp : components) {
            if (T* ptr = dynamic_cast<T*>(comp.get())) {
                return ptr;
            }
        }
        return nullptr;
    }

protected:
    std::vector<std::unique_ptr<Component>> components;
};
