#pragma once
//#include "MoveComponent.h"
//#include "RendererComponent.h"
#include "common.h";
#include "Texture.h"

class Wall {
public:
    Wall(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Wall(const Wall& rhs) = delete;
    // move ctor (zakazany)
    Wall(Wall&& rhs) = delete;
    // Destructor
    ~Wall();
    // copy prirazeni
    void operator=(const Wall& rhs) = delete;
    // move prirazeni
    void operator=(Wall&& rhs) = delete;

    void Render();
    enum eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    SDL_Rect GetDstBox() const;
    bool IsDestroyble() const;
private:
    SDL_Rect dstBox;
    SDL_Rect srcBox;

    bool isDestroyble = false;

    SDL_Rect windowRect;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };
};

