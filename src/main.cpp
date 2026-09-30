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
    camera.target = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    float cam_yaw = -90.0f;
    float cam_pitch = 0.0f;
    float sensitivity = 0.1f;
    float cam_speed = 5.0f;

    InitWindow(window_width, window_height, window_title.c_str());
    SetTargetFPS(60);

    DisableCursor();

    while(!WindowShouldClose()) {
        /* Mouse input and camera direction */
        Vector2 mouse_delta = GetMouseDelta();

        cam_yaw += mouse_delta.x * sensitivity;
        cam_pitch -= mouse_delta.y * sensitivity;

        if (cam_pitch > 89.0f) cam_pitch = 89.0f;
        if (cam_pitch < -89.0f) cam_pitch = -89.0f;

        float yaw_rad = cam_yaw * DEG2RAD;
        float pitch_rad = cam_pitch * DEG2RAD;

        Vector3 cam_direction = {
            cosf(pitch_rad) * cosf(yaw_rad),
            sinf(pitch_rad),
            cosf(pitch_rad) * sinf(yaw_rad)
        };

        /* Keyboard input */
        Vector3 forward = {
            cosf(yaw_rad),
            0.0f,
            sinf(yaw_rad)
        };

        Vector3 right = {
            -forward.z,
            0.0f,
            forward.x
        };

        float speed = cam_speed * GetFrameTime();

        if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_Q)) camera.position.y -= speed;
        if (IsKeyDown(KEY_E)) camera.position.y += speed;

        camera.target = Vector3Add(camera.position, cam_direction);

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