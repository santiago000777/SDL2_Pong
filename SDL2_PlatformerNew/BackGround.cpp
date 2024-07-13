#include "common.h"
#include "BackGround.h"

BackGround::BackGround(int width, int height, std::string path, SDL_Renderer* renderer)
	: box { 0, 0, width, height }, renderer(renderer) {

	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

BackGround::~BackGround() {
	SDL_DestroyTexture(texture);
	std::cout << "Deleted background\n";
}

void BackGround::Render(SDL_Rect* windowRect) {
	SDL_RenderCopy(renderer, texture, NULL, windowRect);
}

SDL_Texture* BackGround::GetTexture() {
	return texture;
}
