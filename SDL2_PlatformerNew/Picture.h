#pragma once
#include "common.h"
#include "Renderer.h"

class Picture {
public:
	
	Picture(const Picture& rhs) = delete;
	Picture(Picture&& rhs) {
		this->srcBox = rhs.srcBox;
		this->tex = rhs.tex;
		rhs.tex = nullptr;
	}

	void operator=(const Picture& rhs) = delete;
	void operator=(Picture&& rhs) {
		this->srcBox = rhs.srcBox;
		this->tex = rhs.tex;
		rhs.tex = nullptr;
	}

	static Picture&& Create(const std::string& path, Uint8 rTransparent, Uint8 gTransparent, Uint8 bTransparent, Uint8 aTransparent) {
		if (path.empty()) {
			std::cout << "Textura nema prirazenou cestu, cesta je prazdna";
			BREAK();
		} else if (SDL_LoadBMP(path.c_str()) == nullptr) {
			std::cout << "Nelze nalezt soubor s cestou na nastaveni obrazku Textury: " + path;
			BREAK();
		}

		SDL_Surface* surface = SDL_LoadBMP(path.c_str());

		Uint32 transparentColor = SDL_MapRGBA(surface->format, rTransparent, gTransparent, bTransparent, aTransparent);
		SDL_SetColorKey(surface, SDL_ENABLE, transparentColor);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(SRenderer::Get().Renderer(), surface);
		SDL_Rect srcBox = {0, 0, surface->w, surface->h};

		SDL_FreeSurface(surface);
		return { texture, srcBox };
	}

	static void DeleteTexture(SDL_Texture* tex) {
		if (tex == nullptr)
			return;
		SDL_DestroyTexture(tex);
		std::cout << "SDL_Destroy -> Deleted Texture!\n";
	}

	SDL_Texture* GetTexture() const { return tex; }

	SDL_Rect GetSrcBox() const { return srcBox; }

	~Picture() {
	}
	
private:
	Picture(SDL_Texture* tex, SDL_Rect srcBox)
		: tex(tex), srcBox(srcBox) {

	}

	SDL_Texture* tex;
	SDL_Rect srcBox;
};
