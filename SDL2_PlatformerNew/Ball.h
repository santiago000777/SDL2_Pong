#pragma once
#include "Object.h"

class Ball : public Object {
public:
	Ball(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
	Ball(const Ball& rhs);
	Ball(Ball&& rhs);
	~Ball();

	void operator=(const Ball& rhs);
	void operator=(Ball&& rhs);
};

