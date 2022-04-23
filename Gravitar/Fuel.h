#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Fuel {

protected:

	int valore;
	int tipo;
	Vector2f Fuel_position;
	Sprite Fuel_sprite;
	Texture Fuel_texture;
	Sprite Fuel_sprite2;
	Texture Fuel_texture2;

public:

	Fuel(Vector2f pos);
	Vector2f getPosition();
	Sprite getSprite();
	Texture getTexture();
	Sprite getSprite2();
	Texture getTexture2();
};