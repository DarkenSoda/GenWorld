#pragma once

#include <GLFW/glfw3.h>

namespace Utils {
    class Time {
    public:
        static void Update() { CalculateTime(); }
        static float deltaTime;
        static float time;
        static float frameRate;

    private:
        static void CalculateTime() { GetTime(); CalculateDeltaTime(); CalculateFrameRate(); }
        static void GetTime();
        static void CalculateDeltaTime();
        static void CalculateFrameRate();

        static int frameCount;
        static float lastTime;
        static float lastFrameRateTime;

    };
}