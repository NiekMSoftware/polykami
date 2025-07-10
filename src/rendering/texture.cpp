//
// Created by niek on 2025/07/10.
//

#include "polykami/rendering/texture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <format>

namespace polykami::rendering {

    Texture::Texture(const std::string &path) {
        loadTexture(path, 0);
    }

    Texture::Texture(const std::vector<std::string> &paths) {
        // load in textures
        textures.reserve(paths.size());
        for (size_t i = 0; i < paths.size(); ++i) {
            loadTexture(paths[i], static_cast<unsigned int>(i));
        }
    }

    Texture::~Texture() {
        cleanup();
    }

    Texture::Texture(Texture&& other) noexcept
        : textures(std::move(other.textures))
        , width(other.width)
        , height(other.height)
        , channels(other.channels) {
        other.width = 0;
        other.height = 0;
        other.channels = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept {
        if (this != &other) {
            cleanup();

            textures = std::move(other.textures);
            width = other.width;
            height = other.height;
            channels = other.channels;

            other.width = 0;
            other.height = 0;
            other.channels = 0;
        }
        return *this;
    }

    unsigned int Texture::getTexture(const size_t index) const {
        if (index >= textures.size()) {
            std::cerr << "Texture index out of range.\n";
            return 0;
        }
        return textures[index];
    }

    void Texture::loadTexture(const std::string &path, const unsigned int textureUnit) {
        if (!std::filesystem::exists(path)) {
            const std::string msg = std::format("Try retrieving image from {} - FAILED", path);
            std::cerr << msg << '\n';
            return;
        }
        glActiveTexture(GL_TEXTURE0 + textureUnit);

        unsigned int tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        setTextureParameters();

        // load image data
        int imageWidth, imageHeight, imageChannels;
        unsigned char* data = stbi_load(path.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
        if (!data) {
            glDeleteTextures(1, &tex);
            const std::string msg = std::format(
                "Loading image '{}' failed: {}",
                path,
                stbi_failure_reason()
            );
            std::cerr << msg << '\n';
            return;
        }

        // store dimensions from first texture
        if (textures.empty()) {
            width = imageWidth;
            height = imageHeight;
            channels = imageChannels;
        }

        // determine format and upload texture
        const GLenum format = determineFormat(imageChannels);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(format), imageWidth, imageHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);  // release resources
        textures.emplace_back(tex);  // store texture ID
    }

    void Texture::setTextureParameters() {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    unsigned int Texture::determineFormat(const int channels) {
        switch (channels) {
            case 1: return GL_RED;
            case 3: return GL_RGB;
            case 4: return GL_RGBA;
            default: {
                std::cerr << "Unsupported channel count: " << channels << '\n';
                return 0;
            }
        }
    }

    void Texture::cleanup() {
        for (unsigned int texture : textures) {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
        }
        textures.clear();
    }

}  // polykami::rendering