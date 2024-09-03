#pragma once
#include "common.h"

class File {
public:
	File(const std::string& fileName);
	~File();

	void Clear();

	enum class MODE {
		NONE = 0,
		READ,
		WRITE
	};

	void Open(MODE mode);
	void Close();

	template<typename T>
	void Save(const T* value, int size) {
		if (currentMode != MODE::WRITE) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		file.write((char*)value, size);
	}

	template<typename T>
	void Save(const T& value, int size = sizeof(T)) {
		if (currentMode != MODE::WRITE) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}
		file.write((char*)&value, size);
	}
	template<> void Save(const std::string& value, int size) {
		if (currentMode != MODE::WRITE) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		file.write((char*)value.data(), size);
	}
	template<typename T>
	void Save(const std::vector<T>& v, int count, int elementSize = sizeof(T)) {
		if (currentMode != MODE::WRITE) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}
		for (int i = 0; i < count; i++) {
			file.write((char*)&v[i], elementSize);
		}
	}


	template<typename T>
	void Load(T* value, int size) {
		if (currentMode != MODE::READ) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}
		file.seekg(position);
		file.read((char*)value, size);
		position += size;
	}

	template<typename T>
	void Load(T& value, int size = sizeof(T)) {
		if (currentMode != MODE::READ) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}
		file.seekg(position);
		file.read((char*)&value, size);
		position += size;
	}
	template<> void Load(std::string& s, int size) {
		if (currentMode != MODE::READ) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		s.resize(size);
		file.seekg(position);
		file.read((char*)s.data(), size);
		position += size;
	}
	template<typename T>
	void Load(std::vector<T>& v, int count, int elementSize = sizeof(T)) {
		if (currentMode != MODE::READ) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		v.resize(count);
		for (int i = 0; i < count; i++) {
			file.seekg(position);
			file.read((char*)&v[i], elementSize);
			position += elementSize;
		}
	}

private:
	MODE currentMode;
	int position = 0;
	std::string fileName;
	std::fstream file;
};