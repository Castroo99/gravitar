#pragma once
#include "Proiettile.h"
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Bunker {

protected:

	int bunker_vita;
	float bunker_rotation;
	Sprite bunker_sprite;
	Texture bunker_texture;
	Sprite bunker_sprite2;
	Texture bunker_texture2;
	Vector2f bunker_position;
	float coolDown;
	float shootTime;
	float coolDown2;
	float shootTime2;
	vector<Direction> directions;

public:

	Bunker(Vector2f pos, float rot);
	Sprite getSprite();
	Sprite getSprite2();
	void DiminuisciVita();
	int getVita();
	Vector2f getposition();
	float getRotation();
	Direction randDir();
	void update(float elapsedTime, vector<Proiettile>& bbullets);
	void update2(float elapsedTime, vector<Proiettile>& bbullets2);
};
