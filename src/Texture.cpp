#include "Texture.hpp"
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include "stb_image/stb_image.h"

namespace OpenGLTutorial {

Texture::Texture(const std::string &filename)
{
    int width, height, channels;

    std::uint8_t *image_data =
        stbi_load(filename.c_str(), &width, &height, &channels, 4);

    if (nullptr == image_data)
    {
        throw std::runtime_error("unable to load texture '" + filename + "'");
    }

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image_data);

    stbi_image_free(image_data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::bind(std::uint32_t unit)
{
    assert(unit < 32);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

} // namespace OpenGLTutorial
