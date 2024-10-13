#pragma once
#include "common.h"
#include "Picture.h"
#include "Circle.h"

class Object {
public:
    Object() {}
    Object(Vec4f box, const std::string& path, int characterWidth);
    Object(const Object& rhs) = delete;
    Object(Object&& rhs);
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
    Vec4f GetBox() const;

    int GetSpriteWidth() const;
    int GetCurrentSprite() const;
    void ChangeSprite();

    static bool Collision(const Object& object, const Circle& circle);

    const std::string& GetPath() const;

    bool isAlive = true;
protected:

    Vec4f box;
    SDL_Rect srcBox;
    std::string path;

    bool isDestroyble = false;

    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, DeleteTexture };

    int currentSprite = 0;
private:
    int sprites = 0;
};