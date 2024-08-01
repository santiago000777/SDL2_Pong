#pragma once
#include "MovableObject.h"

class Player : public MovableObject {
public:
    Player(SDL_Rect dstBox, const std::string& path, int characterWidth, SDL_Rect windowRect);
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
    void Update();
    bool IsGameOver();
    void DecreaseLives(int i);

    void ResetPosition();

    int GetPlayerId() const;
    void AddPoints(int points);

private:
    int idPlayer;
    static int playerCount;
    enum class eControls : short {
        UP = 'w',
        LEFT = 'a',
        DOWN = 's',
        RIGHT = 'd'
    };
    int lives = 2;
    int points = 0;
};
