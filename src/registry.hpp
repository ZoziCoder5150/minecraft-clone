#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <map>
#include "structs.hpp"

class Registry {
    private:
    std::map<BlockID, RegistryBlock> blocks;
    std::map<TextureID, Texture2D> textures;

    public:
    void register_block(BlockID id, RegistryBlock block);
    RegistryBlock get_block(BlockID id);

    void register_texture(TextureID id, Texture2D texture);
    Texture2D get_texture(TextureID id);
    ~Registry();
};