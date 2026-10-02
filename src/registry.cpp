#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include "registry.hpp"

void Registry::register_block(BlockID id, Model block) {
    this->block_models.emplace(id, block);
}

Model Registry::get_block(BlockID id) {
    if (this->block_models.find(id) != this->block_models.end()) {
        return this->block_models[id];
    } else {
        return (Model){0};
    }
}

void Registry::register_texture(Texture2D texture) {
    this->textures.push_back(texture);
}

Registry::~Registry() {
    for (const std::pair<const BlockID, Model> model : this->block_models) {
        UnloadModel(model.second);
    }
    for (Texture2D texture : this->textures) {
        UnloadTexture(texture);
    }
}