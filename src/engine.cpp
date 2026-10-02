#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "engine.hpp"

void Engine::init_camera(Vector3 start_position, float sensitivity, float speed) {
    this->sensitivity = sensitivity;
    this->cam_speed = speed;
    camera.position = start_position;
    camera.target = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Engine::init_window(int window_width, int window_height, const char * window_title, Color bg_color, int target_fps) {
    this->bg_color = bg_color;
    this->window_height = window_height;
    this->window_width = window_width;
    this->window_title = window_title;

    InitWindow(window_width, window_height, window_title);

    SetTargetFPS(target_fps);
    DisableCursor();
}

void Engine::update() {
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
}

void Engine::render() {
    BeginDrawing();
        ClearBackground(bg_color);
        BeginMode3D(camera);

            DrawSphere(sphere_pos, 5, RED);
            DrawGrid(100, 1.0f);
            
        EndMode3D();
    EndDrawing();
}

Engine::~Engine() {
    CloseWindow();
}