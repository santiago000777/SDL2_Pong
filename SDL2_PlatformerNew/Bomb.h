#pragma once
#include "Object.h"
#include "Circle.h"

// 20x20
class Bomb : public Object {
public:
	Bomb(Vec4f box, const std::string& path, int characterWidth);
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

	SDL_Rect GetRange() const;
	void AddPoints(int p);
	int GetPoints() const;

	bool canDetonate = false;
private:
	SDL_Rect range;
	int collectedPoints = 0;
};