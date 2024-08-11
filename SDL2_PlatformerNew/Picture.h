#pragma once
#include "common.h"
#include "IRenderer.h"
#include <tuple>

std::tuple<SDL_Texture*, SDL_Rect> CreateTexture(const std::string& path, Uint8 rTransparent, Uint8 gTransparent, Uint8 bTransparent, Uint8 aTransparent);

void DeleteTexture(SDL_Texture* tex);
