#pragma once
#include "MovableObject.h"

class Ball : public MovableObject {
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

    void SetOwnerId(int id);
    int GetOwnerId() const;
    int GetPoints() const;
    void AddPoints(int points);

	void HandleEvents(float delta);
    void Update();
    void ResetPoints();

protected:
    int points = 0;
    int playerOwnerId = -1;
};

