#pragma once

#include <cmath>
#include <conio.h>  
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <dos.h>
#include <fcntl.h>
#include <fstream>
#include<iostream>
#include <locale.h>
#include <map>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>       
#include <thread>
#include <windows.h>
#include <winuser.h>

#define DEBUG()	if(GetAsyncKeyState(VK_ESCAPE)) {__debugbreak();}
#define BREAK	__debugbreak
#define PI		3.14159265359

	// SDL2
#include "SDL.h"

	// SDL_ttf
#include "SDL_ttf.h"

static bool WasPressedKey(short key) {
	short i = GetAsyncKeyState(toupper(key));
	if ((i & 0x0001) == 0) {
		return false;
	}
	return true;
}

static bool PressedKey(short key) {
	short i = GetAsyncKeyState(toupper(key));
	if ((i & 0x8000) == 0) {
		return false;
	}
	return true;
}

struct Vec2 {
public:
	float x { 0 }, y { 0 };

public:
	Vec2() {}
	Vec2(float x, float y)
		: x(x), y(y) {
	}
	void operator+=(const Vec2& vec) {
		this->x += vec.x;
		this->y += vec.y;
	}
	Vec2& operator+(Vec2 vec) {
		vec += *this;
		return vec;
	}
	void operator*=(float f) {
		this->x *= f;
		this->y *= f;
	}
};

struct Vec4f {
public:
	float x { 0.0f }, y { 0.0f }, w { 0.0f }, h { 0.0f };

public:
	Vec4f() {}
	Vec4f(float x, float y, float w, float h)
		: x(x), y(y), w(w), h(h) {
	}

	Vec4f(const Vec4f& vec)
		: x(vec.x), y(vec.y), w(vec.w), h(vec.h) {
	}
	void operator=(const Vec4f& vec) {
		x = vec.x;
		y = vec.y;
		w = vec.w;
		h = vec.h;
	}

	SDL_Rect Get() const {
		return { (int)roundf(this->x), (int)roundf(this->y), (int)roundf(this->w), (int)roundf(this->h) };
	}
};

struct Color {
public:
	unsigned char r, g, b, a;

public:
	Color() = default;
	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alfa)
		: r(red), g(green), b(blue), a(alfa) {
	}
};