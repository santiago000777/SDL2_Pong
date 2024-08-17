#pragma once
#include "MovableObject.h"

class Player : public MovableObject {
public:
    Player(Vec4f box, const std::string& path, int characterWidth);
    // copy ctor (zakazany)
    Player(const Player& rhs) = delete;
    // move ctor (zakazany)
    Player(Player&& rhs) = delete;
    // Destructor
    ~Player() override;
    // copy prirazeni
    void operator=(const Player& rhs) = delete;
    // move prirazeni
    void operator=(Player&& rhs) = delete;

    void HandleEvents();
    void Update();
    bool IsGameOver() const;
    void DecreaseLives(int i);

    void ResetPosition();

    int GetPlayerId() const;
    int GetLives() const;
    int GetPoints() const;
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

    int lives = 3;
    int points = 0;
};