#pragma once
#include "common.h"

class Circle {
public:
	//Circle() {}
	Circle(SDL_Rect dstBox) {
		radius = (dstBox.w + dstBox.h) / 2 * 3;

		center.x = dstBox.x + dstBox.w / 2;
		center.y = dstBox.y + dstBox.h / 2;
	}

	int radius { 0 };
	Vec2 center;
private:
};

