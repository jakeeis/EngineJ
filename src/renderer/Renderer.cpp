#include "Renderer.hpp"

using namespace EngineJ::renderer;

void MeshGeometry::AddVertex(Vec2 point) {
    vertices.push_back(point.x());
    vertices.push_back(point.y());
}

Renderer::Renderer(std::string canvasSelector) : canvasSelector(canvasSelector) {}

RenderSettings Renderer::InitializeWebGl() {
    static bool staticInit = false;
    if (staticInit) return RenderSettings{};

    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context(canvasSelector.c_str(), &attrs);
    emscripten_webgl_make_context_current(context);

    emscripten_get_canvas_element_size(canvasSelector.c_str(), &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    staticInit = true;
    return RenderSettings{};
}

void Renderer::AddProgram(RenderSettings& settings, std::string& vertexPath, std::string& fragmentPath) {
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexPath);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentPath);

    settings._program = createProgram(vertexShader, fragmentShader);

    settings._positionAttribLoc = glGetAttribLocation(settings._program, "a_position");
}

void Renderer::AddMesh(RenderSettings& settings, MeshGeometry& geometry, MeshMaterial& material) {
    glGenBuffers(1, &settings._positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, settings._positionBuffer);

    settings._numTriangles = geometry.vertices.size() / 2;
    int bufferSize = geometry.vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &geometry.vertices[0], GL_STATIC_DRAW);

    glUseProgram(settings._program);
    glEnableVertexAttribArray(settings._positionAttribLoc);

    glBindBuffer(GL_ARRAY_BUFFER, settings._positionBuffer);

    GLuint size = 2;
    GLuint type = GL_FLOAT;
    GLuint normalize = GL_FALSE;
    GLuint stride = size * sizeof(float);
    void* offset = 0;
    glVertexAttribPointer(settings._positionAttribLoc, size, type, normalize, stride, offset);

    settings._colorUniformLoc = glGetUniformLocation(settings._program, "u_color");
    settings._color = material.color;

    settings._transformUniformLoc = glGetUniformLocation(settings._program, "u_transform");
    settings._transform = geometry.transform;
    settings._transform.Transpose();
}

void Renderer::Render(RenderSettings& settings) {
    glUseProgram(settings._program);
    glEnableVertexAttribArray(settings._positionAttribLoc);
    glBindBuffer(GL_ARRAY_BUFFER, settings._positionBuffer);

    glUniform4f(settings._colorUniformLoc, settings._color.x(), settings._color.y(), settings._color.z(), settings._color.w());
    glUniformMatrix3fv(settings._transformUniformLoc, 1, GL_FALSE, &settings._transform[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, settings._numTriangles);
}

GLuint Renderer::createShader(GLenum shaderType, std::string& shaderPath) {
    std::tuple<char*, int> shaderSource = _readShaderFile(shaderPath);
    const GLchar* sourceString = std::get<0>(shaderSource);
    GLint sourceStringLength = std::get<1>(shaderSource);

    GLuint shader = glCreateShader(shaderType);

    if (shader == 0) {
        return 0;
    }

    glShaderSource(shader, 1, &sourceString, &sourceStringLength);
    glCompileShader(shader);

    _logGLErrors(glGetShaderiv, glGetShaderInfoLog, shader);

    return shader;
}

GLuint Renderer::createProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    _logGLErrors(glGetProgramiv, glGetProgramInfoLog, program);

    return program;
}

std::tuple<char*, int> Renderer::_readShaderFile(std::string& filePath) {
    std::ifstream t(filePath);

    t.seekg(0, std::ios::end);
    int length = t.tellg();

    t.seekg(0, std::ios::beg);
    char* buffer = new char[length];
    t.read(buffer, length);
    t.close();

    return std::tuple<char*, int>(buffer, length);
}

void Renderer::_logGLErrors(LogIvFunction logIv, LogInfoLogFunction logInfoLog, GLuint logObjIndex) {
    int infoLen = 0;

    logIv(logObjIndex, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
        char* infoLog = new char(infoLen);

        logInfoLog(logObjIndex, infoLen, NULL, infoLog);
        printf("GLSL Log: %s\n", infoLog);

        free(infoLog);
    }
}