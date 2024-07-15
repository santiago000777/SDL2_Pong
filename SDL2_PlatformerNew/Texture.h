#pragma once
#include "common.h"
#include "Renderer.h"

class Texture {
public:
	static SDL_Texture* Create(const std::string& path) {
		if (path.empty()) {
			std::cout << "Textura nema prirazenou cestu, cesta je prazdna";
			BREAK();
		} else if (SDL_LoadBMP(path.c_str()) == NULL) {
			std::cout << "Nelze nalezt soubor s cestou na nastaveni obrazku Textury: " + path;
			BREAK();
		}

		SDL_Surface* surface = SDL_LoadBMP(path.c_str());

		Uint32 transparentColor = SDL_MapRGBA(surface->format, 255, 255, 255, 0);
		SDL_SetColorKey(surface, SDL_ENABLE, transparentColor);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(SRenderer::Get().Renderer(), surface);
		SDL_FreeSurface(surface);

		return texture;
	}
};
