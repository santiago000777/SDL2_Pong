#include "Bomb.h"

Bomb::Bomb(SDL_Rect dstBox, const std::string& path, int characterWidth) 
	: Object(dstBox, path, characterWidth), range(dstBox) {

}

Bomb::~Bomb() {

}
