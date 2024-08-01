#include "Brick.h"

Brick::Brick(SDL_Rect dstBox, const std::string& path, int characterWidth, SDL_Rect windowRect)
	: Object(dstBox, path, characterWidth, windowRect) {
	isDestroyble = true;

}

Brick::~Brick() {
	std::cout << "Deleted brick - " << points << " points\n";
}

int Brick::GetPoints() const {
	return points;
}

void Brick::SetPoints(int points) {
	this->points = points;
}
