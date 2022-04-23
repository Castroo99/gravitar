#pragma once
#include <SFML/Graphics.hpp>
#include "Astronave.h"
#include "Proiettile.h"
#include "Pianeta.h"
#include "Bunker.h"
#include "TextureManager.h"
#include "Collision.h"
#include <vector>
#include <iostream>
using namespace sf;

class Engine {

private:

	RenderWindow Finestra;//crea una finestra
	Sprite backgroundSprite;// sprite sfondo
	

	Astronave astronave;
	vector<Pianeta> pianeti;
	vector<Sprite> hearts;
	int cnt;
	bool sistema;
	RectangleShape rTraente;
	ConvexShape terrenoShape;
	bool raggio;
	bool gameover;
	Sprite gameOverSprite;

	void input(); //funzione per impostare i comandi dell astronave
	void collision();
	void update(float dtAsSecond);
	void draw();
	vector<Pianeta>& getPianeti();
	Sprite GetGameOverSprite();
	int casuale();


public:

	Engine();//costruttore
	void start();
};
