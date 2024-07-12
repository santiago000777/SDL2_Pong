#pragma once
#include "Object.h"

class Wall : public Object {
public:
	Wall(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
	Wall(const Wall& rhs);
	Wall(Wall&& rhs);
	~Wall();

	void operator=(const Wall& rhs);
	void operator=(Wall&& rhs);
};

