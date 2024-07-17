#include "Ball.h"



Ball::Ball(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect) 
	: Object(dstBox, path, from, windowRect) {
	/*std::random_device nahodneCis;
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	std::cout << dist(nahodneCis) << ",  " << dist(nahodneCis) << "\n";
	vector = { roundf(dist(nahodneCis)), roundf(dist(nahodneCis)) };*/
	vector = { 1, 1 };
}

//Ball::Ball(const Ball& rhs) 
//	: Object(rhs) {
//
//}

//Ball::Ball(Ball&& rhs) 
//	: Object(std::move(rhs)) {
//
//}

Ball::~Ball() {
	std::cout << "Deleted ball\n";
}

//void Ball::operator=(const Ball& rhs) {
//	this->dstBox = rhs.dstBox;
//	this->srcBox = rhs.srcBox;
//	this->windowRect = rhs.windowRect;
//	this->isDestroyble = rhs.isDestroyble;
//	
//	this->vector = rhs.vector;
//
//	this->renderer = rhs.renderer;
//	this->texture = Texture::Create(renderer, path);
//	*this->background = *rhs.background;
//	memcpy(this->collision, rhs.collision, 4 * sizeof(bool));
//}

//void Ball::operator=(Ball&& rhs) {
//	this->dstBox = rhs.dstBox;
//	this->srcBox = rhs.srcBox;
//	this->windowRect = rhs.windowRect;
//	this->isDestroyble = rhs.isDestroyble;
//	this->path = rhs.path;
//	this->vector = rhs.vector;
//	
//	memcpy(this->collision, rhs.collision, 4 * sizeof(bool));
//	
//	this->background = rhs.background;
//	rhs.background = nullptr;
//	
//	this->renderer = rhs.renderer;
//	rhs.renderer = nullptr;
//	
//	this->texture = rhs.texture;
//	rhs.texture = nullptr;
//}

void Ball::HandleEvents() {
	if (this->collision[eIndex::UP]) {
		vector.y *= -1;
	}
	if (this->collision[eIndex::DOWN]) {
		vector.y *= -1;
	}
	if (this->collision[eIndex::LEFT]) {
		vector.x *= -1;
	}
	if (this->collision[eIndex::RIGHT]) {
		vector.x *= -1;
	}
}

//void Ball::CollisionPoint(std::vector<Brick*>* otherObjects, float delta) {
//	this->collision[LEFT] = false;
//	this->collision[RIGHT] = false;
//	this->collision[UP] = false;
//	this->collision[DOWN] = false;
//
//	for (auto& object : *otherObjects) {
//		if (IsCollision(object, delta)) {
//
//			if (this->isDestroyble) {
//				delete this;
//				return;
//			}
//
//			if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetPosition().x
//				&& this->dstBox.y < object->GetPosition().y + object->GetPosition().h && this->dstBox.y + this->dstBox.h > object->GetPosition().y) {
//				
//				this->collision[RIGHT] = true;
//				std::cout << "RIGHT\n";
//			}
//			if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetPosition().x + object->GetPosition().w
//				&& this->dstBox.y < object->GetPosition().y + object->GetPosition().h && this->dstBox.y + this->dstBox.h > object->GetPosition().y) {
//
//				this->collision[LEFT] = true;
//				std::cout << "LEFT\n";
//			}
//			if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetPosition().y
//				&& this->dstBox.x < object->GetPosition().x + object->GetPosition().w && this->dstBox.x + this->dstBox.w > object->GetPosition().x) {
//
//				this->collision[DOWN] = true;
//				std::cout << "DOWN\n";
//			}
//			if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetPosition().y + object->GetPosition().h
//				&& this->dstBox.x < object->GetPosition().x + object->GetPosition().w && this->dstBox.x + this->dstBox.w > object->GetPosition().x) {
//
//				this->collision[UP] = true;
//				std::cout << "UP\n";
//			}
//
//			if (object->IsDestroyble()) {
//				delete object;
//			}
//		}
//	}
//}


