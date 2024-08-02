#pragma once
#include "MovableObject.h"

	// TODO: Odraz na spodni hranici, kde se odecitaji zivoty

class Bubble : public MovableObject {
public:
	Bubble() = delete;
	Bubble(SDL_Rect dstBox, const std::string& path, int characterWidth);
	Bubble(const Bubble& rhs) = delete;
	Bubble(Bubble&& rhs) = delete;
	~Bubble();
	void operator=(const Bubble& rhs) = delete;
	void operator=(Bubble&& rhs) = delete;

	void Update();
private:

};

