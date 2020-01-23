#include "Collision.h"

Collision::Collision()
{
	/* DOES NOTHING */
}

Collision::Collision(float height, float width, float offset_down, float offset_right, Color color)
{
	CreateHitbox(height, width, offset_down, offset_right, color);
}

void Collision::UpdateHitbox(Sprite& sprite)
{
	hitbox.setPosition(Vector2f
	(sprite.getGlobalBounds().left + offset_right, 
		sprite.getGlobalBounds().top + offset_down));
}

void Collision::CreateHitbox(float height, float width, float offset_down, float offset_right, Color color)
{
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineThickness(-1.0f);
	hitbox.setOutlineColor(color);

	this->offset_down = offset_down;
	this->offset_right = offset_right;
	hitbox.setSize(Vector2f(width, height));
}

void Collision::UpdateConsole()
{
	cout << "\nHITBOX left: " << hitbox.getGlobalBounds().left << endl;
	cout << "HITBOX top: " << hitbox.getGlobalBounds().top << endl;
	cout << "HITBOX width: " << hitbox.getGlobalBounds().width << endl;
	cout << "HITBOX hight: " << hitbox.getGlobalBounds().height << endl;
}

void Collision::UpdateConsoleCollision(Sprite& sprite)
{
	if (CheckCollision(sprite)) cout << "COLLISION\n";
	else cout << "NO COLLISION\n";
}

bool Collision::CheckCollision(Collision& coll)
{
	return this->hitbox.getGlobalBounds().intersects(coll.hitbox.getGlobalBounds());
}

bool Collision::CheckCollision(Sprite& sprite)
{
	return hitbox.getGlobalBounds().intersects(sprite.getGlobalBounds());
}


void Collision::ShowHitbox(RenderWindow* window)
{
	window->draw(this->hitbox);
}

void Collision::ShowHitbox(RenderWindow* window, Sprite& sprite, Color color)
{
	RectangleShape hitbox;
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineThickness(-1.0f);
	hitbox.setOutlineColor(color);
	hitbox.setSize(Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));
	hitbox.setPosition(Vector2f(sprite.getGlobalBounds().left,sprite.getGlobalBounds().top));
	window->draw(hitbox);
}

bool Collision::FixPositionBottom(Sprite& sprite1, Sprite& sprite2)
{		
	if (hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height > sprite2.getGlobalBounds().top
		/*&& hitbox.getGlobalBounds().left > sprite2.getGlobalBounds().left
		&& hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width < sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width*/
		&& hitbox.getGlobalBounds().top < sprite2.getGlobalBounds().top)
	{
		sprite1.setPosition(sprite1.getPosition().x, sprite2.getGlobalBounds().top - sprite1.getGlobalBounds().height + 5);
		return true;
	}
	else return false;
}

bool Collision::FixPositionTop(Sprite& sprite1, Sprite& sprite2)
{
	if (hitbox.getGlobalBounds().top > sprite2.getGlobalBounds().top - sprite2.getGlobalBounds().height
		/*&& hitbox.getGlobalBounds().left > sprite2.getGlobalBounds().left
		&& hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width < sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width*/
		&& hitbox.getGlobalBounds().top > sprite2.getGlobalBounds().top)
	{
		sprite1.setPosition(sprite1.getPosition().x, sprite2.getGlobalBounds().top + sprite2.getGlobalBounds().height - offset_down);
		return true;
	}
	else return false;
}

bool Collision::FixPositionLeftRight(Sprite& sprite1, Sprite& sprite2)
{
	if (hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width > sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width
		&& hitbox.getGlobalBounds().left < sprite1.getGlobalBounds().left + sprite2.getGlobalBounds().width
		&& hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height > sprite2.getGlobalBounds().top + 5
		&& hitbox.getGlobalBounds().top < sprite2.getGlobalBounds().top + sprite2.getGlobalBounds().height - 1)
	{
		sprite1.setPosition(sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width - offset_right + sprite1.getGlobalBounds().width, sprite1.getPosition().y);
		return true;
	}
	else if (hitbox.getGlobalBounds().left < sprite2.getGlobalBounds().left
		&& hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width > sprite1.getGlobalBounds().left
		&& hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height > sprite2.getGlobalBounds().top + 5
		&& hitbox.getGlobalBounds().top < sprite2.getGlobalBounds().top + sprite2.getGlobalBounds().height - 1)
	{
		sprite1.setPosition(sprite2.getGlobalBounds().left - sprite1.getGlobalBounds().width + offset_right, sprite1.getPosition().y);
		return true;
	}
	else return false;
}