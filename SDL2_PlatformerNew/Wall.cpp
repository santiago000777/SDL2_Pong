#include "Wall.h"

Wall::Wall(Vec4f box, const std::string& path, int characterWidth)
	: Object(box, path, characterWidth) {

}

Wall::~Wall() {
	std::cout << "Deleted wall!\n";
}