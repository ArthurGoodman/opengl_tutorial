set(OPENGL_APP opengl_app)

add_executable(${OPENGL_APP}
    app.cpp
    Display.cpp
    Mesh.cpp
    Shader.cpp
    Texture.cpp
    Utility.cpp
    )

target_include_directories(${OPENGL_APP}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_compile_definitions(${OPENGL_APP}
    PRIVATE GLM_ENABLE_EXPERIMENTAL
    )

target_link_libraries(${OPENGL_APP}
    PRIVATE stb_image
    PRIVATE GLEW::GLEW
    PRIVATE OpenGL::GL
    PRIVATE ${SDL2_LIBRARIES}
    PRIVATE glm
    )
