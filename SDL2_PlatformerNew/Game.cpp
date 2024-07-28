#include "common.h"
#include "Game.h"

Game::Game(const std::string& windowName, int posX, int posY, int windowWidth, int windowHeight, int flags) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow(windowName.c_str(), posX, posY, windowWidth, windowHeight, flags);
	SRenderer::Init(window);
	
	
	this->windowRect = { 0, 0, windowWidth, windowHeight };
}

Game::~Game() {
	for (auto& wall : walls) {
		delete wall;
	}
	for (auto& ball : balls) {
		delete ball;
	}
	for (auto& player : players) {
		delete player;
	}
	for (auto& brick : bricks) {
		delete brick;
	}
	delete background;
	SDL_DestroyWindow(window);
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
		Render();
	}
	secondFrame = std::chrono::high_resolution_clock::now();
}

/*
	==GameLoop==
	
	std::chrono::time_point<std::chrono::high_resolution_clock> firstCollision, secondCollision, firstFrame, secondFrame;
	{
		durationCollision = std::chrono::duration_cast<std::chrono::milliseconds>(secondCollision - firstCollision);
		if(durationCollision >= deltaTime/4) {		-> 4x rychlejsi nez vykresleni
			firstCollision = std::chrono::high_resolution_clock::now();
			Collision();	-> kontrola kolize u vsech objektu
		}
		secondCollision = std::chrono::high_resolution_clock::now();

		durationFrame = std::chrono::duration_cast<std::chrono::milliseconds>(secondFrame - firstFrame);
		if (durationFrame.count() >= deltaTime) {
	}
	....
*/

void Game::SetBackground(const std::string& BGpath) {
	background = new Background(windowRect.w, windowRect.h, BGpath);
}

bool Game::IsGameOver() {
	return isGameOver;
}

void Game::Render() {
	SDL_RenderClear(SRenderer::Get().Renderer());

	background->Render(&windowRect);
	for (auto& wall : walls) {
		wall->Render();
	}
	for (auto& brick : bricks) {
		brick->Render();
	}
	for (auto& ball : balls) {
		ball->Render();
	}
	for (auto& player : players) {
		player->Render();
	}

	SDL_RenderPresent(SRenderer::Get().Renderer());
}

void Game::Update(float delta) {
		// Collision&HandleEvents
	for (auto& ball : balls) {
			// HandleEvents++
		for (auto wall : walls) {
			MovableObject::Collision(*ball, *wall);
		}
	}
	for (auto& ball : balls) {
		for (auto player : players) {
			if (MovableObject::Collision(*ball, *player)) {
				ball->SetOwnerId(player->GetPlayerId());
				if (ball->GetOwnerId() == player->GetPlayerId() && ball->GetPoints() > 0) {
					player->AddPoints(ball->GetPoints());
					ball->ResetPoints();
				}
			}
		}
	}
	for (auto& ball : balls) {
		for (int i = 0; i < bricks.size(); i++) {
			if (MovableObject::Collision(*ball, *bricks[i])) {
				ball->AddPoints(bricks[i]->GetPoints());
				delete bricks[i];
				bricks.erase(bricks.begin() + i);
			}
		}
	}
		
		// ???
		// Update
	for (auto& ball : balls) {
			//HandleEvents--
		ball->HandleEvents(delta);
		ball->Update();
	}
		// ???

		// Collision&HandleEvents
	for (auto& player : players) {
		player->HandleEvents(delta);
		for (auto wall : walls) {
			MovableObject::Collision(*player, *wall);
		}
	}

		// Update
	for (auto& player : players) {
		player->Update();
	}

		// Game over logic
	int uncatchedBalls = 0;
	for (auto ball : balls) {
		if (ball->GetDstBox().y > 820) {
			uncatchedBalls++;
		}
	}
	for (auto& player : players) {
		player->DecreaseLives(uncatchedBalls);
	}
	for (auto& player : players) {
		if (player->IsGameOver()) {
			isGameOver = true;
		}
	}
}
