#pragma once

#include "all_headers.h"

bool CheckCollision(Rect <float> hitbox1, Rect <float> hitbox2);
void FixPositionBottom(Sprite& s1, Sprite& s2);

class Collision
{
	Rect <float> hitbox;
public:
	friend bool CheckCollision(Rect <float> hitbox1, Rect <float> hitbox2);
	friend void FixPosition(Sprite& s1, Sprite& s2);
};
