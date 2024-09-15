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
	void Save(const std::string& value) {
		if (currentMode != MODE::WRITE) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}
		Save(value.size());
		file.write((char*)value.data(), value.size());
	}
	template<typename T>
	void Save(const std::vector<T>& v, int elementSize = sizeof(T)) {
		if (currentMode != MODE::WRITE) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		Save(v.size());
		for (int i = 0; i < v.size(); i++) {
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
	void Load(std::string& s) {
		if (currentMode != MODE::READ) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		size_t size;
		Load(size);
		s.resize(size);

		file.seekg(position);
		file.read((char*)s.data(), size);
		position += size;
	}
	template<typename T>
	void Load(std::vector<T>& v, int elementSize = sizeof(T)) {
		if (currentMode != MODE::READ) {
			std::cout << "Opacny mod\n";
			return;
		}
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		size_t size;
		Load(size);
		v.resize(size);

		for (int i = 0; i < size; i++) {
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

