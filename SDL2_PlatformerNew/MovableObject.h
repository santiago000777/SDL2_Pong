#pragma once
#include "Object.h"
class MovableObject : public Object {
public:
	MovableObject() = delete;
	MovableObject(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect);
	MovableObject(const MovableObject& rhs) = delete;
	MovableObject(MovableObject&& rhs) = delete;
	~MovableObject();
	void operator=(const MovableObject& rhs) = delete;
	void operator=(MovableObject&& rhs) = delete;

	static bool Collision(MovableObject& object, const Object& other);

		// ??
	static float deltaT;
protected:

	bool collision[4] = { 0, 0, 0, 0 };
	TVec2 vector;
private:
};

