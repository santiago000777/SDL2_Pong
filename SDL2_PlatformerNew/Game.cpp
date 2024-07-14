#include "common.h"
#include "Game.h"

Game::Game(const std::string& windowName, int posX, int posY, int windowWidth, int windowHeight, int flags) {
	SDL_Init(SDL_INIT_EVERYTHING);

	this->window = SDL_CreateWindow(windowName.c_str(), posX, posY, windowWidth, windowHeight, flags);
	this->windowRect.x = 0;
	this->windowRect.y = 0;
	this->windowRect.w = windowWidth;
	this->windowRect.h = windowHeight;

	this->renderer = SDL_CreateRenderer(window, -1, 1);
}

Game::~Game() {
	for (auto& object : objects) {
		delete object;
	}
	delete backGround;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::Loop() {
	durationUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(secondUpdate - firstUpdate);
	if (durationUpdate.count() >= updateDelta) {
		firstUpdate = std::chrono::high_resolution_clock::now();

		Update(/*durationPosun.count()**/1/*0*/);
	}
	secondUpdate = std::chrono::high_resolution_clock::now();

	durationFrame = std::chrono::duration_cast<std::chrono::milliseconds>(secondFrame - firstFrame);
	if (durationFrame.count() >= deltaTime) {
		firstFrame = std::chrono::high_resolution_clock::now();
		Clear();
		Render();
	}
	secondFrame = std::chrono::high_resolution_clock::now();
}

void Game::SetBackGround(const std::string& BGpath) {
	backGround = new BackGround(windowRect.w, windowRect.h, BGpath, renderer);
	for (auto& object : objects) {
		object->SetBackground(backGround);
	}
}

void Game::Render() {
	SDL_RenderClear(renderer);

	backGround->Render(&windowRect);
	for (auto& object : objects) {
		object->Render();
	}

	SDL_RenderPresent(renderer);
}

void Game::Clear() {
	for (auto& object : objects) {
		object->Clear();
	}
}

void Game::Update(float delta) {
	for (auto& object : objects) {
		object->HandleEvents();
		object->Update(&objects, delta);
	}
}
