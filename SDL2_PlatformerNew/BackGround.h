#pragma once
#include "Texture.h"

class Background {
public:
	//Background() = default;
	// ctor s parametry
	Background(int width, int height, std::string path);
	// copy ctor (zakazany)
	Background(const Background& rhs) = delete;
	// move ctor (zakazany)
	Background(Background&& rhs) = delete;
	// copy prirazeni
	void operator=(const Background& rhs) = delete; 
	// move prirazeni
	void operator=(Background&& rhs) = delete;
	// Destructor
	~Background();

	void Render(SDL_Rect* windowRect); 
	SDL_Texture* GetTexture();

private:
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };

	SDL_Rect box;
};

