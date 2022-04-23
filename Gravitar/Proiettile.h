#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
using namespace sf;
using namespace std;

//DIREZIONI POSSIBILI DEI PROIETTILI DELL'ASTRONAVE

enum Direction{

	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_DOWN,
	DIRECTION_RAND1,
	DIRECTION_RAND2
};

class Proiettile{
	
private:

	Sprite bullet_sprite;
	Texture bullet_texture;
	Vector2f bullet_position;
	float bullet_max_speed;
	Direction dir;
	
public:
	
	Proiettile(Vector2f pos, Direction _dir);
	Sprite getSprite();
	Vector2f getposition();
	void update(float elapsedtime);
	
};
