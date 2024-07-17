#include "Brick.h"

Brick::Brick(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect) 
	: Object(dstBox, path, from, windowRect) {
	isDestroyble = true;
}

Brick::~Brick() {
	std::cout << "Deleted brick\n";
}

void Brick::SetPoints() {
	std::random_device randomNum;
	std::uniform_int_distribution<int> dist(-20, 100);
	points = dist(randomNum);
}

