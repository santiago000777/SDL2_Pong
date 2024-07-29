#include "MovableObject.h"

float MovableObject::deltaT = 0.0f;

bool MovableObject::Collision(MovableObject& object, const Object& other) {
	
		// upravit Collision -> pomocne promenne

	SDL_Rect box = { object.dstBox.x + object.vector.x * MovableObject::deltaT, object.dstBox.y + object.vector.y * MovableObject::deltaT, object.dstBox.w, object.dstBox.h };
	
    if (box.x + box.w > other.GetDstBox().x && box.x < other.GetDstBox().x + other.GetDstBox().w
	&& box.y + box.h > other.GetDstBox().y && box.y < other.GetDstBox().y + other.GetDstBox().h) {

		if (abs(box.y - (other.GetDstBox().y + other.GetDstBox().h)) < abs((box.y + box.h) - other.GetDstBox().y)) {

			if (abs(box.y - (other.GetDstBox().y + other.GetDstBox().h)) < abs(box.x - (other.GetDstBox().x + other.GetDstBox().w))
			&& abs(box.y - (other.GetDstBox().y + other.GetDstBox().h)) < abs((box.x + box.w) - other.GetDstBox().x)) {
				std::cout << "Up\n";
				object.collision[UP] = true;
			} else {
				if (abs(box.x - (other.GetDstBox().x + other.GetDstBox().w)) < abs((box.x + box.w) - other.GetDstBox().x)) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		} 
		else {
			if (abs((box.y + box.h) - other.GetDstBox().y) < abs(box.x - (other.GetDstBox().x + other.GetDstBox().w))
			&& abs((box.y + box.h) - other.GetDstBox().y) < abs((box.x + box.w) - other.GetDstBox().x)) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
			} else {
				if (abs(box.x - (other.GetDstBox().x + other.GetDstBox().w)) < abs((box.x + box.w) - other.GetDstBox().x)) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		}
		return true;
	} 
	else {
		return false;
	}
}

MovableObject::MovableObject(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect) 
	: Object(dstBox, path, fromBox, windowRect) {

}

MovableObject::~MovableObject() {
}
