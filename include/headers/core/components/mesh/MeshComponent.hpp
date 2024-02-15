#pragma once

#include "EngineJCoreLibs.hpp"
#include "GameComponent.hpp"
#include "MeshElement.hpp"

namespace EngineJ::core {
    using namespace math::matrix;

    class MeshComponent : public GameComponent, public virtual ITransformable {
    public:
        MeshComponent(GameEntity* entityPtr);

        void Render();
        Mat3 GetTransform() { return transform; };

    protected:
        Mat3 transform;
        std::vector<MeshElement> children;
    private:
    };
}