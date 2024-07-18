#pragma once
#include "Player.h"
#include "Wall.h"

class Ball {
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

    void Render();
    bool IsDestroyble();
    void Update(float delta);
    enum eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    SDL_Rect GetDstBox() const;

    void Collision(Player* player , float delta);
    void Collision(Wall* wall, float delta);

protected:
    TVec2 vector;
    SDL_Rect dstBox;
    SDL_Rect srcBox;

    bool collision[4] = { 0, 0, 0, 0 };
    bool isDestroyble = false;

    SDL_Rect windowRect;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };


    
};

