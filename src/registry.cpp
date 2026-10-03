#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include "registry.hpp"

void Registry::register_block(BlockID id, RegistryBlock block) {
    this->blocks.emplace(id, block);
}

RegistryBlock Registry::get_block(BlockID id) {
    if (this->blocks.find(id) != this->blocks.end()) {
        return this->blocks[id];
    } else {
        return (RegistryBlock){0};
    }
}

void Registry::register_texture(TextureID id, Texture2D texture) {
    this->textures.emplace(id, texture);
}

Texture2D Registry::get_texture(TextureID id) {
    if (this->textures.find(id) != this->textures.end()) {
        return this->textures[id];
    } else {
        return (Texture2D){0};
    }
}

Registry::~Registry() {
    for (std::pair<TextureID, Texture2D> texture : this->textures) {
        UnloadTexture(texture.second);
    }
}