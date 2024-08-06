#pragma once
#include "Object.h"
#include "Circle.h"
	
// 20x20
class Bomb : public Object {
public:
	Bomb(SDL_Rect dstBox, const std::string& path, int characterWidth);
	// copy ctor (zakazany)
	Bomb(const Bomb& rhs) = delete;
	// move ctor (zakazany)
	Bomb(Bomb&& rhs) = delete;
	// copy prirazeni
	void operator=(const Bomb& rhs) = delete;
	// move prirazeni
	void operator=(Bomb&& rhs) = delete;
	// Destructor
	~Bomb() override;
private:
	Circle range;
};

