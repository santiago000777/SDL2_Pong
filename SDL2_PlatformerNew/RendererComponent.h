#pragma once
#include "common.h"
#include "Texture.h"

class RendererComponent {
public:
	
	SDL_Rect srcBox;
	SDL_Rect windowRect;

	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };

	virtual void Render() = 0;
private:

};

