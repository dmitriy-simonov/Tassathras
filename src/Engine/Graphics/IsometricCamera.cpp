#include "IsometricCamera.h"
#include <algorithm>
#include <cmath>

namespace Tassathras
{
    IsometricCamera::IsometricCamera(float tileWidth, float tileHeight, float screenWidth, float screenHeight, float zoom)
        : m_TileWidth(tileWidth)
        , m_TileHeight(tileHeight)
        , m_ScreenWidth(screenWidth)
        , m_ScreenHeight(screenHeight)
        , m_Zoom(zoom)
        , m_WorldPosition(0.0f, 0.0f)
    {
        m_IsoTileWidth = m_TileWidth / 2.0f;
        m_IsoTileHeight = m_TileHeight / 2.0f;
    }

    void IsometricCamera::setPosition(const glm::vec2& worldPos) {
        m_WorldPosition = worldPos;
    }

    void IsometricCamera::move(const glm::vec2& delta) {
        m_WorldPosition += delta;
    }

    void IsometricCamera::setZoom(float zoomLevel) {
        m_Zoom = std::clamp(zoomLevel, 0.1f, 5.0f);
    }

    void IsometricCamera::zoom(float delta) {
        setZoom(m_Zoom + delta);
    }

    glm::vec2 IsometricCamera::worldToScreen(float worldX, float worldY, float worldZ) const {
        float isoX = (worldX - worldY) * m_IsoTileWidth;
        float isoY = (worldX + worldY) * m_IsoTileHeight - worldZ * m_TileHeight;

        isoX *= m_Zoom;
        isoY *= m_Zoom;

        float cameraScreenX = (m_WorldPosition.x - m_WorldPosition.y) * m_IsoTileWidth * m_Zoom;
        float cameraScreenY = (m_WorldPosition.x + m_WorldPosition.y) * m_IsoTileHeight * m_Zoom;

        float screenX = isoX - cameraScreenX + m_ScreenWidth / 2.0f;
        float screenY = isoY - cameraScreenY + m_ScreenHeight / 2.0f;

        return { screenX, screenY };
    }

    glm::vec2 IsometricCamera::screenToWorld(float screenX, float screenY) const {
        float cameraScreenX = (m_WorldPosition.x - m_WorldPosition.y) * m_IsoTileWidth * m_Zoom;
        float cameraScreenY = (m_WorldPosition.x + m_WorldPosition.y) * m_IsoTileHeight * m_Zoom;

        float worldScreenX = screenX - m_ScreenWidth / 2.0f + cameraScreenX;
        float worldScreenY = screenY - m_ScreenHeight / 2.0f + cameraScreenY;

        worldScreenX /= m_Zoom;
        worldScreenY /= m_Zoom;

        float x = (worldScreenX / m_IsoTileWidth + worldScreenY / m_IsoTileHeight) / 2.0f;
        float y = (worldScreenY / m_IsoTileHeight - worldScreenX / m_IsoTileWidth) / 2.0f;

        return { x, y };
    }

    IsometricCamera::Bounds IsometricCamera::getVisibleBounds() const {
        glm::vec2 topLeft = screenToWorld(0, 0);
        glm::vec2 topRight = screenToWorld(m_ScreenWidth, 0);
        glm::vec2 bottomLeft = screenToWorld(0, m_ScreenHeight);
        glm::vec2 bottomRight = screenToWorld(m_ScreenWidth, m_ScreenHeight);

        Bounds bounds;
        bounds.minWorldX = std::min({ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x });
        bounds.maxWorldX = std::max({ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x });
        bounds.minWorldY = std::min({ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y });
        bounds.maxWorldY = std::max({ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y });

        float paddingX = 2.0f;
        float paddingY = 2.0f;
        bounds.minWorldX -= paddingX;
        bounds.maxWorldX += paddingX;
        bounds.minWorldY -= paddingY;
        bounds.maxWorldY += paddingY;

        return bounds;
    }

    glm::mat4 IsometricCamera::getViewProjectionMatrix() const {
        glm::mat4 projection = glm::ortho(0.0f, m_ScreenWidth, m_ScreenHeight, 0.0f, -100.0f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_WorldPosition.x, -m_WorldPosition.y, 0.0f));
        return projection * view;
    }
}