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

int Brick::GetCurrentSprite() const {
	return currentSprite;
}

void Brick::SetPoints(int points) {
	this->points = points;
}

void Brick::ChangeSprite() {
	currentSprite++;
}
