#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tassathras
{
    class IsometricCamera {
    public:
        IsometricCamera(float tileWidth, float tileHeight, float screenWidth, float screenHeight, float zoom = 1.0f);

        void setPosition(const glm::vec2& worldPos);
        void move(const glm::vec2& delta);  
        void setZoom(float zoomLevel);
        void zoom(float delta);  

        glm::vec2 worldToScreen(float worldX, float worldY, float worldZ = 0.0f) const;  // Для отрисовки тайлов
        glm::vec2 screenToWorld(float screenX, float screenY) const;  // Для кликов мыши
        glm::mat4 getViewProjectionMatrix() const;


        inline const glm::vec2& getPosition() const { return m_WorldPosition; }
        inline float getZoom() const { return m_Zoom; }
        inline float getTileWidth() const { return m_TileWidth; }
        inline float getTileHeight() const { return m_TileHeight; }

        struct Bounds {
            float minWorldX;
            float maxWorldX;
            float minWorldY;
            float maxWorldY;
        };
        Bounds getVisibleBounds() const;

    private:
        glm::vec2 m_WorldPosition;  
        float m_TileWidth;
        float m_TileHeight;
        float m_Zoom;

        float m_ScreenWidth;
        float m_ScreenHeight;

        float m_IsoTileWidth;
        float m_IsoTileHeight;
    };
}