#pragma once
#include "common.h"

class BackGround {
public:
	BackGround() = default;
	// ctor s parametry
	BackGround(int width, int height, std::string path, SDL_Renderer* renderer);
	// copy ctor (zakazany)
	BackGround(const BackGround& rhs) = delete;
	// move ctor (zakazany)
	BackGround(BackGround&& rhs) = delete;
	// copy prirazeni
	void operator=(const BackGround& rhs);
	// move prirazeni
	void operator=(BackGround&& rhs);
	// Destructor
	~BackGround();

	void Render(SDL_Rect* windowRect); 
	SDL_Texture* GetTexture();

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect box;
};

