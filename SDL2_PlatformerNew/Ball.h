#pragma once
#include "Object.h"
class Ball : public Object {
public:
    Ball(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Ball(const Ball& rhs) = delete;
    // move ctor (zakazany)
    Ball(Ball&& rhs) = delete;
    // Destructor
    ~Ball();
    // copy prirazeni
    void operator=(const Ball& rhs) = delete;
    // move prirazeni
    void operator=(Ball&& rhs) = delete;

	void HandleEvents() override;

};

