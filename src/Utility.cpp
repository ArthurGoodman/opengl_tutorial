#include "Utility.hpp"
#include <fstream>
#include <stdexcept>
#include <streambuf>

namespace OpenGLTutorial {

std::string loadFile(const std::string &filename)
{
    std::ifstream file{filename};

    if (!file)
    {
        throw std::runtime_error("unable to read file '" + filename + "'");
    }

    return std::string{(std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>()};
}

} // namespace OpenGLTutorial
