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

	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;
}

void Ball::Render() {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

bool Ball::IsDestroyble() {
	return isDestroyble;
}

void Ball::Update(float delta) {
	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
	else {

		if (this->isDestroyble) {
			delete this;
			return;
		}

		if (this->collision[LEFT]) {

			if (this->vector.x > 0 && !this->collision[RIGHT])
				this->dstBox.x += roundf(this->vector.x * delta);

			if (this->vector.y < 0 && !this->collision[UP]
				|| this->vector.y > 0 && !this->collision[DOWN]) {

				this->dstBox.y += roundf(this->vector.y * delta);
			}
		}
		if (this->collision[RIGHT]) {

			if (this->vector.x < 0 && !this->collision[LEFT]) {
				this->dstBox.x += roundf(this->vector.x * delta);
			}
			if (this->vector.y < 0 && !this->collision[UP]
				|| this->vector.y > 0 && !this->collision[DOWN]) {

				this->dstBox.y += roundf(this->vector.y * delta);
			}
		}
		if (this->collision[UP]) {

			if (this->vector.y > 0 && !this->collision[DOWN])
				this->dstBox.y += roundf(this->vector.y * delta);

			if (this->vector.x < 0 && !this->collision[LEFT]
				|| this->vector.x > 0 && !this->collision[RIGHT]) {

				this->dstBox.x += roundf(this->vector.x * delta);
			}
		}
		if (this->collision[DOWN]) {

			if (this->vector.y < 0 && !this->collision[UP])
				this->dstBox.y += roundf(this->vector.y * delta);

			if (this->vector.x < 0 && !this->collision[LEFT]
				|| this->vector.x > 0 && !this->collision[RIGHT]) {

				this->dstBox.x += roundf(this->vector.x * delta);
			}
		}
	}
}

SDL_Rect Ball::GetDstBox() const {
	return dstBox;
}

void Ball::Collision(Player* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
	&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[RIGHT] = true;
			std::cout << "RIGHT\n";
		}
		if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[LEFT] = true;
			std::cout << "LEFT\n";
		}
		if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[DOWN] = true;
			std::cout << "DOWN\n";
		}
		if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[UP] = true;
			std::cout << "UP\n";
		}
	}
	if (object->IsDestroyble()) {
		delete object;
		return;
	}
}

void Ball::Collision(Wall* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
		&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[RIGHT] = true;
			std::cout << "RIGHT\n";
		}
		if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[LEFT] = true;
			std::cout << "LEFT\n";
		}
		if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[DOWN] = true;
			std::cout << "DOWN\n";
		}
		if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[UP] = true;
			std::cout << "UP\n";
		}
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


