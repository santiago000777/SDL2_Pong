#include "Text.h"
#include "IRenderer.h"

void Text::Init(std::string text, TTF_Font* font, SDL_Rect dstBox, SDL_Color color) {
	this->font = font;
	this->dstBox = dstBox;
	this->color = color;

	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	std::cout << "Created Text surface\n";
	texture.reset(SDL_CreateTextureFromSurface(Renderer::Get().Renderer(), surface));
	std::cout << "Created Text texture\n";
	SDL_FreeSurface(surface);
	std::cout << "Deleted Text surface\n";
}

void Text::Render() {
	SDL_RenderCopy(Renderer::Get().Renderer(), texture.get(), NULL, &dstBox);
}

void Text::ChangeText(std::string text) {
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	std::cout << "Created Text surface\n";
	texture.reset(SDL_CreateTextureFromSurface(Renderer::Get().Renderer(), surface));
	std::cout << "Created Text texture\n";
	SDL_FreeSurface(surface);
	std::cout << "Deleted Text surface\n";
}

Text::~Text() {

	std::cout << "Deleted Text\n";
}
