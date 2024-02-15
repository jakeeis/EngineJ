#pragma once

#include "EngineJCoreLibs.hpp"
#include "GameEntity.hpp"

#include "MeshComponent.hpp"

namespace EngineJ::core {
    class CharacterEntity : public virtual GameEntity, public virtual MeshComponent {
    public:
        CharacterEntity();
    };
}