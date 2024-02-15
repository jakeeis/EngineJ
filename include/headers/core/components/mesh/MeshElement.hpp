#pragma once

#include "EngineJCoreLibs.hpp"
#include "EngineJMath.hpp"
#include "EngineJRenderer.hpp"

namespace EngineJ::core {
    using namespace EngineJ::math::matrix;

    using renderer::MeshGeometry;
    using renderer::MeshMaterial;
    using renderer::RenderSettings;

    class ITransformable {
    public:
        virtual ~ITransformable() {};

        void SetLocalTransform(Mat3 mat) { localTransform = mat; /*setGlobalTransform();*/ };

        Mat3& GetLocalTransform() { return localTransform; };
        Mat3& GetGlobalTransform() { return globalTransform; };
    protected:
        Mat3 localTransform;
        Mat3 globalTransform;

        // virtual void setGlobalTransform() = 0;
    };

    class MeshElement : public virtual ITransformable {
    public:
        MeshGeometry geometry;
        MeshMaterial material;

        MeshElement(ITransformable& parent);
    protected:
        RenderSettings renderSettings;

        ITransformable& parent;
        std::vector<MeshElement> children;

        virtual void setGlobalTransform() { globalTransform = parent.GetGlobalTransform() * GetLocalTransform(); };
    private:
    };
}