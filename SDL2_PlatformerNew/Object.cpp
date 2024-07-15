#include "common.h"
#include "Object.h"

Object::Object(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect)
	: dstBox(dstBox), renderer(renderer), srcBox(fromBox), windowRect(windowRect) {

	texture = Texture::Create(renderer, path);
}

Object::Object(Object&& rhs) {
	this->dstBox = rhs.dstBox;
	this->srcBox = rhs.srcBox;
	this->windowRect = rhs.windowRect;

	this->renderer = rhs.renderer;
	rhs.renderer = NULL;
	this->texture = rhs.texture;
	rhs.texture = NULL;
}

Object::~Object() {
	SDL_DestroyTexture(texture);
	std::cout << "Deleted Object!" << std::endl;
}

void Object::operator=(const Object& rhs) {
}

void Object::operator=(Object&& rhs) {
}

void Object::SetBackground(Background* bg) {
	background = bg;
}

bool Object::IsDestroyble() {
	return isDestroyble;
}

void Object::Render() {
	SDL_RenderCopy(renderer, texture, &srcBox, &dstBox); // NULL -> pro cely obr.
}

void Object::HandleEvents() {
	vector = { 0, 0 };
}

void Object::Update(std::vector<Object*>* otherObjects, float delta) {
	CollisionPoint(otherObjects, delta);

	if (this->collision[LEFT]) {

		if (this->vector.x > 0 && !this->collision[RIGHT])
			this->dstBox.x += this->vector.x * delta;

		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->dstBox.y += this->vector.y * delta;
		}
	}
	if (this->collision[RIGHT]) {

		if (this->vector.x < 0 && !this->collision[LEFT]) {
			this->dstBox.x += this->vector.x * delta;
		}
		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->dstBox.y += this->vector.y * delta;
		}
	}
	if (this->collision[UP]) {

		if (this->vector.y > 0 && !this->collision[DOWN])
			this->dstBox.y += this->vector.y * delta;

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->dstBox.x += this->vector.x * delta;
		}
	}
	if (this->collision[DOWN]) {

		if (this->vector.y < 0 && !this->collision[UP])
			this->dstBox.y += this->vector.y * delta;

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->dstBox.x += this->vector.x * delta;
		}
	}
	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += vector.x * delta;
		this->dstBox.y += vector.y * delta;
	}
}

void Object::Clear() {
	SDL_RenderCopy(renderer, background->GetTexture(), &srcBox, &dstBox);
}

void Object::CollisionPoint(std::vector<Object*>* otherObjects, float delta) {
	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;

	for (int i = 0; i < otherObjects->size(); i++) {
		if (otherObjects->at(i) == this) {
			continue;
		}

		if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > otherObjects->at(i)->dstBox.x && this->dstBox.x + this->vector.x * delta < otherObjects->at(i)->dstBox.x + otherObjects->at(i)->dstBox.w)
			&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > otherObjects->at(i)->dstBox.y && this->dstBox.y + this->vector.y * delta < otherObjects->at(i)->dstBox.y + otherObjects->at(i)->dstBox.h)) {

			if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= otherObjects->at(i)->dstBox.x
				&& this->dstBox.y < otherObjects->at(i)->dstBox.y + otherObjects->at(i)->dstBox.h && this->dstBox.y + this->dstBox.h > otherObjects->at(i)->dstBox.y) {

				this->collision[RIGHT] = true;
				std::cout << "RIGHT\n";
			}
			if (this->vector.x * delta < 0 && this->dstBox.x <= otherObjects->at(i)->dstBox.x + otherObjects->at(i)->dstBox.w
				&& this->dstBox.y < otherObjects->at(i)->dstBox.y + otherObjects->at(i)->dstBox.h && this->dstBox.y + this->dstBox.h > otherObjects->at(i)->dstBox.y) {

				this->collision[LEFT] = true;
				std::cout << "LEFT\n";
			}
			if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= otherObjects->at(i)->dstBox.y
				&& this->dstBox.x < otherObjects->at(i)->dstBox.x + otherObjects->at(i)->dstBox.w && this->dstBox.x + this->dstBox.w > otherObjects->at(i)->dstBox.x) {

				this->collision[DOWN] = true;
				std::cout << "DOWN\n";
			}
			if (this->vector.y * delta < 0 && this->dstBox.y <= otherObjects->at(i)->dstBox.y + otherObjects->at(i)->dstBox.h
				&& this->dstBox.x < otherObjects->at(i)->dstBox.x + otherObjects->at(i)->dstBox.w && this->dstBox.x + this->dstBox.w > otherObjects->at(i)->dstBox.x) {

				this->collision[UP] = true;
				std::cout << "UP\n";
			}
		}
	}
}
