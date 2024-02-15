#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <webgl/webgl1.h>

#include "EngineJCoreLibs.hpp"
#include "EngineJMath.hpp"

namespace EngineJ::renderer {
    using namespace EngineJ::math::matrix;

    typedef void (*LogIvFunction)(GLuint, GLenum, GLint*);
    typedef void (*LogInfoLogFunction)(GLuint, GLsizei, GLsizei*, GLchar*);

    struct MeshGeometry {
    public:
        std::vector<float> vertices;
        std::vector<int> indices;
        Mat3 transform = Mat3({
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
            });

        void AddVertex(Vec2 point);
    };

    struct MeshMaterial {
        Vec4 color;

        MeshMaterial(Vec4 color = Vec4()) : color(color) {};
    };

    struct RenderSettings {
    private:
        friend class Renderer;

        GLuint _program;
        GLuint _positionAttribLoc;
        GLuint _positionBuffer;
        GLuint _colorUniformLoc;
        GLuint _transformUniformLoc;

        int _numTriangles;
        Vec4 _color;
        Mat3 _transform;
    };

    class Renderer {
    public:
        Renderer(std::string canvasSelector);

        RenderSettings InitializeWebGl();
        void AddProgram(RenderSettings& settings, std::string& vertexPath, std::string& fragmentPath);
        void AddMesh(RenderSettings& settings, MeshGeometry& geometry, MeshMaterial& material);
        void Render(RenderSettings& settings);
        void Clear(Vec4 color = Vec4{ 0.2, 0.2, 0.2, 1.0 });

    protected:
        const std::string canvasSelector;

        int width;
        int height;

        GLuint createShader(GLenum shaderType, std::string& shaderPath);
        GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

    private:
        std::tuple<char*, int>  _readShaderFile(std::string& filePath);

        void _logGLErrors(LogIvFunction logIv, LogInfoLogFunction logInfoLog, GLuint logObjIndex);
    };
}