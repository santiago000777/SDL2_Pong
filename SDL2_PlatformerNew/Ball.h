#pragma once
#include "MovableObject.h"
#include "File.h"

class Ball : public MovableObject {
public:
    Ball(){}
    Ball(Vec4f box, const std::string& path, int characterWidth);
    Ball(Vec4f box, Vec2 vector, const std::string& path, int characterWidth);
    // copy ctor (zakazany)
    Ball(const Ball& rhs) = delete;
    // move ctor (zakazany)
    Ball(Ball&& rhs)/* = delete*/;
    // Destructor
    ~Ball() override;
    // copy prirazeni
    void operator=(const Ball& rhs) = delete;
    // move prirazeni
    void operator=(Ball&& rhs) = delete;

    void SetOwnerId(int id);
    int GetOwnerId() const;

    int GetPoints() const;
    void SetPoints(int points);
    void AddPoints(int points);

    void Update();
    void ResetPoints();
    void ResetPosition();

    void Save(File& file);
    void Load(File& file);
protected:
    float velocity = 0.7;
    int points = 0;
    int playerOwnerId = -1;
};