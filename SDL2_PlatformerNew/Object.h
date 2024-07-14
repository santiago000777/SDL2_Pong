#pragma once
#include "Texture.h"
#include "Background.h"

class Object {
public:
	Object(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect);
	Object(const Object& rhs) = delete;
	Object(Object&& rhs);
	~Object();

	void operator=(const Object& rhs);
	void operator=(Object&& rhs);

	void SetBackground(Background* bg);
	bool IsDestroyble();

	virtual void Render();
	virtual void HandleEvents();
	virtual void Update(std::vector<Object*>* otherObjects, float delta);
	virtual void Clear();

	enum eIndex : int {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

protected:
	SDL_Renderer* renderer;
	TVec2 vector;
	SDL_Rect dstBox;
	SDL_Rect srcBox;

	bool collision[4];
	bool isDestroyble = false;

private:
	void CollisionPoint(std::vector<Object*>* otherObjects, float delta);

	SDL_Rect windowRect;
	Background* background;
	SDL_Texture* texture;
};

