#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "engine.hpp"

int main(int argc, char ** argv) {
    Engine engine;

    engine.init_camera((Vector3){0.0f, 0.0f, 0.0f}, 0.1f, 5.0f);
    engine.init_window(640, 360, "Minecraft Clone", {134, 219, 255, 255}, 60);

    while(!WindowShouldClose()) {
        engine.update();
        engine.render();
    }

    return 0;
}