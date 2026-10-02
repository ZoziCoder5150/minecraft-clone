#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "structs.hpp"

class Engine {
    private:

    int window_height;
    int window_width;
    std::string window_title;
    std::string res_dir;
    Color bg_color;
    Camera3D camera = { 0 };
    Vector3 sphere_pos = (Vector3) {0.0f, 0.0f, 0.0f};
    float cam_yaw = -90.0f;
    float cam_pitch = 0.0f;
    float sensitivity;
    float cam_speed;

    Texture2D dirt_texture = {0};
    Texture2D stone_texture = {0};
    Model dirt_model = {0};
    Model stone_model = {0};

    public:

    void init_camera(Vector3 start_position, float sensitivity, float speed);
    void init_window(int window_width, int window_height, const char * window_title, Color bg_color, int target_fps);

    void update();
    void begin_rendering();
    void render_chunk(const Chunk * chunk, Vector3 position);
    void finish_rendering();

    void load_res(const char * res_dir);

    ~Engine();
};