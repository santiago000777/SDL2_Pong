#pragma once
#include "Picture.h"

class Background {
public:
	//Background() = default;
	// ctor s parametry
	Background(std::string path);
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

	void Render();

private:
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Picture::DeleteTexture };
};