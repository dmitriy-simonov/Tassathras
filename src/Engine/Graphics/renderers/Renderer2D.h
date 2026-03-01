#pragma once
#include "Graphics/Texture.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <array>

namespace Tassathras {

    struct QuadVertex {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec4 color;
        float texIndex;
    };

    struct Quad {
        QuadVertex vertices[4];
        float getZ() const { return vertices[0].position.z; }
    };

    class Renderer2D {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const glm::mat4& viewProjectionMatrix);
        static void endScene();

        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f);

        static void drawQuadIsometric(const glm::vec2& screenPos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float zOrder = 0.0f);

        static void drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
        static void drawRect(const glm::vec2& min, const glm::vec2& max, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

        static void setSortingEnabled(bool enabled) { s_SortingEnabled = enabled; }

    private:
        static void flush();
        static void startBatch();
        static void nextBatch();

    private:
        static bool s_SortingEnabled;
    };
}

