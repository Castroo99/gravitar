#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Proiettile.h"
#include "TextureManager.h"
using namespace sf;
using namespace std;

Proiettile::Proiettile(Vector2f pos, Direction _dir) {
	
	bullet_position = pos;
	dir = _dir;
	bullet_sprite.setTexture(*textureManager.getBulletTexture());
	bullet_texture.setSmooth(true);
	bullet_sprite.setScale(0.01, 0.01);
	bullet_max_speed = 400;
}

Sprite Proiettile::getSprite(){

	return bullet_sprite;
}

Vector2f Proiettile::getposition(){

	return bullet_position;
}

//SPOSTA IL PROIETTILE NEL TEMPO IN BASE ALLA DIREZIONE

void Proiettile::update(float elapsedtime) {
	
	if (dir == DIRECTION_UP) {

		bullet_position.y -= bullet_max_speed * elapsedtime;
	}

	if (dir == DIRECTION_DOWN) {

		bullet_position.y += bullet_max_speed * elapsedtime;
	}

	if (dir == DIRECTION_RIGHT) {

		bullet_position.x += bullet_max_speed * elapsedtime;
	}
	if (dir == DIRECTION_LEFT) {

		bullet_position.x -= bullet_max_speed * elapsedtime;
	}
	if (dir == DIRECTION_RAND1) {
	
		bullet_position.x += bullet_max_speed * elapsedtime;
		bullet_position.y -= bullet_max_speed * elapsedtime;
	}
	if (dir == DIRECTION_RAND2) {

		bullet_position.x -= bullet_max_speed * elapsedtime;
		bullet_position.y -= bullet_max_speed * elapsedtime;
	}

    bullet_sprite.setPosition(bullet_position);
}


		




