#pragma once

#include "all_headers.h"

class Collision
{
private:
	struct ver{
		float left;
		float right;
		float bottom;
		float top;
		float width;
		float height;
	}h1, h2, s1, s2;

	Rect <float> hitbox1;
	Rect <float> hitbox2;
	Sprite sprite1;
	Sprite sprite2;

private:
	void UpdateH1(Rect <float> hitbox1);
	void UpdateH2(Rect <float> hitbox2);
	void UpdateS1(Sprite& sprite1);
	void UpdateS2(Sprite& sprite2);

public:
	// HITBOX1 - SPRITE1
	bool CheckCollision(Rect <float> hitbox1, Sprite& sprite1);
	void FixPosition(Rect <float> hitbox1, Sprite& sprite1, Sprite& sprite2);
};


