#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>


std::string read_file(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return (std::string)buffer.data();
}
