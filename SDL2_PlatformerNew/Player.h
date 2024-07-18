#pragma once
#include "Wall.h"

class Player {
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

    void Render();
    bool IsDestroyble();
    void Update(std::vector<Wall*>* others, float delta);
    enum class eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    SDL_Rect GetDstBox() const;
    bool IsGameOver();
    void DecreaseLives(int i);

protected:
    TVec2 vector;
    SDL_Rect dstBox;
    SDL_Rect srcBox;

    bool collision[4];
    bool isDestroyble = false;

    SDL_Rect windowRect;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };


    void CollisionPoint(std::vector<Wall*>* others, float delta);
    
    
private:
    enum class eControls : short {
        UP = 'w',
        LEFT = 'a',
        DOWN = 's',
        RIGHT = 'd'
    };
    int lives = 1;
};

