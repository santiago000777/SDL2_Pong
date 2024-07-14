#pragma once


class Background {
public:
	Background() = default;
	// ctor s parametry
	Background(int width, int height, std::string path, SDL_Renderer* renderer);
	// copy ctor (zakazany)
	Background(const Background& rhs) = delete;
	// move ctor (zakazany)
	Background(Background&& rhs) = delete;
	// copy prirazeni
	void operator=(const Background& rhs); 
	// move prirazeni
	void operator=(Background&& rhs);
	// Destructor
	~Background();

	void Render(SDL_Rect* windowRect); 
	SDL_Texture* GetTexture();

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect box;
};

