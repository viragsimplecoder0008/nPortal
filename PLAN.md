# nPortal Development Plan

This document outlines the steps required to transform the current engine into a fully feature-complete Source-like engine capable of running a Portal clone.

## Phase 1: Core Engine Architecture
- [x] **World Management**: Implement `IWorld` interface and `WorldFactory` for level loading.
- [x] **Asset Pipeline**: Create tools to split and process OBJ files into engine-ready headers (`split_obj.py`).
- [x] **Entity System**: Implement an Entity-Component-System (ECS) or a classic GameObject hierarchy to manage objects in the world.
- [x] **Resource Manager**: Centralized loading and caching of textures, models, and sounds.

## Phase 2: Physics & Collision
- [ ] **Collision Detection**: Implement AABB (Axis-Aligned Bounding Box) and OBB (Oriented Bounding Box) collision.
- [ ] **Raycasting**: Essential for portal gun mechanics and interaction.
- [ ] **Rigid Body Dynamics**: Basic physics for movable objects (cubes, turrets).
- [ ] **Character Controller**: Refine `PlayerController` for smooth movement, jumping, and collision response (Source-engine style air strafing).

## Phase 3: Portal Mechanics
- [ ] **Portal Rendering**: Implement stencil buffer or render-to-texture techniques to draw portal views.
- [ ] **Teleportation**: Logic to seamlessly transport the player and objects between portals.
- [ ] **Momentum Preservation**: Ensure velocity is rotated and preserved upon exiting a portal.
- [ ] **Recursive Rendering**: Handle portals looking into other portals (limit recursion depth).

## Phase 4: Graphics & Visuals
- [ ] **Lighting**: Implement dynamic lighting and baked lightmaps.
- [ ] **Shaders**: Support for normal maps, specular highlights, and portal effects.
- [ ] **Camera System**: robust camera handling, including view bobbing and portal transitions.

## Phase 5: Gameplay Elements
- [ ] **Portal Gun**: Model, animation, and firing logic.
- [ ] **Interactables**: Weighted Storage Cubes, Buttons, Doors, Elevators.
- [ ] **Triggers**: Areas that trigger events (level transitions, dialogue).
- [x] **Audio**: Not needed (Nspire has no speaker).

## Phase 6: Content & Polish
- [ ] **Level Format**: Define a file format for levels (or stick to code-based loading for now, but data-driven is better).
- [ ] **UI/HUD**: Crosshair, portal indicators, menus.
- [ ] **Optimization**: Frustum culling, occlusion culling.

## Next Immediate Steps
1.  Integrate `split_obj.py` into the build process.
2.  Implement a basic `TestWorld` in `worlds/Testlvl` using the new `IWorld` interface.
3.  Implement basic AABB collision for the player against the static world.
