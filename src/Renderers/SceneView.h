#pragma once

#include "../Core/FrameBuffer.h"
#include "../Core/Camera.h"
#include "../Utils/Time.h"
#include "../Core/Engine/AppWindow.h"
#include "../UI/ViewportShading.h"
#include "../UI/GlobalButtons.h"
#include "Renderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class SceneView {
public:
    bool init(AppWindow* window);
    void render();

    void setCamera(Camera* camera) { this->camera = camera; }
    void setRenderer(Renderer* renderer) {
        this->renderer = renderer;
        renderer->updateShadingParameters(m_ShadingPanel.getParameters());
    }

private:
    Renderer* renderer;
    FrameBuffer framebuffer;
    Camera* camera;
    AppWindow* window;
    glm::vec2 m_ViewportSize;
    ShadingPanel m_ShadingPanel;
    GlobalButtons m_GlobalButtons;

    bool camMode = false;
    bool isSceneWindowHovered = false;
    float lastX = 0, lastY = 0;


    void renderSceneView();
    void renderViewportShading();
    void renderGlobalButtons();

    void processInput();
    void mouseClick();
    void mouse_pos_calc();

};
