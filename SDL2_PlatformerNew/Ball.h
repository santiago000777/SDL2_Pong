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
    void Update(std::vector<Player*>* otherObjects, float delta);
    void Update(std::vector<Wall*>* otherObjects, float delta);
    enum eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    SDL_Rect GetDstBox() const;

protected:
    TVec2 vector;
    SDL_Rect dstBox;
    SDL_Rect srcBox;

    bool collision[4];
    bool isDestroyble = false;

    SDL_Rect windowRect;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };


    void CollisionPoint(std::vector<Player*>* otherObjects, float delta);
    void CollisionPoint(std::vector<Wall*>* otherObjects, float delta);
};

