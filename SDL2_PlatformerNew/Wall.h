#pragma once
#include "Object.h"

class Wall : public Object {
public:
    Wall(Vec4f box, const std::string& path, int characterWidth);
    // copy ctor (zakazany)
    Wall(const Wall& rhs) = delete;
    // move ctor (zakazany)
    Wall(Wall&& rhs) = delete;
    // Destructor
    ~Wall() override;
    // copy prirazeni
    void operator=(const Wall& rhs) = delete;
    // move prirazeni
    void operator=(Wall&& rhs) = delete;
};