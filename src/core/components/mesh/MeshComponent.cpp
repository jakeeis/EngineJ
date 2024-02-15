#include "MeshComponent.hpp"
#include "EngineJCore.hpp"

using namespace EngineJ::core;

MeshComponent::MeshComponent(GameEntity* entityPtr) : GameComponent(entityPtr) {
    transform = Mat3{
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    };

    MeshElement element(*this);
    // children.push_back(element);
};