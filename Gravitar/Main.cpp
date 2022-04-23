// gravitar.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Engine.h"
using namespace sf;

int main() {

	textureManager.loadAllTextures();
	Engine engine;
	engine.start();

	return 0;
}
