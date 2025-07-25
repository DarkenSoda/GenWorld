#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include "../Core/Engine/AppWindow.h"


class IRenderContext {
public:
    IRenderContext() : window(nullptr) {}
    virtual ~IRenderContext() = default;

    virtual bool init(AppWindow* window) = 0;
    virtual void shutdown() = 0;

    virtual void preRender() = 0;
    virtual void render() = 0;
    virtual void postRender() = 0;

protected:
    AppWindow* window;

};
