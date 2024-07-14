#include "common.h"
#include "Background.h"

Background::Background(int width, int height, std::string path, SDL_Renderer* renderer)
	: box { 0, 0, width, height }, renderer(renderer) {

	//SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(SDL_LoadBMP(path.c_str()), SDL_FreeSurface);
	texture = SDL_CreateTextureFromSurface(renderer, surface.get());
	//SDL_FreeSurface(surface);
}

Background::~Background() {
	SDL_DestroyTexture(texture);
	std::cout << "Deleted background\n";
}

void Background::Render(SDL_Rect* windowRect) {
	SDL_RenderCopy(renderer, texture, NULL, windowRect);
}

SDL_Texture* Background::GetTexture() {
	return texture;
}
