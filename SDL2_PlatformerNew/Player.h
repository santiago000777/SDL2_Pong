#pragma once
#include "Wall.h"

class Player : public Object {
public:
    Player(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Player(const Player& rhs) = delete;
    // move ctor (zakazany)
    Player(Player&& rhs) = delete;
    // Destructor
    ~Player();
    // copy prirazeni
    void operator=(const Player& rhs) = delete;
    // move prirazeni
    void operator=(Player&& rhs) = delete;

    void HandleEvents();
    void Update(float delta);
    bool IsGameOver();
    void DecreaseLives(int i);
    void Collision(Wall* wall, float delta);

    int GetPlayerId() const;

private:
    TVec2 vector;
    int idPlayer;
    static int playerCount;
    bool collision[4];
    enum class eControls : short {
        UP = 'w',
        LEFT = 'a',
        DOWN = 's',
        RIGHT = 'd'
    };
    int lives = 1;
};
