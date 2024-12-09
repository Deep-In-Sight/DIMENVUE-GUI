#include <GL/glew.h>
#include <QOpenGLFramebufferObject>
#include <RasterizerRenderer.h>
#include <iostream>

const char *vertexShaderSource = R"(
#version 450
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment shader source code
const char *fragmentShaderSource = R"(
#version 450
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
}
)";

float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

RasterizerRenderer::RasterizerRenderer()
{
    initialize();
}

void RasterizerRenderer::initialize()
{

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }
    // Build and compile the shader program
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex Shader compilation failed\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment Shader compilation failed\n" << infoLog << std::endl;
    }

    // Link shaders to create a program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);
    // Check for linking errors
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        std::cerr << "Shader Program linking failed\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // Bind the Vertex Array Object
    glBindVertexArray(m_vao);

    // Bind and set the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RasterizerRenderer::render()
{
    glViewport(0, 0, framebufferObject()->width(), framebufferObject()->height());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0); // Unbind VAO
}