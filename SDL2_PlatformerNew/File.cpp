#include "File.h"

File::File(const std::string& fileName) {
	this->fileName = fileName;
	currentMode = MODE::NONE;
}

File::~File() {
	if (file.is_open()) {
		file.close();
	}
}

void File::Open(MODE mode) {
	Close();
	switch (mode) {
		case MODE::READ: {
			file.open(fileName, std::ios::in | std::ios::binary);
			currentMode = MODE::READ;
			break;
		}
		case MODE::WRITE: {
			file.open(fileName, std::ios::app | std::ios::binary | std::ios::ate);
			currentMode = MODE::WRITE;
			break;
		}
		default: {
			currentMode = MODE::NONE;
			break;
		}
	}
}

void File::Close() {
	if (file.is_open()) {
		file.close();
	}
}

void File::Clear() {
	if (currentMode != MODE::WRITE) {
		Open(MODE::WRITE);
	}
	if (!file.is_open()) {
		std::cout << "Nelze otevrit - mazani\n";
		return;
	}
	file.close();
}