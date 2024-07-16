#include "common.h"
#include "Background.h"
#include "Renderer.h"

Background::Background(int width, int height, std::string path)
	: box { 0, 0, width, height } {

	texture.reset(Texture::Create(path));
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
//	rhs.renderer = nullptr;
//	this->texture = rhs.texture;
//	rhs.texture = nullptr;
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
//	rhs.renderer = nullptr;
//	this->texture = rhs.texture;
//	rhs.texture = nullptr;
//}

Background::~Background() {
	std::cout << "Deleted background\n";
}

void Background::Render(SDL_Rect* windowRect) {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), nullptr, windowRect);
}

SDL_Texture* Background::GetTexture() {
	return texture.get();
}
