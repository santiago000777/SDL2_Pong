#pragma once
#include "Object.h"
#include "Circle.h"
#include "File.h"


class Bomb : public Object {
public:
	Bomb() {}
	Bomb(Vec4f box, const std::string& path, int characterWidth);
	// copy ctor (zakazany)
	Bomb(const Bomb& rhs) = delete;
	// move ctor (zakazany)
	Bomb(Bomb&& rhs);
	// copy prirazeni
	void operator=(const Bomb& rhs) = delete;
	// move prirazeni
	void operator=(Bomb&& rhs) = delete;
	// Destructor
	~Bomb() override;

	SDL_Rect GetRange() const;
	void AddPoints(int p);
	int GetPoints() const;

	void Save(File& file);
	void Load(File& file);

	bool canDetonate = false;
private:
	SDL_Rect range;
	int collectedPoints = 0;
};