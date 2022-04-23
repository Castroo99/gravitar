#include<SFML/Graphics.hpp>
#include <iostream>
#include<ctime>
#include <cmath>
#include "Pianeta.h"
#include "Bunker.h"
#include "Fuel.h"
#include "Astronave.h"
using namespace sf;
using namespace std;
#define PI 3.459265

Pianeta::Pianeta(Vector2f pos, float rad) {

	Vector2i screenDimension(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	VertexArray line(LinesStrip, 17);                // CREO LINEE TERRENO
	float y = screenDimension.y - 200.f;
	float casuale[16];

	for (int i = 0; i < 16; i++) {

		casuale[i] = rand() % 200 - (200 / 2);
	}
	line[0].position = Vector2f(0, y);
	float dimSchermo = 0;

	for (int j = 1; j <= 16; j++) {

		int i = j - 1;
		dimSchermo = dimSchermo + (screenDimension.x / 16);
		line[j].position = Vector2f(dimSchermo, y - casuale[i]);
	}
	terreno = line;

	// GENERA NUMERI CASUALI PER COORDINATE CASUALI BUNKER
	
	int b = random1();
	int c = random2();
	int n = b + c;
	vector<int> a; //vettore numeri casuali

	for (int t = 0; t < n; t++) {

		a.push_back(int(rand() % 15 + 1));

		for (int t1 = 0; t1 < t; t1++) {

			if (a[t] == a[t1]) {

				a.erase(a.begin() + t);
				t--;
			}
		}
	}
	
	// CREAZIONE BUNKER1
	
	int i = 0;

	while (i < b) {

		bool generato = false;

		while (!generato) {

			float equazionex = (terreno[a[i]].position.x + terreno[a[i] + 1].position.x) / 2;
			float equazioney = (terreno[a[i]].position.y + terreno[a[i] + 1].position.y) / 2;

			float m = ((terreno[a[i] + 1].position.y - terreno[a[i]].position.y) / (terreno[a[i] + 1].position.x - terreno[a[i]].position.x));
			float arctng = atan(m) * 180 / PI;

			bunkers.push_back(Bunker(Vector2f(equazionex, equazioney), arctng));
			i++;
			generato = true;
		}
	}
	
	// CREAZIONE BUNKER2
	
	int h = b;

	while (h < b + c) {

		bool generato2 = false;

		while (!generato2) {

			float equazionex1 = (terreno[a[h]].position.x + terreno[a[h] + 1].position.x) / 2;
			float equazioney1 = (terreno[a[h]].position.y + terreno[a[h] + 1].position.y) / 2;

			float m1 = ((terreno[a[h] + 1].position.y - terreno[a[h]].position.y) / (terreno[a[h] + 1].position.x - terreno[a[h]].position.x));
			float arctng1 = atan(m1) * 180 / PI;

			bunkers2.push_back(Bunker(Vector2f(equazionex1, equazioney1), arctng1));
			h++;
			generato2 = true;
		}
	}
	
	// CREO FUEL1

	fuels.push_back(Fuel(RandomCoordTerrain1()));

	// CREO FUEL2

	fuels2.push_back(Fuel(RandomCoordTerrain2()));

	pianetiSprite.setPosition(pos);
	pianetiSprite.setScale(0.3, 0.3);
	pianetiSprite.setTexture(*textureManager.getPianetiTexture());

}


VertexArray Pianeta::getTerreno() {

	return terreno;
}



Vector2f Pianeta::RandomCoordTerrain1() {

	Vector2f terr_rand;

	int i = rand() % 8;

	terr_rand.x = terreno[i].position.x;
	terr_rand.y = terreno[i].position.y;

	return terr_rand;
}

Vector2f Pianeta::RandomCoordTerrain2() {

	Vector2f terr_rand;
	
	int i = rand() % 8 + 8;

	terr_rand.x = terreno[i].position.x;
	terr_rand.y = terreno[i].position.y - 30.0;

	return terr_rand;
}

void Pianeta::update(float elapsedTime) {

	for (int i = 0; i < bunkers.size(); i++) {

		bunkers[i].update(elapsedTime, bbullets);
	}

	for (int k = 0; k < bunkers2.size(); k++) {

		bunkers2[k].update2(elapsedTime, bbullets2);
	}

	for (int j = 0; j < bbullets.size(); j++) {

		bbullets[j].update(elapsedTime);
	}

	for (int j = 0; j < bbullets2.size(); j++) {

		bbullets2[j].update(elapsedTime);
	}

	rTraente.setSize(Vector2f(150, 10));
}


int Pianeta::random1() {

	return rand() % 3 + 1;
}

int Pianeta::random2() {
	
	return rand() % 3 + 1;
}

Sprite Pianeta::getPianetiSprite() {

	return pianetiSprite;
}

vector<Bunker>& Pianeta::getBunkers() {

	return bunkers;
}

vector<Bunker>& Pianeta::getBunkers2() {

	return bunkers2;
}

vector<Fuel>& Pianeta::getFuels() {

	return fuels;
}

vector<Proiettile>& Pianeta::getBbullets() {

	return bbullets;
}

vector<Proiettile>& Pianeta::getBbullets2() {

	return bbullets2;
}

vector<Fuel>& Pianeta::getFuels2() {

	return fuels2;
}