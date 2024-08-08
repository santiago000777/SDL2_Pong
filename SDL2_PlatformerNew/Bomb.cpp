#include "Bomb.h"

Bomb::Bomb(SDL_Rect dstBox, const std::string& path, int characterWidth) 
	: Object(dstBox, path, characterWidth) {
	
	range.x = dstBox.x - dstBox.w;
	range.y = dstBox.y - dstBox.h;

	range.w = dstBox.w * 4;
	range.h = dstBox.h * 4;
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
