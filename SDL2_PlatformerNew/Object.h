#pragma once
#include "Texture.h"
#include "Background.h"

class Object {
public:
	Object() {}
	Object(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect);
	Object(const Object& rhs) = delete;
	Object(Object&& rhs) = delete;
	~Object();

	void operator=(const Object& rhs) = delete;
	void operator=(Object&& rhs) = delete;

	bool IsDestroyble();

	virtual void Render();
	virtual void HandleEvents();
	virtual void Update(std::vector<Object*>* otherObjects, float delta);

	enum eIndex : int {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};
	TVec2 GetPosition() const;

protected:
	TVec2 vector;
	SDL_Rect dstBox;
	SDL_Rect srcBox;

	bool collision[4];
	bool isDestroyble = false;

	SDL_Rect windowRect;

	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete};

	
private:
	void CollisionPoint(std::vector<Object*>* otherObjects, float delta);

};

