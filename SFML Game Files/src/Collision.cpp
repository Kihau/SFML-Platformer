#include "Collision.h"

void Collision::UpdateHitbox1(Sprite& sprite1)
{
	hitbox1.top = sprite1.getGlobalBounds().top + sprite1.getGlobalBounds().height - hitbox1.height;
	hitbox1.left = sprite1.getGlobalBounds().left + (sprite1.getGlobalBounds().width - hitbox1.width) / 2;
}

void Collision::CreateHitbox1(float height, float width)
{
	hitbox1.width = width;
	hitbox1.height = height;
	//UpdateHitbox1(sprite1);
}

void Collision::UpdateConsole()
{
	cout << "\nHITBOX left: " << hitbox1.left << endl;
	cout << "HITBOX top: " << hitbox1.top << endl;
	cout << "HITBOX width: " << hitbox1.width << endl;
	cout << "HITBOX hight: " << hitbox1.height << endl;
}

bool Collision::CheckCollision(Sprite& sprite1, Sprite& sprite2)
{
	UpdateHitbox1(sprite1);
	return hitbox1.intersects(sprite2.getGlobalBounds());
}

void Collision::FixPositionBottom(Sprite& sprite1, Sprite& sprite2)
{
	//UpdateHitbox1(sprite1);

	if (sprite1.getGlobalBounds().top - sprite1.getGlobalBounds().height < sprite2.getGlobalBounds().top)
	{
		sprite1.setPosition
		(sprite1.getPosition().x,
			sprite2.getGlobalBounds().top - sprite1.getGlobalBounds().height);
	}
}

void Collision::FixPositionRight(Sprite& sprite1, Sprite& sprite2)
{
	if (sprite1.getGlobalBounds().top - sprite1.getGlobalBounds().height < sprite2.getGlobalBounds().top)
	{
		if (hitbox1.left + hitbox1.width > sprite2.getGlobalBounds().left)
		{
			sprite1.setPosition
			(sprite2.getGlobalBounds().left - hitbox1.width,
				sprite1.getPosition().y);
		}
	}
}
