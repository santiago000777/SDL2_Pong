#pragma once
#include "Object.h"
#include "File.h"

class Brick : public Object {
public:
    Brick(){}
    Brick(Vec4f box, const std::string& path, int characterWidth);
    // copy ctor (zakazany)
    Brick(const Brick& rhs) = delete;
    // move ctor (zakazany)
    Brick(Brick&& rhs);
    // Destructor
    ~Brick() override;
    // copy prirazeni
    void operator=(const Brick& rhs) = delete;
    // move prirazeni
    void operator=(Brick&& rhs) = delete;

    int GetPoints() const;

    void Save(File& file);
    void Load(File& file);
private:
    int points = 1;
};