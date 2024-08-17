#pragma once
#include "common.h"

class Text {
public:
	void Init(std::string text, TTF_Font* font, SDL_Rect dstBox, SDL_Color color);
	void Render();
	void ChangeText(std::string text);

	~Text();

private:
	SDL_Rect dstBox;
	SDL_Color color;
	TTF_Font* font;

	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture = { nullptr, SDL_DestroyTexture };
	SDL_Surface* surface;
};

