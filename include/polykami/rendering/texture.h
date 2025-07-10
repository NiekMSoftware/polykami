//
// Created by niek on 2025/07/10.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

namespace polykami::rendering {

    class Texture {
    public:
        explicit Texture(const std::string& path);
        explicit Texture(const std::vector<std::string>& paths);
        ~Texture();

        // === Non-copyable but moveable ===
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture(Texture&&) noexcept;
        Texture& operator=(Texture&&) noexcept;

        [[nodiscard]] unsigned int getTexture(size_t index = 0) const;
        [[nodiscard]] size_t getTextureCount() const { return textures.size(); }

    private:
        // === Utility ===
        void loadTexture(const std::string& path, unsigned int textureUnit);
        static void setTextureParameters();
        static unsigned int determineFormat(int channels);
        void cleanup();

        std::vector<unsigned int> textures;
        int width{}, height{}, channels{};
    };

}  // polykami::rendering

#endif //TEXTURE_H
