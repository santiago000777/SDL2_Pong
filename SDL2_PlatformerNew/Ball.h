#pragma once
#include "Player.h"
#include "Wall.h"

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

	void HandleEvents();
    void Update(float delta);

    void Collision(Player* player , float delta);
    void Collision(Wall* wall, float delta);

protected:
    TVec2 vector;

    bool collision[4] = { 0, 0, 0, 0 };
};

