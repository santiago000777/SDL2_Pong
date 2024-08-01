#include "common.h"
#include "Game.h"

Game::Game(const std::string& windowName, int posX, int posY, int windowWidth, int windowHeight, int flags) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow(windowName.c_str(), posX, posY, windowWidth, windowHeight, flags);
	SRenderer::Init(window, {0, 0, windowWidth, windowHeight });
	
	
	firstUpdate = std::chrono::high_resolution_clock::now();
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
	if (durationUpdate.count() >= deltaTime/4) {
		Basket();

		if (bricks.size() == 0) {
			isEnd = true;
		}

		MovableObject::deltaT = durationUpdate.count();
		//std::cout << durationUpdate.count() << " ms\n";

		firstUpdate = std::chrono::high_resolution_clock::now();

		HandleEvents();
		Collision();
		Update();
	}
	secondUpdate = std::chrono::high_resolution_clock::now();

	durationFrame = std::chrono::duration_cast<std::chrono::milliseconds>(secondFrame - firstFrame);
	if (durationFrame.count() >= deltaTime) {
		
		if (PressedKey(VK_SPACE)) {
			balls[0]->ResetPosition();
			players[0]->ResetPosition();
		}
		firstFrame = std::chrono::high_resolution_clock::now();
		Render();
	}
	secondFrame = std::chrono::high_resolution_clock::now();
}

void Game::SetBackground(const std::string& BGpath) {
	background = new Background(BGpath);
}

int Game::GetCountOfBricks() const {
	return bricks.size();
}

bool Game::IsEnd() {
	return isEnd;
}

void Game::Basket() {
	for (int i = 0; i < walls.size(); i++) {
		if (!walls[i]->isAlive) {
			delete walls[i];
			walls.erase(walls.begin() + i);
		}
	}
	for (int i = 0; i < bricks.size(); i++) {
		if (!bricks[i]->isAlive) {
			delete bricks[i];
			bricks.erase(bricks.begin() + i);
		}
	}
	for (int i = 0; i < balls.size(); i++) {
		if (!balls[i]->isAlive) {
			delete balls[i];
			balls.erase(balls.begin() + i);
		}
	}
	for (int i = 0; i < players.size(); i++) {
		if (!players[i]->isAlive) {
			delete players[i];
			players.erase(players.begin() + i);
		}
	}
}

void Game::Render() {
	SDL_RenderClear(SRenderer::Get().Renderer());

	background->Render();
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

void Game::Update() {
		// Update
	for (auto& ball : balls) {
		ball->Update();
	}
	for (auto& player : players) {
		player->Update();
	}

		// Game over logic
	int uncatchedBalls = 0;
	for (auto ball : balls) {
		if (ball->GetDstBox().y > 820) {
			uncatchedBalls++;
			ball->isAlive = false;
		}
	}
	for (auto& player : players) {
		player->DecreaseLives(uncatchedBalls);
	}
	for (auto& player : players) {
		if (player->IsGameOver()) {
			player->isAlive = false;
			isEnd = true;
		}
		else if (player->isAlive && uncatchedBalls > 0) {
			for (auto ball : balls) {
				if (!ball->isAlive) {
					ball->ResetPosition();
					ball->ResetPoints();
					ball->isAlive = true;
				}
			}
		}
	}
}

void Game::HandleEvents() {
	for (auto player : players) {
		player->HandleEvents();
	}
	for (auto ball : balls) {
		ball->HandleEvents();
	}
}

void Game::Collision() {
	for (auto& ball : balls) {
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
			MovableObject::Collision(*player, *ball);
		}
	}

	for (auto& ball : balls) {
		for (int i = 0; i < bricks.size(); i++) {
			if (MovableObject::Collision(*ball, *bricks[i])) {
				if (bricks[i]->GetCurrentSprite() == 1) {
					ball->AddPoints(bricks[i]->GetPoints());
					bricks[i]->isAlive = false;
				}
				bricks[i]->ChangeSprite();
			}
		}
	}

	for (auto& player : players) {
		for (auto wall : walls) {
			MovableObject::Collision(*player, *wall);
		}
	}
}
