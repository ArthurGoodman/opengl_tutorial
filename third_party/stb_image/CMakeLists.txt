add_library(stb_image
    stb_image.c
    )

target_include_directories(stb_image
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_compile_definitions(stb_image
    PRIVATE STB_IMAGE_IMPLEMENTATION
    )

target_compile_options(stb_image
    PRIVATE "-Wno-conversion"
    PRIVATE "-Wno-unused-parameter"
    )
