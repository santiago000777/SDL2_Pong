#pragma once
#include "common.h"
#include "Texture.h"

class RendererComponent {
public:
	RendererComponent(SDL_Rect from, SDL_Rect windowRect);

	virtual void Render() = 0;
protected:
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };
	SDL_Rect dstBox;
	SDL_Rect srcBox;
	SDL_Rect windowRect;

private:

};

