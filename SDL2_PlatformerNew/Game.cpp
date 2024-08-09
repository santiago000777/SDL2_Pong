#include "common.h"
#include "Game.h"

SGame sGame;

IGame& Game::Get() {
	return sGame;
}

SGame::~SGame() {
	SDL_Quit();
}

void SGame::Init(const std::string& windowName, int posX, int posY, int windowWidth, int windowHeight, int flags) {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window.reset(SDL_CreateWindow(windowName.c_str(), posX, posY, windowWidth, windowHeight, flags));
	Renderer::Get().Init(window.get(), { 0, 0, windowWidth, windowHeight });

	firstUpdate = std::chrono::high_resolution_clock::now();
}

void SGame::Loop() {

	durationUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(secondUpdate - firstUpdate);
	if (durationUpdate.count() >= deltaTime / 4) {
		Basket();

		if (bricks.size() == 0) {
			isEnd = true;
		}

		MovableObject::deltaT = (float)durationUpdate.count();
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

void SGame::Start() {
	int sec = 0;
	SDL_RenderClear(Renderer::Get().Renderer());
	background->Render();
	SDL_RenderPresent(Renderer::Get().Renderer());

	while (sec < 3) {
		durationUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - firstUpdate);
		if (durationUpdate.count() >= 1000) {
			std::cout << sec + 1 << "...\n";
			sec++;
			firstUpdate = std::chrono::high_resolution_clock::now();
		}
	}
}

void SGame::SetBackground(const std::string& BGpath) {
	background = std::make_unique<Background>(BGpath);
}

int SGame::CountOfBricks() const {
	return bricks.size();
}

bool SGame::IsEnd() {
	return isEnd;
}

void SGame::AddWall(SDL_Rect dstBox, const std::string& path, int characterWidth) {
	walls.push_back(std::make_unique<Wall>(dstBox, path, characterWidth));
}

void SGame::AddPlayer(SDL_Rect dstBox, const std::string& path, int characterWidth) {
	players.push_back(std::make_unique<Player>(dstBox, path, characterWidth));
}

void SGame::AddBall(SDL_Rect dstBox, const std::string& path, int characterWidth) {
	balls.push_back(std::make_unique<Ball>(dstBox, path, characterWidth));
}

void SGame::AddBrick(SDL_Rect dstBox, const std::string& path, int characterWidth) {
	bricks.push_back(std::make_unique<Brick>(dstBox, path, characterWidth));
}

void SGame::AddBubble(SDL_Rect dstBox, const std::string& path, int characterWidth) {
	bubbles.push_back(std::make_unique<Bubble>(dstBox, path, characterWidth));
}

void SGame::AddBomb(SDL_Rect dstBox, const std::string& path, int characterWidth) {
	bombs.push_back(std::make_unique<Bomb>(dstBox, path, characterWidth));
}

void SGame::Basket() {
	std::erase_if(walls, [](const std::unique_ptr<Wall>& obj) { return !obj->isAlive; });
	std::erase_if(bricks, [](const std::unique_ptr<Brick>& obj) { return !obj->isAlive; });
	std::erase_if(balls, [](const std::unique_ptr<Ball>& obj) { return !obj->isAlive; });
	std::erase_if(players, [](const std::unique_ptr<Player>& obj) { return !obj->isAlive; });
	std::erase_if(bubbles, [](const std::unique_ptr<Bubble>& obj) { return !obj->isAlive; });
	std::erase_if(bombs, [](const std::unique_ptr<Bomb>& obj) { return !obj->isAlive; });
}

void SGame::Render() {
	SDL_RenderClear(Renderer::Get().Renderer());

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
	for (auto& bomb : bombs) {
		bomb->Render();
	}

	SDL_RenderPresent(Renderer::Get().Renderer());
}

void SGame::Update() {
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
				SDL_Rect pom = { bubble->GetDstBox().x, bubble->GetDstBox().y, ball->GetDstBox().w, ball->GetDstBox().h };
				balls.push_back(std::make_unique<Ball>(pom, ball->GetPath(), ball->GetSpriteWidth()));
			}
		}
	}

	// Bomb logic
	for (auto& ball : balls) {
		for (auto& bomb : bombs) {
			if (MovableObject::Collision(*ball, *bomb)) {
				bomb->canDetonate = true;
				bomb->ChangeSprite();
				if (bomb->isAlive)
					bomb->isAlive = false;
			}
		}
	}

	for (auto& bomb : bombs) {
		for (auto& brick : bricks) {
			if (bomb->canDetonate && MovableObject::Collision(*brick, bomb->GetRange())) {
				bomb->AddPoints(brick->GetPoints());
				brick->isAlive = false;
			}
		}
	}

	for (auto& ball : balls) {
		for (auto& bomb : bombs) {
			if (bomb->canDetonate) {
				ball->AddPoints(bomb->GetPoints());
			}
		}
	}

	// SGame over logic
	int uncatchedBalls = 0;
	for (auto& ball : balls) {
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
		} else if (player->isAlive && uncatchedBalls > 0) {
			for (auto& ball : balls) {
				if (!ball->isAlive && balls.size() == 1) {
					ball->ResetPosition();
					ball->ResetPoints();
					ball->isAlive = true;
				}
			}
		}
	}
}

void SGame::HandleEvents() {
	for (auto& player : players) {
		player->HandleEvents();
	}
}

void SGame::Collision() {
	for (auto& ball : balls) {
		for (auto& wall : walls) {
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
		for (auto& player : players) {
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
				} else {
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
		for (auto& wall : walls) {
			MovableObject::Collision(*player, *wall);
		}
	}
}