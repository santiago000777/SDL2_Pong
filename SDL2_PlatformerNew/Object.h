#pragma once
#include "common.h"

class Object {
public:
	Object(SDL_Renderer* renderer, SDL_Rect destBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect);
	Object(const Object& rhs) = delete;
	Object(Object&& rhs);
	~Object();

	void operator=(const Object& rhs);
	void operator=(Object&& rhs);

	void SetBackground(BackGround* bg);

	virtual void Render();
	virtual void HandleEvents();
	virtual void Posun(std::vector<Object*>* otherObjects, float delta);
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

	bool kolize[4];

private:
	void MistoKolize(std::vector<TGameObject*>* otherObjects, float delta);

	SDL_Rect windowRect;
	BackGround* background;
	SDL_Texture* texture;
};

