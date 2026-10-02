#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <cstdint>

typedef std::uint16_t Block;

enum BlockType : std::uint16_t {
    AIR = 0,
    DIRT = 1,
    STONE = 2
};

typedef struct {
    Block blocks[16][16][16];
} Chunk;