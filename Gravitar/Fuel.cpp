#include "Fuel.h"
#include "TextureManager.h"
using namespace sf;

Fuel::Fuel(Vector2f pos) {

	Fuel_position = pos;
                                 // CREO 1° TIPO DI FUEL
	Fuel_sprite.setTexture(*textureManager.getFuelTexture());
	Fuel_sprite.setPosition(pos);
	Fuel_sprite.setScale(0.2, 0.2);
	Fuel_sprite.setOrigin(148, 85.5);
	                             // CREO 2° TIPO DI FUEL
	Fuel_sprite2.setTexture(*textureManager.getFuelTexture2());
	Fuel_sprite2.setPosition(pos);
	Fuel_sprite2.setScale(0.15, 0.15);
	Fuel_sprite.setOrigin(112.5, 112.5);
}

Vector2f Fuel::getPosition(){

	return Fuel_position;
}

Sprite Fuel::getSprite(){

	return Fuel_sprite;
}

Texture Fuel::getTexture(){

	return Fuel_texture;
}

Sprite Fuel::getSprite2(){

	return Fuel_sprite2;
}

Texture Fuel::getTexture2(){

	return Fuel_texture2;
}


