#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "structs.hpp"
#include "registry.hpp"

class Engine {
    private:

    int window_height;
    int window_width;
    std::string window_title;
    Color bg_color;
    Camera3D camera = { 0 };
    Vector3 sphere_pos = (Vector3) {0.0f, 0.0f, 0.0f};
    float cam_yaw = -90.0f;
    float cam_pitch = 0.0f;
    float sensitivity;
    float cam_speed;
    Registry *registry;

    public:
    Engine(class Registry *registry);
    ~Engine();

    void init_camera(Vector3 start_position, float sensitivity, float speed);
    void init_window(int window_width, int window_height, const char * window_title, Color bg_color, int target_fps);

    void update();

    void begin_rendering();
    void begin_3d_mode();

    void render_chunk(const Chunk * chunk, Vector3 position);
    void render_hud();

    void end_3d_mode();
    void finish_rendering();
};