#pragma once
#include "Object.h"

class Wall : public Object {
public:
    Wall(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Wall(const Wall& rhs) = delete;
    // move ctor (zakazany)
    Wall(Wall&& rhs) = delete;
    // Destructor
    ~Wall();
    // copy prirazeni
    void operator=(const Wall& rhs) = delete;
    // move prirazeni
    void operator=(Wall&& rhs) = delete;
};

