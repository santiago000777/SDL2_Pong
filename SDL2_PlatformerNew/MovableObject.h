#pragma once
#include "Object.h"
class MovableObject : public Object {
public:
	MovableObject() = delete;
	MovableObject(SDL_Rect dstBox, const std::string& path, int characterWidth);
	MovableObject(const MovableObject& rhs) = delete;
	MovableObject(MovableObject&& rhs) = delete;
	~MovableObject() override;
	void operator=(const MovableObject& rhs) = delete;
	void operator=(MovableObject&& rhs) = delete;

	static bool Collision(MovableObject& object, const Object& other);
	static bool Collision(MovableObject& object, const SDL_Rect& other);
	static bool Collision(const Object& object, const SDL_Rect& other);
	static bool Collision(MovableObject& object, MovableObject& other);

	const std::string& GetPath() const;
	const Vec2 GetVector() const;

	static float deltaT;
protected:
	std::string path;
	bool collision[4] = { 0, 0, 0, 0 };
	Vec2 vector;
private:

};