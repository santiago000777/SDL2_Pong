#pragma once
#include "common.h"

class Texture {
public:
	static SDL_Texture* Create(SDL_Renderer* renderer, const std::string& path) {
		if (path.empty()) {
			std::cout << "Textura nema prirazenou cestu, cesta je prazdna";
			BREAK();
		} else if (SDL_LoadBMP(path.c_str()) == NULL) {
			std::cout << "Nelze nalezt soubor s cestou na nastaveni obrazku Textury: " + path;
			BREAK();
		}

		//SDL_Surface* surface = SDL_LoadBMP(path.c_str());
		std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(SDL_LoadBMP(path.c_str()), SDL_FreeSurface);

		Uint32 transparentColor = SDL_MapRGBA(surface->format, 255, 255, 255, 0);
		SDL_SetColorKey(surface.get(), SDL_ENABLE, transparentColor);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.get());
		//SDL_FreeSurface(surface);

		return texture;
	}
};
