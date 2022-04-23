#include <SFML/Graphics.hpp>
#include <iostream>
#include "Astronave.h"
#include "Proiettile.h"
using namespace sf;
using namespace std;

Astronave::Astronave() {

	Astronave_position.x = VideoMode::getDesktopMode().width - 100.0; 
	Astronave_position.y = VideoMode::getDesktopMode().height / 2;
	Astronave_speed = 300;
	Astronave_sprite.setTexture(*textureManager.getAstronaveTexture());
	Astronave_sprite.setOrigin(64.f, 64.f);
	Astronave_sprite.setScale(0.5, 0.5);
	coolDown = 0.35;
	shootTime = 0;
	astronave_vita = 3;
	heart_Astronave_sprite.setTexture(*textureManager.getHeartTexture());
	heart_Astronave_sprite.setScale(0.2, 0.2);
	float posx = 0;
	tmp = 0;
	
					// CREO VECTOR DI CUORI (VITA DELL'ASTRONAVE)
	
	for (int i = 0; i < 3; i++) {

		hearts.push_back(heart_Astronave_sprite);
		hearts[i] = heart_Astronave_sprite;
		hearts[i].setPosition(VideoMode::getDesktopMode().width - 1.1 * posHearts(), 10.f);

	}

	                                // BARRA DEL FUEL
	
	fuelShape.setPosition(10.f, 50.f);
	fuelShape.setSize(Vector2f(200, 50));
	fuelShape.setFillColor(Color::Black);
	fuelShape.setOutlineThickness(2);

	fuelSize.x = 200;
	fuelSize.y = 50;

	fuelShape1.setPosition(10.f, 50.f);
	fuelShape1.setSize(fuelSize);
	fuelShape1.setFillColor(Color::Magenta);
	fuelShape1.setOutlineThickness(2);

	                               // PUNTEGGIO
	
	score = 0;
	ss << score;
	punteggio.setString(ss.str());
	myfont.loadFromFile("arial.ttf");
	punteggio.setFont(myfont);

	punteggio.setPosition(Vector2f(VideoMode::getDesktopMode().width / 2, 50));
	punteggio.setCharacterSize(40);

}

Sprite Astronave::getSprite() {

	return Astronave_sprite;
}

Vector2f Astronave::getPosition() {

	return Astronave_position;
}

float Astronave::speed() {

	return Astronave_speed;
}

void Astronave::moveUp() {

	Astronave_sprite.setRotation(0.f);
	upBottomPressed = true;
	dir = DIRECTION_UP;
}

void Astronave::moveDown() {

	Astronave_sprite.setRotation(180.f);
	downBottomPressed = true;
	dir = DIRECTION_DOWN;
}

void Astronave::moveLeft() {

	Astronave_sprite.setRotation(270.f);
	leftBottomPressed = true;
	dir = DIRECTION_LEFT;
}

void Astronave::moveRight() {

	Astronave_sprite.setRotation(90.f);
	rightBottomPressed = true;
	dir = DIRECTION_RIGHT;
}

void Astronave::stopUp() {

	upBottomPressed = false;
}

void Astronave::stopDown() {

	downBottomPressed = false;
}

void Astronave::stopLeft() {

	leftBottomPressed = false;
}

void Astronave::stopRight() {

	rightBottomPressed = false;
}

void Astronave::fire() {

	backspaceBottomPressed = true;
}

void Astronave::notFire() {

	backspaceBottomPressed = false;
}

void Astronave::fuelLine() {

	cBottomPressed = true;
}

void Astronave::notFuelLine() {

	cBottomPressed = false;
}

int Astronave::getVita() {

	return astronave_vita;
}

int Astronave::AumentaVita() {

	return astronave_vita = 3;
}

Sprite Astronave::heartgetSprite() {

	return heart_Astronave_sprite;
}

vector<Sprite>& Astronave::getHearts() {

	return hearts;
}

float Astronave::posHearts() {

	posx = posx + 100.f;

	return posx;
}

void Astronave::DiminuisciVita() {

	astronave_vita = astronave_vita - 1;
}

