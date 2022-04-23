#pragma once
#include <vector>
#include "Proiettile.h"
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace sf;
using namespace std;

class Astronave {

protected:

	float Astronave_speed;
	Vector2f Astronave_position;
	Sprite Astronave_sprite;
	Texture Astronave_texture;

	bool leftBottomPressed;
	bool rightBottomPressed;
	bool upBottomPressed;
	bool downBottomPressed;
	bool backspaceBottomPressed;
	bool cBottomPressed;

	float coolDown;
	float shootTime;
	Direction dir;
	vector<Proiettile> bullets;
	int astronave_vita;

	Sprite heart_Astronave_sprite;
	vector<Sprite> hearts;
	float posx;
	RectangleShape fuelShape;
	RectangleShape fuelShape1;
	float tmp;
	RectangleShape rTraente;
	Vector2f fuelSize;
	Text punteggio;
	Font myfont;
	int score;
	ostringstream ss;

public:

	Astronave();
	Sprite getSprite();
	Vector2f getPosition();
	float speed();
	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void stopUp();
	void stopDown();
	void stopLeft();
	void stopRight();
	
	void fire();
	void notFire();
	
	void fuelLine();
	void notFuelLine();
	
	vector<Proiettile>& getBullets();
	
	void DiminuisciVita();
	int getVita();
	int AumentaVita();
	Sprite heartgetSprite();
	vector<Sprite>& getHearts();
	float posHearts();
	
	void update(float elapsedTime2);
	
	RectangleShape getFuelShape();
	RectangleShape getFuelShape1();
	void setPos(Vector2f p);
	RectangleShape& getrTraenteShape();
	void addFuel1();
	void addFuel2();
	float getFuelsizeX();
	float getFuelsizeY();
	
	void resetHP();
	
	void update2(float elapsedTime);
	
	void resetFuel();
	
	Text getPunteggio();
	void AumentaPunteggio1();
	void AumentaPunteggio2();
	void AumentaPunteggio3();
	void AumentaPunteggio4();
	void resetPunteggio();
};