#pragma once

#include "EngineJCoreLibs.hpp"
#include "GameObject.hpp"

namespace EngineJ::core
{
    class GameComponent;

    class GameEntity : public GameObject
    {
    public:
        friend class GameComponent;

        GameEntity();

        void InitComponents();

    protected:
        std::vector<GameComponent*> components{};
    };
}