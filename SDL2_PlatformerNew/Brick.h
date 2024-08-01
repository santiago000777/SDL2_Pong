#pragma once
#include "Object.h"
class Brick : public Object {
public:
    Brick(SDL_Rect dstBox, const std::string& path, int characterWidth, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Brick(const Brick& rhs) = delete;
    // move ctor (zakazany)
    Brick(Brick&& rhs) = delete;
    // Destructor
    ~Brick();
    // copy prirazeni
    void operator=(const Brick& rhs) = delete;
    // move prirazeni
    void operator=(Brick&& rhs) = delete;

	int GetPoints() const;
    void SetPoints(int points);
private:
	int points = 1;
    int textureIndex = 1;
};

