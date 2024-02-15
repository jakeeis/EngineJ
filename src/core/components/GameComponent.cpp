#include "GameComponent.hpp"
#include "EngineJCore.hpp"

using namespace EngineJ::core;

TagMap GameComponent::_tagMap;

GameComponent::GameComponent(GameEntity* entityPtr)
{
    addEntity(entityPtr, componentTagList);
}

void GameComponent::addEntity(GameEntity* entityPtr, TagList tagList)
{
    for (TagID tag : tagList) {
        _getEntityList(tag).insert(entityPtr);
    }
}

void GameComponent::removeEntity(GameEntity* entityPtr, TagList tagList)
{
    for (int tag : tagList) {
        _getEntityList(tag).erase(entityPtr);
    }
}

EntityList& GameComponent::_getEntityList(TagID tagId)
{
    return _tagMap[tagId];
}