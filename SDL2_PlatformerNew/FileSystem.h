#pragma once
#include "common.h"

namespace File {
	template<typename T>
	void Save(const T* value, int size) {
		std::ofstream file("BinExample.bin", std::ios::out | std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		file.write((char*)value, size);
		file.close();
	}

	template<typename T>
	void Save(const T& value, int size = sizeof(T)) {
		std::ofstream file("BinExample.bin", std::ios::out | std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}
		file.write((char*)&value, size);
		file.close();
	}
	template<> void Save(const std::string& value, int size) {
		std::ofstream file("BinExample.bin", std::ios::out | std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		file.write((char*)value.data(), size);
		file.close();
	}

	template<typename T>
	void Load(T* value, int size) {
		std::ifstream file("BinExample.bin", std::ios::in | std::ios::binary);
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		file.read((char*)value, size);
		file.close();
	}

	template<typename T>
	void Load(T& value, int size = sizeof(T)) {
		std::ifstream file("BinExample.bin", std::ios::in | std::ios::binary);
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		file.read((char*)&value, size);

		file.close();
	}
	template<> void Load(std::string& s, int size) {
		std::ifstream file("BinExample.bin", std::ios::in | std::ios::binary);
		if (!file.is_open()) {
			std::cout << "Nelze otevrit\n";
			return;
		}

		s.resize(size);
		file.read((char*)s.data(), size);

		file.close();
	}
}