void Astronave::update(float elapsedTime) {

	// MUOVE L'ASTRONAVE IN BASE ALL'INPUT                                          

	if (upBottomPressed) {

		Astronave_position.y -= Astronave_speed * elapsedTime;
	}

	if (downBottomPressed) {

		Astronave_position.y += Astronave_speed * elapsedTime;
	}

	if (rightBottomPressed) {

		Astronave_position.x += Astronave_speed * elapsedTime;
	}
	if (leftBottomPressed) {

		Astronave_position.x -= Astronave_speed * elapsedTime;
	}

	Astronave_sprite.setPosition(Astronave_position); // MUOVE L'ASTRONAVE SULLA SUA NUOVA POSIZIONE

	shootTime += elapsedTime;

	if (backspaceBottomPressed && shootTime >= coolDown) { //SPARA I PROIETTILI QUANDO VIENE PREMUTA LA SPACE BAR

		bullets.push_back(Proiettile(getPosition(), dir));
		shootTime = 0;
	}

	for (size_t i = 0; i < bullets.size(); i++) {

		bullets[i].update(elapsedTime);
	}

	if (cBottomPressed) { //SETTA IL RAGGIO TRAENTE QUANDO VIENE PREMUTO IL TASTO 'C'

		rTraente.setPosition(getPosition());
		rTraente.setFillColor(Color::Red);
		rTraente.setOutlineThickness(2);
		rTraente.setRotation(90);
	}

	punteggio.setString(ss.str());
}

RectangleShape Astronave::getFuelShape() {

	return fuelShape;
}

RectangleShape Astronave::getFuelShape1() {

	return fuelShape1;
}

vector<Proiettile>& Astronave::getBullets() {

	return bullets;
}

void Astronave::setPos(Vector2f p) {

	Astronave_position.x = p.x;
	Astronave_position.y = p.y;
}

RectangleShape& Astronave::getrTraenteShape() {

	return rTraente;
}

float Astronave::getFuelsizeX() {

	return fuelSize.x;
}

float Astronave::getFuelsizeY() {

	return fuelSize.y;
}

void Astronave::resetHP() {

	//RESETTA LE IMPOSTAZIONI DELLA VITA QUANDO SI RIAVVIA IL GIOCO

	astronave_vita = 3;
	posx = 0;
	hearts.clear();
	for (int i = 0; i < 3; i++) {

		hearts.push_back(heartgetSprite());
		hearts[i] = heartgetSprite();
		hearts[i].setPosition(VideoMode::getDesktopMode().width - 1.1 * posHearts(), 10.f);
	}
}

void Astronave::update2(float elapsedTime) {

	//FA DIMINUIRE LA BARRA DEL CARBURANTE

	if (fuelSize.x >= 0) {

		fuelSize.x -= elapsedTime * 5;

		fuelShape1.setSize(fuelSize);
	}
}

void Astronave::resetFuel() {

	fuelSize.x = 200;
	fuelShape1.setSize(fuelSize);
}

void Astronave::addFuel1() {

	float add1 = 30;

	//AGGIUNGE CARBURANTE ALLA BARRA QUANDO SI RACCOGLIE IL FUEL DAL TERRENO

	if (fuelSize.x + add1 > 200) {

		fuelSize.x = 200;
	}

	else {

		fuelSize.x += add1;
	}
	fuelShape1.setSize(fuelSize);
}

void Astronave::addFuel2() {

	float add2 = 50;

	if (fuelSize.x + add2 > 200) {

		fuelSize.x = 200;
	}

	else {

		fuelSize.x += add2;
	}
	fuelShape1.setSize(fuelSize);
}

Text Astronave::getPunteggio() {

	return punteggio;
}

//AUMENTANO IL PUNTEGGIO IN BASE AGLI EVENTI CHE AVVENGONO

void Astronave::AumentaPunteggio1() {

	score = score + 50;
	ss.str("");
	ss << score;
}

void Astronave::AumentaPunteggio2() {

	score = score + 40;
	ss.str("");
	ss << score;
}

void Astronave::AumentaPunteggio3() {

	score = score + 100;
	ss.str("");
	ss << score;
}

void Astronave::AumentaPunteggio4() {

	score = score + 200;
	ss.str("");
	ss << score;
}

//RESETTA IL PUNTEGGIO QUANDO SI RIAVVIA IL GIOCO

void Astronave::resetPunteggio() {

	score = 0;
	ss.str("");
	ss << score;
}









