#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../Renderers/UiContext.h"
#include "../../Renderers/SceneView.h"
#include "../../Renderers/Renderer.h"
#include "../../Controllers/GeneratorController.h"
#include "../../Utils/Time.h"
#include "../../Utils/Exporter/MeshExporter.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../ShaderManager.h"
#include "AppWindow.h"

class TerrainController;
class BlockController;
class GeneratorController;

class Application {
public:
    void Run();

    static Application* GetInstance() {
        if (_instance == nullptr) {
            _instance = new Application();
        }
        return _instance;
    }

    AppWindow* GetWindow() const { return m_window; }
    void Generate();
    void RandomizeSeed();
    void Export(const std::string& format);
    void Quit() { m_isRunning = false; }

private:
    Application();
    ~Application();

    void init();
    void CheckGenerationMode();
    void shutdown();
    void LoadDefaultShaders();

    static Application* _instance;

    bool m_isRunning = true;

    int current_mode;

    AppWindow* m_window;
    Camera camera = Camera(glm::vec3(0.0f, 75.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f);
    Renderer renderer;
    SceneView sceneView;
    UiContext uiCtx;
    GeneratorController* generatorController = nullptr;

    BlockController* blockController = nullptr;
    TerrainController* terrainController = nullptr;

    friend int main(void);
};
