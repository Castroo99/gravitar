#include "Bunker.h"
#include "TextureManager.h"
#include <vector>
using namespace sf;
using namespace std;

Bunker::Bunker(Vector2f pos, float rot) {

	bunker_position = pos;
	bunker_rotation = rot;
	bunker_vita = 3;
	                    // 1° TIPO DI BUNKER
	bunker_sprite.setTexture(*textureManager.getBunkerTexture());
	bunker_sprite.setPosition(pos);
	bunker_sprite.setScale(0.4, 0.4);
	bunker_sprite.setOrigin(135, 135);
	bunker_sprite.setRotation(rot);
	                    // 2° TIPO DI BUNKER
	bunker_sprite2.setTexture(*textureManager.getBunkerTexture2());
	bunker_sprite2.setPosition(pos);
	bunker_sprite2.setScale(0.35, 0.35);
	bunker_sprite2.setOrigin(150, 150);
	bunker_sprite2.setRotation(rot);

	shootTime = 0;
	coolDown = 2;
	shootTime2 = 0;
	coolDown2 = 2.5;
	bunker_texture.setSmooth(true);

	// DIREZIONI DI SPARO DEI BUNKER

	directions.push_back(DIRECTION_UP);
	directions.push_back(DIRECTION_RAND1);
	directions.push_back(DIRECTION_RAND2);
}

Sprite Bunker::getSprite() {

	return bunker_sprite;
}

Sprite Bunker::getSprite2() {

	return bunker_sprite2;
}

int Bunker::getVita() {

	return bunker_vita;
}

void Bunker::DiminuisciVita() {

	bunker_vita = bunker_vita - 1;
}

Vector2f Bunker::getposition() {

	return bunker_position;
}

float Bunker::getRotation() {

	return bunker_rotation;
}

//SCEGLIE UN METODO CASUALE DI SPARO PER UN BUNKER

Direction Bunker::randDir() {

	int x = rand() % 3;

	return directions[x];
}

//AGGIORNANO DURANTE IL GIOCO LE IMPOSTAZIONI DEI BUNKER

void Bunker::update(float elapsedTime, vector<Proiettile>& bbullets) {

	shootTime += elapsedTime;

	if (shootTime >= coolDown) {

		bbullets.push_back(Proiettile(getposition(), randDir()));
		shootTime = 0;
	}
}

void Bunker::update2(float elapsedTime, vector<Proiettile>& bbullets2) {

	shootTime2 += elapsedTime;

	if (shootTime2 >= coolDown2) {

		bbullets2.push_back(Proiettile(getposition(), DIRECTION_UP));
		shootTime2 = 0;
	}
}





