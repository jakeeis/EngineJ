#pragma once

#include "EngineJCoreLibs.hpp"
#include "GameObject.hpp"

namespace EngineJ::core
{
    class GameEntity;

    typedef IDNum TagID;
    typedef std::unordered_set<EngineJ::core::GameEntity*> EntityList;
    typedef std::vector<TagID> TagList;
    typedef std::unordered_map<TagID, EntityList> TagMap;

    class GameComponent : public GameObject
    {
    public:
        GameComponent(GameEntity* entityPtr);

    protected:
        TagList componentTagList{};

        void addEntity(GameEntity* entityPtr, TagList tagList);
        void removeEntity(GameEntity* entityPtr, TagList tagList);

    private:
        static TagMap _tagMap;

        EntityList& _getEntityList(TagID);
    };
}