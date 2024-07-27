#include "Ball.h"

Ball::Ball(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect) 
	: Object(dstBox, path, from, windowRect) {
	/*std::random_device nahodneCis;
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	std::cout << dist(nahodneCis) << ",  " << dist(nahodneCis) << "\n";
	vector = { roundf(dist(nahodneCis)), roundf(dist(nahodneCis)) };*/
	
	vector = { 1.5f, 1.5f };
}


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

int Ball::GetOwnerId() const {
	return playerOwnerId;
}

int Ball::GetPoints() const {
	return points;
}

void Ball::HandleEvents() {
	/*this->vector *= delta;
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
	}*/
}

void Ball::Update(float delta) {
	this->vector *= delta;
	
	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
	else {
		if (this->isDestroyble) {
			delete this;
			return;
		}

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

	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;
}

void Ball::ResetPoints() {
	points = 0;
}

void Ball::Collision(Player* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
	&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			//this->vector.x = this->dstBox.x + this->dstBox.w - object->GetDstBox().x;
			this->collision[RIGHT] = true;
			//std::cout << "Ball - RIGHT\n";
		}
		if (this->vector.x < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[LEFT] = true;
			//std::cout << "Ball - LEFT\n";
		}
		if (this->vector.y > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[DOWN] = true;
			//std::cout << "Ball - DOWN\n";
		}
		if (this->vector.y < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[UP] = true;
			//std::cout << "Ball - UP\n";
		}
		if (object->IsDestroyble()) {
			delete object;
			playerOwnerId = -1;
			return;
		}
		else
			playerOwnerId = object->GetPlayerId();
	}
}

void Ball::Collision(Wall* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
	&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x > 0 && this->dstBox.x + this->dstBox.w + this->vector.x * delta >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[RIGHT] = true;
			//std::cout << "Ball - RIGHT\n";
		}
		if (this->vector.x < 0 && this->dstBox.x + this->vector.x * delta <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[LEFT] = true;
			//std::cout << "Ball - LEFT\n";
		}
		if (this->vector.y > 0 && this->dstBox.y + this->dstBox.h + this->vector.y * delta >= object->GetDstBox().y
			&& this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w + this->vector.x * delta > object->GetDstBox().x) {

			this->collision[DOWN] = true;
			//std::cout << "Ball - DOWN\n";
		}
		if (this->vector.y < 0 && this->dstBox.y + this->vector.y * delta <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[UP] = true;
			//std::cout << "Ball - UP\n";
		}
		playerOwnerId = -1;
	}
}

bool Ball::Collision(Brick* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
	&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[RIGHT] = true;
			//std::cout << "Ball - RIGHT\n";
		}
		if (this->vector.x < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[LEFT] = true;
			//std::cout << "Ball - LEFT\n";
		}
		if (this->vector.y > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[DOWN] = true;
			//std::cout << "Ball - DOWN\n";
		}
		if (this->vector.y < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[UP] = true;
			//std::cout << "Ball - UP\n";
		}
		if (object->IsDestroyble() && object->GetPoints() > 0) {
			points += object->GetPoints();

			delete object;
		}

		playerOwnerId = -1;
		return true;
	} else
		return false;
	
}
