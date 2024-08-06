#include "Brick.h"

Brick::Brick(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: Object(dstBox, path, characterWidth) {

	isDestroyble = true;

	std::random_device randomNum;
	std::uniform_int_distribution<int> randomPoints(-10, 20);
	points = randomPoints(randomNum);
}

Brick::~Brick() {
	std::cout << "Deleted brick - " << points << " points\n";
}

int Brick::GetPoints() const {
	return points;
}

