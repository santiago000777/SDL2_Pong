#include "common.h"
#include "Player.h"

int Player::playerCount = 0;


Player::Player(Vec4f box, const std::string& path, int characterWidth)
	: MovableObject(box, path, characterWidth) {
	idPlayer = playerCount;
	playerCount++;
}

//Player::Player(const Player& rhs) 
//	: Object(rhs) {
//}
//
//Player::Player(Player&& rhs)
//	: Object(rhs) {
//
//}

Player::Player(Player&& rhs) 
	: MovableObject(std::move(rhs)){

	lives = rhs.lives;
	points = rhs.points;
	path = "Pictures/paddle.bmp"; 
	auto [tex, _] = CreateTexture(path, 255, 0, 255, 255);
	texture.reset(tex);
}

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

void Player::Update() {

	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->box.x += vector.x * MovableObject::deltaT;
		this->box.y += vector.y * MovableObject::deltaT;
		currentSprite = 0;
		return;
	}
	if (this->isDestroyble) {
		isAlive = false;
		return;
	}

	if (this->collision[LEFT]) {

		if (this->vector.x > 0 && !this->collision[RIGHT])
			this->box.x += this->vector.x * MovableObject::deltaT;

		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->box.y += this->vector.y * MovableObject::deltaT;
		}
	}
	if (this->collision[RIGHT]) {

		if (this->vector.x < 0 && !this->collision[LEFT]) {
			this->box.x += this->vector.x * MovableObject::deltaT;
		}
		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->box.y += this->vector.y * MovableObject::deltaT;
		}
	}
	if (this->collision[UP]) {

		if (this->vector.y > 0 && !this->collision[DOWN])
			this->box.y += this->vector.y * MovableObject::deltaT;

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->box.x += this->vector.x * MovableObject::deltaT;
		}
	}
	if (this->collision[DOWN]) {

		if (this->vector.y < 0 && !this->collision[UP])
			this->box.y += this->vector.y * MovableObject::deltaT;

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->box.x += this->vector.x * MovableObject::deltaT;
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

int Player::GetLives() const {
	return lives;
}

int Player::GetPoints() const {
	return points;
}

void Player::AddPoints(int points) {
	this->points += points;
}


void Player::Save(File& file) {
	file.Save(srcBox);
	file.Save(box);
	file.Save(currentSprite);

	file.Save(vector);

	file.Save(lives);
	file.Save(points);
}

void Player::Load(File& file) {
	idPlayer = playerCount;
	playerCount++;

	file.Load(srcBox);
	file.Load(box);
	file.Load(currentSprite);

	file.Load(vector);

	file.Load(lives);
	file.Load(points);
}


bool Player::IsGameOver() const {
	if (lives <= 0)
		return true;
	return false;
}

void Player::DecreaseLives(int i) {
	lives -= i;
}

void Player::ResetPosition() {
	box.x = 255.0f;
	box.y = 750.0f;
}