#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <cstdint>

typedef std::uint16_t BlockID;
typedef std::uint16_t TextureID;

enum BlockType : std::uint16_t {
    AIR = 0,
    DIRT = 1,
    STONE = 2
};

enum CulledFaces : std::uint8_t {
    CULL_TOP    = 0x1,
    CULL_BOTTOM = 0x2,
    CULL_NORTH  = 0x4,
    CULL_SOUTH  = 0x8,
    CULL_EAST   = 0x10,
    CULL_WEST   = 0x20
};

typedef struct {
    BlockID blocks[16][16][16];
    uint8_t cull[16][16][16];
} Chunk;