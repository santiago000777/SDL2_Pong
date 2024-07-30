#include "Object.h"

SDL_Rect Object::GetDstBox() const {
	return dstBox;
}

bool Object::IsDestroyble() const {
	return isDestroyble;
}

void Object::Render() {

	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

Object::Object(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect) 
	: dstBox(dstBox), srcBox(fromBox), windowRect(windowRect) {

	texture.reset(Texture::Create(path, 255, 255, 255, 255));
}

Object::~Object() {

}
