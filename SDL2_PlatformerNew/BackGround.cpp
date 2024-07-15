#include "common.h"
#include "Background.h"
#include "Renderer.h"

Background::Background(int width, int height, std::string path)
	: box { 0, 0, width, height } {

	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	
	texture = SDL_CreateTextureFromSurface(SRenderer::Get().Renderer(), surface);
	//std::make_u
	SDL_FreeSurface(surface);
}

//Background::Background(const Background& rhs) {
//	this->box = rhs.box;
//
//	this->renderer = rhs.renderer;
//	this->texture = rhs.texture;
//}
//
//Background::Background(Background&& rhs) {
//	this->box = rhs.box;
//
//	this->renderer = rhs.renderer;
//	rhs.renderer = NULL;
//	this->texture = rhs.texture;
//	rhs.texture = NULL;
//}
//
//void Background::operator=(const Background& rhs) {
//	this->box = rhs.box;
//
//	this->renderer = rhs.renderer;
//	this->texture = rhs.texture;
//}
//
//void Background::operator=(Background&& rhs) {
//	this->box = rhs.box;
//
//	this->renderer = rhs.renderer;
//	rhs.renderer = NULL;
//	this->texture = rhs.texture;
//	rhs.texture = NULL;
//}

Background::~Background() {
	SDL_DestroyTexture(texture);
	std::cout << "Deleted background\n";
}

void Background::Render(SDL_Rect* windowRect) {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture, NULL, windowRect);
}

SDL_Texture* Background::GetTexture() {
	return texture;
}
