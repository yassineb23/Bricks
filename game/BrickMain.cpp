#include "header.h";
#include <iostream>;
#include <vector>;


const int WIDTH = 1024;
const int HEIGHT = 768;
const char* TITLE = "Brickout";



void GameOver(void) {
	CloseWindow();
}

void collisiondetect(Koora* k,Player* p,std::vector<Brick>* bricks,int* score) {
	if (CheckCollisionCircleRec({ k->x,k->y }, k->radius, p->player())) {
		if (k->x <= p->x || k->x >= p->x + 100) {
			k->speedX *= -1;
		}else if (k->y >= p->y + 10) {
			k->speedY *= -1;
		}else if (k->speedY < 0) {
			k->speedY *= -1;
		}
	}else if (k->x > GetScreenWidth()) {
		k->speedX *= -1;
	}else if (k->x < 0) {
		k->speedX *= -1;
	}else if (k->y < 0) {
		k->y *= -1;
	}else if (k->y > GetScreenHeight()) {
		GameOver();
	}

	for (auto& b : *bricks) {
		if (CheckCollisionCircleRec({ k->x,k->y }, k->radius, b.brick()) && b.alive) {
			b.alive = false;
			*score+= 10;
			if (k->x <= b.x || k->x >= b.x + 100) {
				k->speedX *= -1;
			}
			else if (k->y >= b.y + 30 ) {
				k->speedY *= -1;
			}
			else if (k->y > b.y) {
				k->speedY *= -1;
			}
		}
	}
}


void updatekoora(Koora* k) {
	k->x += k->speedX * GetFrameTime();
	k->y -= k->speedY * GetFrameTime();
}


void updateplayer(Player* p) {
	if (IsKeyDown(KEY_LEFT) && p->x >= 0) {
		p->x -= p->speed * GetFrameTime();
	}
	else if (IsKeyDown(KEY_RIGHT) && p->x <= GetScreenWidth() - 100) {
		p->x += p->speed * GetFrameTime();
	}
}


std::vector<Brick> createBricks(void) {
	std::vector<Brick> bricks;
	for (int i = 30; i < GetScreenHeight() / 3 - 35; i += 25){
		for (int j = 25; j < GetScreenWidth() - 65; j += 60) {
			Brick b;
			b.x = j;
			b.y = i;
			bricks.push_back(b);
			j += 10;
		}
		i += 15;
	}
	return bricks;
}

void drawbricks(std::vector<Brick> bricks) {
	for (auto& b : bricks) {
		if(b.alive)DrawRectangle(b.x, b.y, b.size, b.height, GREEN);
	}
}

void main(void) {
	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(60);
	Koora k;
	Player p;
	std::vector<Brick> bricks = createBricks();
	int score = 0;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(TextFormat("Score: %06i", score), 0, 0, 20, RED);
		k.draw();
		p.draw();
		updateplayer(&p);
		updatekoora(&k);
		collisiondetect(&k, &p, &bricks,&score);
		drawbricks(bricks);

		EndDrawing();
	}

	CloseWindow();

}