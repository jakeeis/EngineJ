#pragma once

#include "EngineJCoreLibs.hpp"

namespace EngineJ::core
{
    typedef int IDNum;

    class GameObject
    {
    public:
        GameObject();

    protected:
        IDNum id;
        IDNum _generateId() const;
    };
}