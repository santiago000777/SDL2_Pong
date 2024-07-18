#include "Wall.h"

Wall::Wall(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect)
	: dstBox(dstBox), srcBox(from), windowRect(windowRect) {

	texture.reset(Texture::Create(path, 255, 255, 255, 255));
}

Wall::~Wall() {
	std::cout << "Deleted wall!\n";
}

void Wall::Render() {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

SDL_Rect Wall::GetDstBox() const {
	return dstBox;
}

bool Wall::IsDestroyble() const {
	return isDestroyble;
}

