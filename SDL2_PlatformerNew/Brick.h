#pragma once
#include "Object.h"
class Brick : public Object {
public:
    Brick(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Brick(const Brick& rhs) = delete;
    // move ctor (zakazany)
    Brick(Brick&& rhs) = delete;
    // Destructor
    ~Brick()/* override*/;
    // copy prirazeni
    void operator=(const Brick& rhs) = delete;
    // move prirazeni
    void operator=(Brick&& rhs) = delete;

    //void HandleEvents() override;
    void SetPoints() override;

private:
};

