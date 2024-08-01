#include "Wall.h"

Wall::Wall(SDL_Rect dstBox, const std::string& path, int characterWidth, SDL_Rect windowRect)
	: Object(dstBox, path, characterWidth, windowRect) {

}

Wall::~Wall() {
	std::cout << "Deleted wall!\n";
}


