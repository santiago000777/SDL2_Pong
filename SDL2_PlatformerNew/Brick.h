#pragma once
#include "Object.h"
class Brick : public Object {
public:
    Brick(SDL_Rect dstBox, const std::string& path, int characterWidth);
    // copy ctor (zakazany)
    Brick(const Brick& rhs) = delete;
    // move ctor (zakazany)
    Brick(Brick&& rhs) = delete;
    // Destructor
    ~Brick() override;
    // copy prirazeni
    void operator=(const Brick& rhs) = delete;
    // move prirazeni
    void operator=(Brick&& rhs) = delete;

    int GetPoints() const;

private:
    int points = 0;
};