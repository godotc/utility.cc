/**
 * @ Author: godot42
 * @ Create Time: 2024-08-02 10:47:59
 * @ Modified by: @godot42
 * @ Modified time: 2025-03-07 16:34:28
 * @ Description:
 */


#include "utility/file_utils.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>


namespace ut
{
namespace file
{

std::optional<std::string> read_all(const std::filesystem::path &filepath)
{
    static constexpr size_t FILE_MAX_SIZE = 1024 * 1024 * 128; // 128 MB

    // Open the file
    std::ifstream f(filepath, std::ios::binary | std::ios::ate);
    if (!f.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return {};
    }

    // Get the size of the file
    std::streamsize file_size = f.tellg();
    f.seekg(0, std::ios::beg);
    if (file_size > FILE_MAX_SIZE) {
        std::cerr << "File is too large: " << filepath << std::endl;
        return {};
    }


    // Allocate memory to store the file content
    std::string buffer;
    buffer.resize(file_size);

    // Read the file content into the allocated memory
    if (!f.read(buffer.data(), file_size)) {
        std::cerr << "Failed to read file: " << filepath << std::endl;
        return {};
    }

    // Close the file
    f.close();

    return std::move(buffer);
}

bool is_image(const std::filesystem::path &filepath)
{
    // TODO: read binary file type
    auto ext = filepath.filename().extension();
    return ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp";
}

std::optional<size_t> get_content_hash(const std::filesystem::path &filepath)
{
    if (auto content = ut::file::read_all(filepath)) {
        return ut::file::get_hash(*content);
    }
    return {};
}

std::optional<size_t> get_hash(const std::string &text)
{
#if 1
    std::hash<std::string> hasher;
    auto                   value = hasher(text);
    return value;

#else
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX    sha256;
    SHA256_Init(&sha256);

    std::ifstream shaderFile(shaderFilePath, std::ios::binary);
    if (!shaderFile.is_open()) {
        // Handle error
    }

    char buffer[4096];
    while (shaderFile.read(buffer, 4096)) {
        SHA256_Update(&sha256, buffer, shaderFile.gcount());
    }
    SHA256_Update(&sha256, buffer, shaderFile.gcount());
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        char hex[3];
        sprintf(hex, "%02x", hash[i]);
        shaderHash += hex;
    }
#endif

    return {};
}

} // namespace file

} // namespace ut
