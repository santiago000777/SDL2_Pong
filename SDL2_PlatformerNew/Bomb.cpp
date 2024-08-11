#include "Bomb.h"

Bomb::Bomb(Vec4f box, const std::string& path, int characterWidth)
	: Object(box, path, characterWidth) {

	range.x = int(box.x - box.w);
	range.y = int(box.y - box.h);

	range.w = int(box.w * 4);
	range.h = int(box.h * 4);
}

Bomb::~Bomb() {
	std::cout << "Deleted Bomb\n";
}

SDL_Rect Bomb::GetRange() const {
	return range;
}

void Bomb::AddPoints(int p) {
	collectedPoints += p;
}

int Bomb::GetPoints() const {
	return collectedPoints;
}