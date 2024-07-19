#pragma once
#include "Player.h"
#include "Wall.h"
#include "Brick.h"

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

    int GetOwnerId() const;
    int GetPoints() const;
	void HandleEvents();
    void Update(float delta);
    void ResetPoints();

    void Collision(Player* player , float delta);
    void Collision(Wall* wall, float delta);
    bool Collision(Brick* wall, float delta);

protected:
    int points = 0;
    TVec2 vector;
    int playerOwnerId = -1;
    bool collision[4] = { 0, 0, 0, 0 };
};

