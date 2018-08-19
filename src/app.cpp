#include <exception>
#include <iostream>
#include <GL/glew.h>
#include "Camera.hpp"
#include "Display.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

int main(int /*argc*/, const char ** /*argv*/) try
{
    static constexpr std::size_t c_width = 800;
    static constexpr std::size_t c_height = 600;

    using namespace OpenGLTutorial;

    Display display{c_width, c_height, "My Window"};

    Shader shader{"./res/shader.vert", "./res/shader.frag"};

    // std::vector<Vertex> vertices{
    //     Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 1.0f)},
    //     Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 0.0f)},
    //     Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f)},
    // };

    // std::vector<uint32_t> indices{0, 1, 2};

    // Mesh mesh{vertices, indices};
    Mesh mesh{"./res/teapot.obj"};

    Texture texture{"./res/texture.jpg"};

    Transform transform;
    transform.setScale(glm::vec3{0.075f});

    Camera camera{glm::vec3{0, 0, -3},
                  70.0f,
                  static_cast<float>(c_width) / c_height,
                  0.01f,
                  1000.0f};

    float time = 0.0f;

    while (!display.isClosed())
    {
        display.clear(0.11f, 0.12f, 0.13f, 1.0f);

        shader.bind();
        texture.bind(0);

        transform.getPosition().x = std::sin(time * 1.1f) / 3;
        transform.getPosition().y = std::cos(time * 1.2f) / 3;
        transform.getRotation().x = time * 1.1f;
        transform.getRotation().y = time * 1.2f;
        transform.getRotation().z = time * 1.3f;

        shader.update(transform, camera);
        mesh.draw();

        display.update();

        time += 0.01f;
    }

    return 0;
}
catch (const std::exception &e)
{
    std::cerr << "error: " << e.what() << std::endl;
}
catch (...)
{
    std::cerr << "unknown error occurred" << std::endl;
}
