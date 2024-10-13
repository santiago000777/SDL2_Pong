#include "Brick.h"

Brick::Brick(Vec4f box, const std::string& path, int characterWidth)
	: Object(box, path, characterWidth) {

	isDestroyble = true;
}

Brick::Brick(Brick&& rhs) 
	: Object(std::move(rhs)) {

	path = "Pictures/BrickSpriteSheet.bmp";
	auto [tex, _] = CreateTexture(path, 255, 0, 255, 255);
	texture.reset(tex);

	points = rhs.points;
}

Brick::~Brick() {
	std::cout << "Deleted brick - " << points << " points\n";
}

int Brick::GetPoints() const {
	return points;
}


void Brick::Save(File& file) {
	file.Save(srcBox);
	file.Save(box);
	file.Save(currentSprite);

	file.Save(points);
}

void Brick::Load(File& file) {
	file.Load(srcBox);
	file.Load(box);
	file.Load(currentSprite);

	file.Load(points);

	isDestroyble = true;
}
