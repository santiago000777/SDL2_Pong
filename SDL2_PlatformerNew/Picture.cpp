#include "Picture.h"

std::tuple<SDL_Texture*, SDL_Rect> CreateTexture(const std::string& path, Uint8 rTransparent, Uint8 gTransparent, Uint8 bTransparent, Uint8 aTransparent) {// 
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

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::Get().Renderer(), surface);
	SDL_Rect srcBox = { 0, 0, surface->w, surface->h };

	SDL_FreeSurface(surface);

	return { texture, srcBox };
}

void DeleteTexture(SDL_Texture* tex) {
	if (tex == nullptr)
		return;
	SDL_DestroyTexture(tex);
	std::cout << "SDL_Destroy -> Deleted Texture!\n";
}