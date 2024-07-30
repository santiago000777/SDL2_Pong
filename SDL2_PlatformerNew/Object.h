#pragma once
#include "common.h"
#include "Texture.h"

class Object {
public:
	Object() = delete;
    Object(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect);
	Object(const Object& rhs) = delete;
	Object(Object&& rhs) = delete;
    ~Object();
	void operator=(const Object& rhs) = delete;
	void operator=(Object&& rhs) = delete;

    void Render();
    enum eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    SDL_Rect GetDstBox() const;
    bool IsDestroyble() const;

    bool isAlive = true;
protected:
    SDL_Rect dstBox;
    SDL_Rect srcBox;

    bool isDestroyble = false;

    SDL_Rect windowRect;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };

private:

};

