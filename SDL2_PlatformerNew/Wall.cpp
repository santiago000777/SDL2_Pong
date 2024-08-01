#include "Wall.h"

Wall::Wall(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: Object(dstBox, path, characterWidth) {

}

Wall::~Wall() {
	std::cout << "Deleted wall!\n";
}


