#include "MeshElement.hpp"
#include "EngineJRenderer.hpp"

using namespace EngineJ::core;
using namespace EngineJ::renderer;

MeshElement::MeshElement(ITransformable& parent) : parent(parent)
{
    // Do once:
    static EngineJ::renderer::Renderer renderer("#canvas");
    static bool staticInit = false;
    if (!staticInit) {
        std::string vertexSource = "assets/renderer/shaders/vertex.glsl";
        std::string fragmentSource = "assets/renderer/shaders/fragment.glsl";

        renderSettings = renderer.InitializeWebGl();
        renderer.AddProgram(renderSettings, vertexSource, fragmentSource);

        staticInit = true;
    }

    // Do every time:
    geometry.AddVertex(Vec2{ -0.05, -0.05 });
    geometry.AddVertex(Vec2{ 0.00, 0.05 });
    geometry.AddVertex(Vec2{ 0.05, -0.05 });

    renderer.AddMesh(renderSettings, geometry, material);

    // MeshGeometry geometry{};
// geometry.transform = transform;

// MeshMaterial material(Vec4(1.0, 1.0, 0.5, 1.0));

    renderer.Render(renderSettings);
};