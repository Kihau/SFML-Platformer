#include "Collision.h"

void Collision::UpdateH1(Rect <float> hitbox1)
{
	h1.left = hitbox1.left;
	h1.right = hitbox1.left + hitbox1.width;
	h1.bottom = hitbox1.top - hitbox1.height;
	h1.top = hitbox1.top;
	h1.width = hitbox1.width;
	h1.height = hitbox1.height;
}

void Collision::UpdateH2(Rect <float> hitbox2)
{
	h2.left = hitbox2.left;
	h2.right = hitbox2.left + hitbox2.width;
	h2.bottom = hitbox2.top - hitbox2.height;
	h2.top = hitbox2.top;
	h2.width = hitbox2.width;
	h2.height = hitbox2.height;
}

void Collision::UpdateS1(Sprite& sprite1)
{
	s1.left = sprite1.getGlobalBounds().left;
	s1.right = sprite1.getGlobalBounds().left + sprite1.getGlobalBounds().width;
	s1.bottom = sprite1.getGlobalBounds().top - sprite1.getGlobalBounds().height;
	s1.top = sprite1.getGlobalBounds().top;
	s1.width = sprite1.getGlobalBounds().width;
	s1.height = sprite1.getGlobalBounds().height;
}

void Collision::UpdateS2(Sprite& sprite2)
{
	s2.left = sprite2.getGlobalBounds().left;
	s2.right = sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width;
	s2.bottom = sprite2.getGlobalBounds().top - sprite2.getGlobalBounds().height;
	s2.top = sprite2.getGlobalBounds().top;
	s2.width = sprite2.getGlobalBounds().width;
	s2.height = sprite2.getGlobalBounds().height;
}

bool Collision::CheckCollision(Rect <float> hitbox1, Sprite& sprite1)
{
	if (hitbox1.intersects(sprite1.getGlobalBounds())) return true;
	else return false;
}

void Collision::FixPosition(Rect <float> hitbox1, Sprite& sprite1, Sprite& sprite2)
{
	UpdateH1(hitbox1);
	UpdateS1(sprite1);
	UpdateS2(sprite2);

	// Bottom Collision
	if (h1.bottom > s2.top)
		sprite1.setPosition(s1.left, s2.top);

	// Left Collision
	else if (h1.right > s2.left)
		sprite1.setPosition(h1.right, s1.top);
}
