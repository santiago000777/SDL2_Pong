#include "Object.h"

SDL_Rect Object::GetDstBox() const {
	return dstBox;
}

int Object::GetSpriteWidth() const {
	return srcBox.w;
}

bool Object::IsDestroyble() const {
	return isDestroyble;
}

int Object::GetCountOfSprites() const {
	return sprites;
}

void Object::Render() {
	srcBox.x = srcBox.w * currentSprite;
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

Object::Object(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: dstBox(dstBox) {

	Picture picture = Picture::Create(path, 255, 0, 255, 255);
	srcBox = picture.GetSrcBox();
	sprites = srcBox.w / characterWidth;
	srcBox.w = characterWidth;
	texture.reset(picture.GetTexture());
}

Object::~Object() {

}
