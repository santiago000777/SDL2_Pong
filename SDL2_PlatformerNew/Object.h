#pragma once
#include "common.h"
#include "Picture.h"
#include "Circle.h"

class Object {
public:
	Object() = delete;
    Object(SDL_Rect dstBox, const std::string& path, int characterWidth);
	Object(const Object& rhs) = delete;
	Object(Object&& rhs) = delete;
    virtual ~Object() = default;
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

    int GetSpriteWidth() const;
    int GetCurrentSprite() const;
    void ChangeSprite();

    static bool Collision(const Object& object, const Circle& circle);

    bool isAlive = true;
protected:

    SDL_Rect dstBox;
    SDL_Rect srcBox;

    bool isDestroyble = false;

    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Picture::DeleteTexture };

    int currentSprite = 0;
private:
    int sprites = 0;

};

