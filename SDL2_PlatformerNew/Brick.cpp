#include "Brick.h"

Brick::Brick(Vec4f box, const std::string& path, int characterWidth)
	: Object(box, path, characterWidth) {

	isDestroyble = true;

	points = 1;
}

Brick::~Brick() {
	std::cout << "Deleted brick - " << points << " points\n";
}

int Brick::GetPoints() const {
	return points;
}