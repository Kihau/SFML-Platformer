#pragma once

#include "all_headers.h"

class Collision
{
private:
	// gotta store hitboxes in vector soon
	//vector <ver> sprites;
	//vector <ver> hitboxes;

	Rect <float> hitbox1;

private:
	void UpdateHitbox1(Sprite& sprite1);

public:
	bool CheckCollision(Sprite& sprite1, Sprite& sprite2);
	void FixPositionBottom(Sprite& sprite1, Sprite& sprite2);
	void FixPositionRight(Sprite& sprite1, Sprite& sprite2);

	void CreateHitbox1(float height, float width);
	void UpdateConsole();
};


