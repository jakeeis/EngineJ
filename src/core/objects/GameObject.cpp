#include "EngineJCore.hpp"
#include "GameObject.hpp"

using namespace EngineJ::core;

GameObject::GameObject() : id(_generateId())
{
    std::cout << id << '\n';
}

IDNum GameObject::_generateId() const
{
    static std::random_device rd;
    static std::mt19937_64 mt(rd());

    return mt();
}