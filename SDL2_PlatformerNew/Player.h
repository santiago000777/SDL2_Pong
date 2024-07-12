#pragma once
#include "Object.h"

class Player : public Object {
public:
    Player(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Player(const Player& rhs) = delete;
    // move ctor (zakazany)
    Player(Player&& rhs)/* = delete*/;
    // Destructor
    ~Player();
    // copy prirazeni
    void operator=(const Player& rhs);
    // move prirazeni
    void operator=(Player&& rhs);

    void HandleEvents() override;

private:
    enum eControls : short {
        UP = 'w',
        LEFT = 'a',
        DOWN = 's',
        RIGHT = 'd'
    };
};

