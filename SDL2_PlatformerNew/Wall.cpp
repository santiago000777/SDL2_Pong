#include "Wall.h"

Wall::Wall(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect)
	: Object(dstBox, path, from, windowRect) {

}

Wall::~Wall() {
	std::cout << "Deleted wall!\n";
}


