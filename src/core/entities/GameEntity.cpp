#include "GameEntity.hpp"
#include "EngineJCore.hpp"

using namespace EngineJ::core;

GameEntity::GameEntity()
{
    components.push_back(new GameComponent(this));
}