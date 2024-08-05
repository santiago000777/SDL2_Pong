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
	for (auto& bubble : bubbles) {
		delete bubble;
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
		
		firstFrame = std::chrono::high_resolution_clock::now();
		Render();
	}
	secondFrame = std::chrono::high_resolution_clock::now();
}

void Game::Start() {
	int sec = 0;
	SDL_RenderClear(SRenderer::Get().Renderer());
	background->Render();
	SDL_RenderPresent(SRenderer::Get().Renderer());

	while (sec < 3) {
		durationUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - firstUpdate);
		if (durationUpdate.count() >= 1000) {
			std::cout << sec + 1 << "...\n";
			sec++;
			firstUpdate = std::chrono::high_resolution_clock::now();
		}
	}
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
	auto lDeleteIfIsNotAlive = [](Object* obj) {
		if (!obj->isAlive) {
			delete obj;
			return true;
		} else
			return false;
	};

	walls.erase(std::remove_if(walls.begin(), walls.end(), lDeleteIfIsNotAlive), walls.end());
	bricks.erase(std::remove_if(bricks.begin(), bricks.end(), lDeleteIfIsNotAlive), bricks.end());
	balls.erase(std::remove_if(balls.begin(), balls.end(), lDeleteIfIsNotAlive), balls.end());
	players.erase(std::remove_if(players.begin(), players.end(), lDeleteIfIsNotAlive), players.end());
	bubbles.erase(std::remove_if(bubbles.begin(), bubbles.end(), lDeleteIfIsNotAlive), bubbles.end());
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
	for (auto& bubble : bubbles) {
		bubble->Render();
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
	for (auto& bubble : bubbles) {
		bubble->Update();
	}
		// Bubble logic
	for (auto& ball : balls) {
		for (auto& bubble : bubbles) {
			if (MovableObject::Collision(*bubble, *ball)) {
				bubble->isAlive = false;
				balls.push_back(new Ball({ bubble->GetDstBox().x, bubble->GetDstBox().y, ball->GetDstBox().w, ball->GetDstBox().h }, ball->GetPath(), ball->GetSpriteWidth()));
			}
		}
	}

		// Game over logic
	int uncatchedBalls = 0;
	for (auto ball : balls) {
		if (MovableObject::Collision(*ball, gameOverRect)) {
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
				if (!ball->isAlive && balls.size() == 1) {
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
}

void Game::Collision() {
	for (auto& ball : balls) {
		for (auto wall : walls) {
			MovableObject::Collision(*ball, *wall);
		}
	}

	for (auto& wall : walls) {
		for (auto& bubble : bubbles) {
			MovableObject::Collision(*bubble, *wall);
		}
	}
	for (auto& bubble : bubbles) {
		MovableObject::Collision(*bubble, gameOverRect);
	}

	for (auto& ball : balls) {
		for (auto player : players) {
			if (MovableObject::Collision(*ball, *player)) {
				if (ball->GetOwnerId() == player->GetPlayerId() && ball->GetPoints() != 0) {
					player->AddPoints(ball->GetPoints());
					ball->ResetPoints();
				}
				ball->SetOwnerId(player->GetPlayerId());
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
				else {
					bricks[i]->ChangeSprite();
				}
			}
		}
	}

	if (balls.size() > 1) {
		for (int j = 0; j < balls.size(); j++) {
			for (int i = j + 1; i < balls.size(); i++) {
				if (j == i) continue;
				if (MovableObject::Collision(*balls[j], *balls[i])) {
					int tempPoints = balls[j]->GetPoints();
					balls[j]->SetPoints(balls[i]->GetPoints());
					balls[i]->SetPoints(tempPoints);
				}
			}
		}
	}

	for (auto& player : players) {
		for (auto wall : walls) {
			MovableObject::Collision(*player, *wall);
		}
	}
}
