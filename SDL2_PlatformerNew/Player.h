#pragma once

class Player : public Object {
public:
    Player(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect);
    // copy ctor (zakazany)
    Player(const Player& rhs) = delete;
    // move ctor (zakazany)
    Player(Player&& rhs) = delete;
    // Destructor
    ~Player()/* override*/;
    // copy prirazeni
    void operator=(const Player& rhs) = delete;
    // move prirazeni
    void operator=(Player&& rhs) = delete;

    void HandleEvents() override;

    void Render();
    bool IsDestroyble();
    void Update(std::vector<Wall*>* others, float delta);
    enum class eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    SDL_Rect GetDstBox() const;
    bool IsGameOver();
    void DecreaseLives(int i);
private:
    enum eControls : short {
        UP = 'w',
        LEFT = 'a',
        DOWN = 's',
        RIGHT = 'd'
    };
    int lives = 1;
};

