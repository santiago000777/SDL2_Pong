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

struct Vec4 {
public:
	int x { 0 }, y { 0 }, w { 0 }, h { 0 };

public:
	Vec4() {}
	Vec4(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) {
	}

	void operator+=(const Vec4& vec) {
		this->x += vec.x;
		this->y += vec.y;
	}
	Vec4& operator+(Vec4 vec) {
		vec += *this;
		return vec;
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