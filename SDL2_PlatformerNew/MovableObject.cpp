#include "MovableObject.h"

float MovableObject::deltaT = 0.0f;


bool MovableObject::Collision(MovableObject& object, const Object& other) {

	SDL_Rect box1 = { object.dstBox.x + object.vector.x * MovableObject::deltaT, object.dstBox.y + object.vector.y * MovableObject::deltaT, object.dstBox.w, object.dstBox.h };
	SDL_Rect box2 = { other.GetDstBox().x, other.GetDstBox().y, other.GetDstBox().w, other.GetDstBox().h };

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

    if (RightEdge(box1) > LeftEdge(box2) && LeftEdge(box1) < RightEdge(box2)
	&& DownEdge(box1) > UpEdge(box2) && UpEdge(box1) < DownEdge(box2)) { 

		if (abs(UpEdge(box1) - DownEdge(box2)) < abs(DownEdge(box1) - UpEdge(box2))) {

			if (abs(UpEdge(box1) - DownEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
			&& abs(UpEdge(box1) - DownEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
				std::cout << "Up\n"; 
				object.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		} 
		else {
			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
			&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
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

bool MovableObject::Collision(MovableObject& object, const SDL_Rect& other) {
	SDL_Rect box1 = { object.dstBox.x + object.vector.x * MovableObject::deltaT, object.dstBox.y + object.vector.y * MovableObject::deltaT, object.dstBox.w, object.dstBox.h };

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

	if (RightEdge(box1) > LeftEdge(other) && LeftEdge(box1) < RightEdge(other)
		&& DownEdge(box1) > UpEdge(other) && UpEdge(box1) < DownEdge(other)) {

		if (abs(UpEdge(box1) - DownEdge(other)) < abs(DownEdge(box1) - UpEdge(other))) {

			if (abs(UpEdge(box1) - DownEdge(other)) < abs(LeftEdge(box1) - RightEdge(other))
				&& abs(UpEdge(box1) - DownEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {
				std::cout << "Up\n";
				object.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		} else {
			if (abs(DownEdge(box1) - UpEdge(other)) < abs(LeftEdge(box1) - RightEdge(other))
				&& abs(DownEdge(box1) - UpEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

const std::string& MovableObject::GetPath() const {
	return path;
}

//bool MovableObject::Collision(MovableObject& object, const MovableObject& other) {
//	SDL_Rect box1 = { object.dstBox.x + object.vector.x * MovableObject::deltaT, object.dstBox.y + object.vector.y * MovableObject::deltaT, object.dstBox.w, object.dstBox.h };
//	SDL_Rect box2 = { other.dstBox.x + other.vector.x * MovableObject::deltaT, other.dstBox.y + other.vector.y * MovableObject::deltaT, other.dstBox.w, other.dstBox.h };
//
//	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
//	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
//	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
//	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };
//
//	if (RightEdge(box1) > LeftEdge(box2) && LeftEdge(box1) < RightEdge(box2)
//		&& DownEdge(box1) > UpEdge(box2) && UpEdge(box1) < DownEdge(box2)) {
//
//		if (abs(UpEdge(box1) - DownEdge(box2)) < abs(DownEdge(box1) - UpEdge(box2))) {
//
//			if (abs(UpEdge(box1) - DownEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
//				&& abs(UpEdge(box1) - DownEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
//				std::cout << "Up\n";
//				object.collision[UP] = true;
//			} else {
//				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
//					std::cout << "Left\n";
//					object.collision[LEFT] = true;
//				} else {
//					std::cout << "Right\n";
//					object.collision[RIGHT] = true;
//				}
//			}
//		} else {
//			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
//				&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
//
//				std::cout << "Down\n";
//				object.collision[DOWN] = true;
//			} else {
//				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
//					std::cout << "Left\n";
//					object.collision[LEFT] = true;
//				} else {
//					std::cout << "Right\n";
//					object.collision[RIGHT] = true;
//				}
//			}
//		}
//		return true;
//	} else {
//		return false;
//	}
//}

bool MovableObject::Collision(MovableObject& object, MovableObject& other) {
	SDL_Rect box1 = { object.dstBox.x + object.vector.x * MovableObject::deltaT, object.dstBox.y + object.vector.y * MovableObject::deltaT, object.dstBox.w, object.dstBox.h };
	SDL_Rect box2 = { other.dstBox.x + other.vector.x * MovableObject::deltaT, other.dstBox.y + other.vector.y * MovableObject::deltaT, other.dstBox.w, other.dstBox.h };

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

	if (RightEdge(box1) > LeftEdge(box2) && LeftEdge(box1) < RightEdge(box2)
		&& DownEdge(box1) > UpEdge(box2) && UpEdge(box1) < DownEdge(box2)) {

		if (abs(UpEdge(box1) - DownEdge(box2)) < abs(DownEdge(box1) - UpEdge(box2))) {

			if (abs(UpEdge(box1) - DownEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(UpEdge(box1) - DownEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
				std::cout << "Up\n";
				object.collision[UP] = true;
				other.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
					other.collision[RIGHT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
					other.collision[LEFT] = true;
				}
			}
		} else {
			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
				other.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
					other.collision[RIGHT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
					other.collision[LEFT] = true;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

MovableObject::MovableObject(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: Object(dstBox, path, characterWidth), path(path) {

}

MovableObject::~MovableObject() {

}
