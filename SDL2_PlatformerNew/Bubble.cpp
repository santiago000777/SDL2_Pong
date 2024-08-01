#include "Bubble.h"

Bubble::Bubble(SDL_Rect dstBox, const std::string& path, int characterWidth) 
	: MovableObject(dstBox, path, characterWidth){

}

Bubble::~Bubble() {
}
