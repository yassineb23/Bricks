#pragma once
#include "raylib.h";


struct Koora {
	float x = GetScreenWidth() / 2;
	float y = GetScreenHeight() / 2;
	int radius = 12;
	int speedX = 250;
	int speedY = 250;
	
	void draw() {
		DrawCircle((int)x, (int)y, radius, RED);
	}
};

struct Player {
	float x = GetScreenWidth() / 2  - 50;
	float y = GetScreenHeight() - 60;
	float size = 100;
	float height = 10;
	int speed = 450;

	Rectangle player() {
		return Rectangle{ x, y, size, height};
	}

	void draw() {
		DrawRectangleRec(player(), WHITE);
	}
};

struct Brick{
	float x = 0.0f;
	float y = 0.0f;
	float size = 60;
	float height = 30;
	bool alive = true;

	Rectangle brick() {
		return Rectangle{ x, y, size, height };
	}

	void draw() {
		DrawRectangleRec(brick(), GREEN);
	}
};