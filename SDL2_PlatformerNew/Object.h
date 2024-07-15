#pragma once
#include "Texture.h"
#include "Background.h"

class Object {
public:
	Object(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect);
	Object(const Object& rhs) = delete;
	Object(Object&& rhs) = delete;
	~Object();

	void operator=(const Object& rhs) = delete;
	void operator=(Object&& rhs) = delete;

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
	TVec2 vector;
	SDL_Rect dstBox;
	SDL_Rect srcBox;

	bool collision[4];
	bool isDestroyble = false;

	SDL_Rect windowRect;
	Background* background;
	SDL_Texture* texture;
	std::string path;
private:
	void CollisionPoint(std::vector<Object*>* otherObjects, float delta);
};

