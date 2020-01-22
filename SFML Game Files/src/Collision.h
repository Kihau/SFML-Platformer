#pragma once

#include "all_headers.h"

class Collision
{
private:
	RectangleShape hitbox;
	float offset_down{};
	float offset_right{};

public:
	Collision();
	Collision(float height, float width, float offset_down = 0.0f, float offset_right = 0.0f, Color color = Color::Green);

	void UpdateHitbox(Sprite& sprite);
	void CreateHitbox(float height, float width, float offset_down = 0.0f, float offset_right = 0.0f, Color color = Color::Green);

	bool CheckCollision(Collision& coll);
	bool CheckCollision(Sprite& sprite);

	void FixPosition(Sprite& sprite, Collision& coll);
	void FixPosition(Sprite& sprite1, Sprite& sprite2);

	void ShowHitbox(RenderWindow* window);
	static void ShowHitbox(RenderWindow* window, Sprite& sprite, Color color = Color::Red);
	void UpdateConsole();
};


