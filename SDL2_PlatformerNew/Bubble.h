#pragma once
#include "MovableObject.h"
#include "File.h"
class Bubble : public MovableObject {
public:
	Bubble() {}
	Bubble(Vec4f box, const std::string& path, int characterWidth);
	Bubble(const Bubble& rhs) = delete;
	Bubble(Bubble&& rhs);
	~Bubble() override;
	void operator=(const Bubble& rhs) = delete;
	void operator=(Bubble&& rhs) = delete;

	void Update();
	void Save(File& file);
	void Load(File& file);
};