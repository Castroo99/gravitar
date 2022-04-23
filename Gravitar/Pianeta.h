#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include"Bunker.h"
#include"Fuel.h"
using namespace sf;
using namespace std;

class Pianeta {

private:

	VertexArray terreno;
	CircleShape pianetaShape;
	vector<Bunker> bunkers;
	vector<Bunker> bunkers2;
	vector<Fuel> fuels;
	vector<Proiettile> bbullets;
	vector<Proiettile> bbullets2;
	vector<Fuel> fuels2;
	Direction dir;
	CircleShape pianeti;
	Sprite pianetiSprite;
	RectangleShape rTraente;
	int casuale1;
	int casuale2;

public:

	Pianeta(Vector2f pos, float rad);
	VertexArray getTerreno();
	Vector2f RandomCoordTerrain1(); // coordinate fuel1
	Vector2f RandomCoordTerrain2(); // coordinate fuel2
	vector<Bunker>& getBunkers();
	vector<Bunker>& getBunkers2();
	vector<Fuel>& getFuels();
	vector<Proiettile>& getBbullets();
	vector<Proiettile>& getBbullets2();
	vector<Fuel>& getFuels2();
	Sprite getPianetiSprite();
	void update(float elapsedTime);
	int random1(); // coordinate bunker1
	int random2(); // coordinate bunker2

};


