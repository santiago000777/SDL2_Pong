#include "common.h"
#include "Background.h"
#include "Renderer.h"

Background::Background(std::string path) {

	Picture picture = Picture::Create(path, 255, 0, 255, 255);
	texture.reset(picture.GetTexture());
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

void Background::Render() {
	SDL_RenderCopy(Renderer::Get().Renderer(), texture.get(), nullptr, &Renderer::Get().WindowRect());
}