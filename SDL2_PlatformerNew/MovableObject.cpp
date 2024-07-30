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

//bool MovableObject::Collision(MovableObject& object, const MovableObject& other) {
//	SDL_Rect box1 = { object.dstBox.x + object.vector.x * MovableObject::deltaT, object.dstBox.y + object.vector.y * MovableObject::deltaT, object.dstBox.w, object.dstBox.h };
//	SDL_Rect box2 = { other.dstBox.x + other.vector.x * MovableObject::deltaT, other.dstBox.y + other.vector.y * MovableObject::deltaT, other.dstBox.w, other.dstBox.h };
//
//	//TODO:
//		// ruzne rychlosti ->
//		// stejnym smerem (obe slozky x||y jsou kladne||zaporne)
//			// vyssi vektor se nastavi na mensi vektor
//		// ruznym smerem (x||y slozka vektoru je kladna tak je ta druha zaporna)
//			// mensi vektor se nastavi na vetsi vektor
//
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

MovableObject::MovableObject(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect) 
	: Object(dstBox, path, fromBox, windowRect) {

}

MovableObject::~MovableObject() {
}
