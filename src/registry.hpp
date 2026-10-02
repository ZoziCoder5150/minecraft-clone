#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "structs.hpp"

class Registry {
    private:
    std::map<BlockID, Model> block_models;
    std::vector<Texture2D> textures;

    public:
    void register_block(BlockID id, Model block);
    Model get_block(BlockID id);

    void register_texture(Texture2D texture);
    ~Registry();
};