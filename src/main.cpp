#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>

int main(int argc, char ** argv) {
    int window_height = 360;
    int window_width = 640;
    std::string window_title = "Minecraft clone";
    Color bg_color = {134, 219, 255, 255};
    Vector3 start_position = {0.0f, 0.0f, 0.0f};
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    float cam_yaw = 0.0f;
    float cam_pitch = 0.0f;

    InitWindow(window_width, window_height, window_title.c_str());
    SetTargetFPS(60);

    DisableCursor();

    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyDown(KEY_W)) camera.position.x += 2.0f;
        if (IsKeyDown(KEY_S)) camera.position.x -= 2.0f;
        if (IsKeyDown(KEY_A)) camera.position.z -= 2.0f;
        if (IsKeyDown(KEY_D)) camera.position.z += 2.0f;
        if (IsKeyDown(KEY_Q)) camera.position.y += 2.0f;
        if (IsKeyDown(KEY_E)) camera.position.y -= 2.0f;

        BeginDrawing();
            ClearBackground(bg_color);
            BeginMode3D(camera);

                DrawSphere(start_position, 5, RED);
                DrawGrid(100, 1.0f);
                
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}