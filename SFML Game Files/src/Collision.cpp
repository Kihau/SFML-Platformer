#include "Collision.h"

bool CheckCollision(Rect <float> hitbox1, Rect <float> hitbox2)
{
	if (hitbox1.intersects(hitbox2)) return true;
	else return false;
}

void FixPositionBottom(Sprite& s1, Sprite& s2)
{
	if (s1.getGlobalBounds().top + s1.getGlobalBounds().height > 
			s2.getGlobalBounds().top + s2.getGlobalBounds().height)
		s1.setPosition(s1.getPosition().x, s1.getGlobalBounds().top);
}
