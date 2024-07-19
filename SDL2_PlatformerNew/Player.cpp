#include "common.h"
#include "Player.h"
#include "Object.h"

Player::Player(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect) 
	: dstBox(dstBox), srcBox(from), windowRect(windowRect) {

	texture.reset(Texture::Create(path, 255, 255, 255, 255));
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
	if (PressedKey((short)eControls::UP)) {
		vector.y = -1;
	}
	if (PressedKey((short)eControls::LEFT)) {
		vector.x = -1;
	}
	if (PressedKey((short)eControls::DOWN)) {
		vector.y = 1;
	}
	if (PressedKey((short)eControls::RIGHT)) {
		vector.x = 1;
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

void Player::Render() {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

bool Player::IsDestroyble() {
	return isDestroyble;
}

void Player::Update(float delta) {
	

	if (!this->collision[(int)eIndex::LEFT] && !this->collision[(int)eIndex::RIGHT] && !this->collision[(int)eIndex::UP] && !this->collision[(int)eIndex::DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
	else {
		if (this->isDestroyble) {
			delete this;
			return;
		}

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
	}
	
	this->collision[(int)eIndex::LEFT] = false;
	this->collision[(int)eIndex::RIGHT] = false;
	this->collision[(int)eIndex::UP] = false;
	this->collision[(int)eIndex::DOWN] = false;
}

SDL_Rect Player::GetDstBox() const {
	return dstBox;
}

void Player::Collision(Wall* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
		&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[(int)eIndex::RIGHT] = true;
			std::cout << "Player - RIGHT\n";
		}
		if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[(int)eIndex::LEFT] = true;
			std::cout << "Player - LEFT\n";
		}
		if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[(int)eIndex::DOWN] = true;
			std::cout << "Player - DOWN\n";
		}
		if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[(int)eIndex::UP] = true;
			std::cout << "Player - UP\n";
		}

		if (object->IsDestroyble()) {
			delete object;
			return;
		}
	}
}

bool Player::IsGameOver() {
	if(lives <= 0)
		return true;
	return false;
}

void Player::AddLives(int i) {
	lives += i;
}
