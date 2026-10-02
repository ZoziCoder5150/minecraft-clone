#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "engine.hpp"

namespace fs = std::filesystem;

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

void Engine::begin_rendering() {
    BeginDrawing();
    ClearBackground(bg_color);
    
}

void Engine::begin_3d_mode() {
    BeginMode3D(this->camera);
    //DrawSphere(sphere_pos, 5, RED);
    DrawGrid(100, 1.0f);
}

void Engine::render_chunk(const Chunk *chunk, Vector3 position) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                Vector3 block_position = Vector3Add(position, (Vector3){i,16-j,k});
                if (chunk->blocks[i][j][k] == STONE) {
                    DrawModel(this->stone_model, block_position, 1.0f, WHITE);
                } else if (chunk->blocks[i][j][k] == DIRT) {
                    DrawModel(this->dirt_model, block_position, 1.0f, WHITE);
                }
            }
        }
    }
}

void Engine::end_3d_mode() {
    EndMode3D();
}

void Engine::render_hud() {
    Vector3 cam_dir = Vector3Subtract(this->camera.position, this->camera.target);
    Vector3 forward = Vector3Normalize(cam_dir);

    if (std::abs(forward.x) > std::abs(forward.z)) {
        if (forward.x < 0) { 
            DrawText("Facing west (-X)", 5, 5, 24, BLACK);
        } else {
            DrawText("Facing east (+X)", 5, 5, 24, BLACK);
        }
    } else {
        if (forward.z < 0) { 
            DrawText("Facing north (-Z)", 5, 5, 24, BLACK);
        } else {
            DrawText("Facing south (+Z)", 5, 5, 24, BLACK);
        }
    }
}

void Engine::finish_rendering() {
    EndDrawing();
}

void Engine::load_res(const char * res_dir) {
    this->res_dir = res_dir;

    fs::path stone_path = fs::path(res_dir) / "stone.png";
    fs::path dirt_path = fs::path(res_dir) / "dirt.png";

    this->stone_texture = LoadTexture(stone_path.c_str());
    this->dirt_texture = LoadTexture(dirt_path.c_str());

    Mesh block_mesh = GenMeshCube(1.0f, 1.0f, 1.0f);

    this->stone_model = LoadModelFromMesh(block_mesh);
    this->dirt_model = LoadModelFromMesh(block_mesh);

    this->stone_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->stone_texture;
    this->dirt_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->dirt_texture;
}

Engine::~Engine() {
    CloseWindow();
    UnloadModel(this->stone_model);
    UnloadModel(this->dirt_model);

    UnloadTexture(this->stone_texture);
    UnloadTexture(this->dirt_texture);
}