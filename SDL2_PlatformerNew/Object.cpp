#include "common.h"
#include "Object.h"
#include "Renderer.h"

std::vector<Player*>* Object::players = nullptr;

Object::Object(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox, SDL_Rect windowRect)
	: dstBox(dstBox), srcBox(fromBox), windowRect(windowRect) {

	texture.reset(Texture::Create(path, 255, 255, 255, 255));
}

//Object::Object(const Object& rhs) {
//	this->dstBox = rhs.dstBox;
//	this->srcBox = rhs.srcBox;
//	this->windowRect = rhs.windowRect;
//	this->isDestroyble = rhs.isDestroyble;
//	this->path = rhs.path;
//	this->vector = rhs.vector;
//
//	this->renderer = rhs.renderer;
//	this->texture = Texture::Create(renderer, path);
//	*this->background = *rhs.background;
//	memcpy(this->collision, rhs.collision, 4 * sizeof(bool));
//}
//
//Object::Object(Object&& rhs) {
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

Object::~Object() {

}

//void Object::operator=(const Object& rhs) {
//	this->dstBox = rhs.dstBox;
//	this->srcBox = rhs.srcBox;
//	this->windowRect = rhs.windowRect;
//	this->isDestroyble = rhs.isDestroyble;
//	this->path = rhs.path;
//	this->vector = rhs.vector;
//
//	this->renderer = rhs.renderer;
//	this->texture = Texture::Create(renderer, path);
//	*this->background = *rhs.background;
//	memcpy(this->collision, rhs.collision, 4 * sizeof(bool));
//}
//
//void Object::operator=(Object&& rhs) {
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

bool Object::IsDestroyble() {
	return isDestroyble;
}

void Object::Render() {
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox); // nullptr -> pro cely obr.
}

void Object::HandleEvents() {
	vector = { 0, 0 };
	
}

void Object::Update(std::vector<Object*>* otherObjects, float delta) {
	CollisionPoint(otherObjects, delta);

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
	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
}

SDL_Rect Object::GetPosition() const {
	return dstBox;
}

bool Object::IsCollision(Object* otherObjects, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > otherObjects->dstBox.x && this->dstBox.x + this->vector.x * delta < otherObjects->dstBox.x + otherObjects->dstBox.w) && (this->dstBox.y + this->vector.y * delta + this->dstBox.h > otherObjects->dstBox.y && this->dstBox.y + this->vector.y * delta < otherObjects->dstBox.y + otherObjects->dstBox.h)) {

		return true;
	} else return false;
}

int Object::GetPoints() const {
	return points;
}

void Object::CollisionPoint(std::vector<Object*>* otherObjects, float delta) {
	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;

	for (auto& object : *otherObjects) {
		if (object == this) {
			continue;
		}

		if (IsCollision(object, delta)) {

			if (this->isDestroyble) {
				delete this;
				return;
			}

			if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetPosition().x
				&& this->dstBox.y < object->GetPosition().y + object->GetPosition().h && this->dstBox.y + this->dstBox.h > object->GetPosition().y) {

				this->collision[RIGHT] = true;
				std::cout << "RIGHT\n";
			}
			if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetPosition().x + object->GetPosition().w
				&& this->dstBox.y < object->GetPosition().y + object->GetPosition().h && this->dstBox.y + this->dstBox.h > object->GetPosition().y) {

				this->collision[LEFT] = true;
				std::cout << "LEFT\n";
			}
			if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetPosition().y
				&& this->dstBox.x < object->GetPosition().x + object->GetPosition().w && this->dstBox.x + this->dstBox.w > object->GetPosition().x) {

				this->collision[DOWN] = true;
				std::cout << "DOWN\n";
			}
			if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetPosition().y + object->GetPosition().h
				&& this->dstBox.x < object->GetPosition().x + object->GetPosition().w && this->dstBox.x + this->dstBox.w > object->GetPosition().x) {

				this->collision[UP] = true;
				std::cout << "UP\n";
			}

			if (object->IsDestroyble()) {
				for(auto& player : *players)
				delete object;
			}
		}
	}
}

void Object::SetPlayers(std::vector<Player*>* p) {
	players = p;
}
