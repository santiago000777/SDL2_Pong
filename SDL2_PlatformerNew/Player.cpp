#include "common.h"
#include "Player.h"
#include "Object.h"

int Player::playerCount = 0;

Player::Player(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: MovableObject(dstBox, path, characterWidth) {
	idPlayer = playerCount;
	playerCount++;
}

//Player::Player(const Player& rhs) 
//	: Object(rhs) {
//}
//
//Player::Player(Player&& rhs)
//	: Object(std::move(rhs)) {
//}

Player::~Player() {
	std::cout << "Deleted player\n";
}

//void Player::operator=(const Player& rhs) {
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
//
//void Player::operator=(Player&& rhs) {
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

void Player::HandleEvents() {
	vector.x = 0;
	vector.y = 0;

	if (PressedKey((short)eControls::LEFT)) {
		vector.x += -1;
	}
	if (PressedKey((short)eControls::RIGHT)) {
		vector.x += 1;
	}

	
}

void Player::Render() {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

bool Player::IsDestroyble() {
	return isDestroyble;
}

void Player::Update(std::vector<Wall*>* others, float delta) {
	CollisionPoint(others, delta);

	if (this->collision[(int)eIndex::LEFT]) {

		if (this->vector.x > 0 && !this->collision[(int)eIndex::RIGHT])
			this->dstBox.x += roundf(this->vector.x * delta);

		if (this->vector.y < 0 && !this->collision[(int)eIndex::UP]
			|| this->vector.y > 0 && !this->collision[(int)eIndex::DOWN]) {

			this->dstBox.y += roundf(this->vector.y * delta);
		}
	}
	if (this->collision[(int)eIndex::RIGHT]) {

		if (this->vector.x < 0 && !this->collision[(int)eIndex::LEFT]) {
			this->dstBox.x += roundf(this->vector.x * delta);
		}
		if (this->vector.y < 0 && !this->collision[(int)eIndex::UP]
			|| this->vector.y > 0 && !this->collision[(int)eIndex::DOWN]) {

			this->dstBox.y += roundf(this->vector.y * delta);
		}
	}
	if (this->collision[(int)eIndex::UP]) {

		if (this->vector.y > 0 && !this->collision[(int)eIndex::DOWN])
			this->dstBox.y += roundf(this->vector.y * delta);

		if (this->vector.x < 0 && !this->collision[(int)eIndex::LEFT]
			|| this->vector.x > 0 && !this->collision[(int)eIndex::RIGHT]) {

			this->dstBox.x += roundf(this->vector.x * delta);
		}
	}
	if (this->collision[(int)eIndex::DOWN]) {

		if (this->vector.y < 0 && !this->collision[(int)eIndex::UP])
			this->dstBox.y += roundf(this->vector.y * delta);

		if (this->vector.x < 0 && !this->collision[(int)eIndex::LEFT]
			|| this->vector.x > 0 && !this->collision[(int)eIndex::RIGHT]) {

			this->dstBox.x += roundf(this->vector.x * delta);
		}
	}
	if (!this->collision[(int)eIndex::LEFT] && !this->collision[(int)eIndex::RIGHT] && !this->collision[(int)eIndex::UP] && !this->collision[(int)eIndex::DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
}

SDL_Rect Player::GetDstBox() const {
	return dstBox;
}

void Player::CollisionPoint(std::vector<Wall*>* others, float delta) {
	this->collision[(int)eIndex::LEFT] = false;
	this->collision[(int)eIndex::RIGHT] = false;
	this->collision[(int)eIndex::UP] = false;
	this->collision[(int)eIndex::DOWN] = false;

	for (auto object : *others) {

		if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
			&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

			if (this->isDestroyble) {
				delete this;
				return;
			}

			if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
				&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

				this->collision[(int)eIndex::RIGHT] = true;
				std::cout << "RIGHT\n";
			}
			if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
				&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

				this->collision[(int)eIndex::LEFT] = true;
				std::cout << "LEFT\n";
			}
			if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
				&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

				this->collision[(int)eIndex::DOWN] = true;
				std::cout << "DOWN\n";
			}
			if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
				&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

				this->collision[(int)eIndex::UP] = true;
				std::cout << "UP\n";
			}

			if (object->IsDestroyble()) {
				delete object;
				return;
			}
		}
	}
}

void Player::Update() {
	
	std::cout << "Player - " << points << "\n";

	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * MovableObject::deltaT);
		this->dstBox.y += roundf(vector.y * MovableObject::deltaT);
		currentSprite = 0;
		return;
	}
	if (this->isDestroyble) {
		isAlive = false;
		return;
	}

	if (this->collision[LEFT]) {

		if (this->vector.x > 0 && !this->collision[RIGHT])
			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);

		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);
		}
	}
	if (this->collision[RIGHT]) {

		if (this->vector.x < 0 && !this->collision[LEFT]) {
			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);
		}
		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);
		}
	}
	if (this->collision[UP]) {

		if (this->vector.y > 0 && !this->collision[DOWN])
			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);
		}
	}
	if (this->collision[DOWN]) {

		if (this->vector.y < 0 && !this->collision[UP])
			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);
		}
	}

	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;
}

int Player::GetPlayerId() const {
	return idPlayer;
}

void Player::AddPoints(int points) {
	this->points += points;
}

bool Player::IsGameOver() const {
	if(lives <= 0)
		return true;
	return false;
}

void Player::AddLives(int i) {
	lives += i;
}

void Player::ResetPosition() {
	dstBox.x = 255;
	dstBox.y = 750;
}
