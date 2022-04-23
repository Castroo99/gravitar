#include "Engine.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace sf;
using namespace std;

Engine::Engine() {
	//Crea la finestra di gioco e imposta la risoluzione
	Vector2f resolution;
	ContextSettings settings;
	settings.antialiasingLevel = 10;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	Finestra.create(VideoMode(resolution.x, resolution.y), "Gravitar", Style::Fullscreen, settings);
	
	backgroundSprite.setTexture(*textureManager.getsfondoTexture()); //sfondo

	rTraente = astronave.getrTraenteShape();
	gameOverSprite.setTexture(*textureManager.getGameOverTexture());
	Vector2f gameSize(resolution.x, resolution.y);
	gameOverSprite.setScale(gameSize.x / gameOverSprite.getLocalBounds().width, gameSize.y / gameOverSprite.getLocalBounds().height);
	gameover = false;
	sistema = true;
	cnt = 0;
	srand(time(NULL));
	getPianeti();
}

void Engine::start() {  // fa avviare il gioco

	Clock clock;

	while (Finestra.isOpen()) { //ciclo infinito che regola il gioco

		Time dt = clock.restart();
		float dtAsSecond = dt.asSeconds();
		input();
		collision();
		update(dtAsSecond);
		draw();
	}
}

void Engine::input() {     //funzione per impostare i comandi

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {

		Finestra.close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {

		astronave.moveUp();
	}
	else {

		astronave.stopUp();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {

		astronave.moveDown();
	}
	else {

		astronave.stopDown();
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {

		astronave.moveLeft();
	}
	else {

		astronave.stopLeft();
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {

		astronave.moveRight();
	}
	else {

		astronave.stopRight();
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {

		astronave.fire();
	}
	else {

		astronave.notFire();
	}
	if (Keyboard::isKeyPressed(Keyboard::C)) {

		astronave.fuelLine();
		raggio = true;
	}
	else {

		astronave.notFuelLine();
		raggio = false;
	}
	if (gameover && Keyboard::isKeyPressed(Keyboard::R)) {

		//RESETTA TUTTO QUANDO SI RIAVVIA IL GIOCO

		pianeti.clear();
		astronave.resetFuel();
		astronave.resetPunteggio();
		astronave.setPos(Vector2f(VideoMode::getDesktopMode().width - 100.0, VideoMode::getDesktopMode().height / 2));
		astronave.resetHP();
		getPianeti();
		cnt = 0;
		sistema = true;
		gameover = false;
	}
}

void Engine::collision() {

	vector<Proiettile>& bullets = astronave.getBullets();
	vector<Bunker>& bunkers = pianeti[cnt].getBunkers();
	vector<Bunker>& bunkers2 = pianeti[cnt].getBunkers2();
	vector<Proiettile>& bbullets = pianeti[cnt].getBbullets();
	vector<Proiettile>& bbullets2 = pianeti[cnt].getBbullets2();
	vector<Sprite>& hearts = astronave.getHearts();
	vector<Fuel>& fuels = pianeti[cnt].getFuels();
	vector<Fuel>& fuels2 = pianeti[cnt].getFuels2();
	RectangleShape& rTraente = astronave.getrTraenteShape();

	if (sistema == true) {

		for (int i = 0; i < pianeti.size(); i++) {

			//COLLISSIONE ASTRONAVE CON I PIANETI

			if (astronave.getSprite().getGlobalBounds().intersects(pianeti[i].getPianetiSprite().getGlobalBounds())) {

				cnt = i;
				sistema = false;
				astronave.setPos(Vector2f(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 6));
			}
		}
		if (astronave.getPosition().x > VideoMode::getDesktopMode().width) {

			astronave.setPos(Vector2f(0, astronave.getPosition().y));
		}

		else if (astronave.getPosition().x < 0) {

			astronave.setPos(Vector2f(VideoMode::getDesktopMode().width, astronave.getPosition().y));

		}
		else if (astronave.getPosition().y < 0) {

			astronave.setPos(Vector2f(astronave.getPosition().x, VideoMode::getDesktopMode().height));

		}
		else if (astronave.getPosition().y > VideoMode::getDesktopMode().height) {

			astronave.setPos(Vector2f(astronave.getPosition().x, 0));
		}
	}
	else {
		//COLLISIONE ASTRONAVE COL TERRENO

		VertexArray duepunti(Points, 2);
		VertexArray terrain = pianeti[cnt].getTerreno();

		if (astronave.getPosition().x > VideoMode::getDesktopMode().width) {

			astronave.setPos(Vector2f(0, astronave.getPosition().y));
		}

		else if (astronave.getPosition().x < 0) {

			astronave.setPos(Vector2f(VideoMode::getDesktopMode().width, astronave.getPosition().y));

		}
		else {

			bool trovato = false;

			for (int i = 0; i < 16 && !trovato; i++) {

				if (astronave.getPosition().x >= terrain[i].position.x && astronave.getPosition().x <= terrain[i + 1].position.x) {

					//INDIVIDUA IL SEGMENTO SOPRA AL QUALE SI TROVA L'ASTRONAVE

					duepunti[0].position = terrain[i].position;
					duepunti[1].position = terrain[i + 1].position;

					trovato = true;
				}
				else {

					trovato = false;
				}
			}

			//CALCOLA LA RETTA DEL SEGMENTO

			float m = (duepunti[1].position.y - duepunti[0].position.y) / (duepunti[1].position.x - duepunti[0].position.x);
			float q = (((duepunti[1].position.x * duepunti[0].position.y) - (duepunti[0].position.x * duepunti[1].position.y)) / (duepunti[1].position.x - duepunti[0].position.x));

			bool astronave_vita2 = false;

			//VERIFICA LA COLLISIONE TRA IL TERRENO E L'ASTRONAVE

			if ((astronave.getPosition().x * m) + q < astronave.getPosition().y) {

				astronave_vita2 = true;
				astronave.DiminuisciVita();
				astronave.setPos(Vector2f(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 6));

				for (int z = 0; z < hearts.size() && astronave_vita2; z++) {

					hearts.erase(hearts.begin());
					z--;
					astronave_vita2 = false;
				}

				if (astronave.getVita() == 0) {

					gameover = true;

				}
			}
			// RAGGIO TRAENTE E TERRENO

			float y1 = abs(astronave.getPosition().y - (m * astronave.getPosition().x + q)) / (sqrt(1 + m * m), 2);
			rTraente.setSize(Vector2f(2 * y1, 5));
		}

		// COLLISIONE PROIETTILI ASTRONAVE COL TERRENO

		VertexArray duepunti1(Points, 2);


		for (int j = 0; j < bullets.size(); j++) {

			bool trovato1 = false;

			for (int i = 0; i < 16 && !trovato1; i++) {

				if (bullets[j].getposition().x >= terrain[i].position.x && bullets[j].getposition().x <= terrain[i + 1].position.x) {

					duepunti1[0].position = terrain[i].position;
					duepunti1[1].position = terrain[i + 1].position;
					trovato1 = true;
				}
				else {

					trovato1 = false;
				}
			}
			float m1 = (duepunti1[1].position.y - duepunti1[0].position.y) / (duepunti1[1].position.x - duepunti1[0].position.x);
			float q1 = (((duepunti1[1].position.x * duepunti1[0].position.y) - (duepunti1[0].position.x * duepunti1[1].position.y)) / (duepunti1[1].position.x - duepunti1[0].position.x));

			if ((bullets[j].getSprite().getPosition().x * m1) + q1 < bullets[j].getSprite().getPosition().y) {

				bullets.erase(bullets.begin() + j);
				j--;
			}
			//}
		}

				//COLLISIONE PROIETTILI ASTRONAVE E BUNKER1
		
		for (int i = 0; i < bullets.size(); i++) {

			bool bullet_alive = true;

			for (int j = 0; j < bunkers.size() && bullet_alive; j++) {

				if (Collision::PixelPerfectTest(bunkers[j].getSprite(), bullets[i].getSprite())) {

					bunkers[j].DiminuisciVita();
					bullets.erase(bullets.begin() + i);
					i--;

					if (bunkers[j].getVita() == 0) {

						bunkers.erase(bunkers.begin() + j);
						j--;
						astronave.AumentaPunteggio1();
					}
					bullet_alive = false;
				}
			}
			if (bullet_alive) {

				if (bullets[i].getSprite().getPosition().x < 0 || bullets[i].getSprite().getPosition().x > VideoMode::getDesktopMode().width
					|| bullets[i].getSprite().getPosition().y < 0 || bullets[i].getSprite().getPosition().y > VideoMode::getDesktopMode().height) {

					bullets.erase(bullets.begin() + i);
					i--;
					bullet_alive = false;
				}
			}
		}	    
				// COLLISIONE PROIETTILI ASTRONAVE E BUNKER2				
		
		for (int i = 0; i < bullets.size(); i++) {

			bool bullet_alive = true;

			for (int j = 0; j < bunkers2.size() && bullet_alive; j++) {

				if (Collision::PixelPerfectTest(bunkers2[j].getSprite(), bullets[i].getSprite())) {

					bunkers2[j].DiminuisciVita();
					bullets.erase(bullets.begin() + i);
					i--;

					if (bunkers2[j].getVita() == 0) {

						bunkers2.erase(bunkers2.begin() + j);
						j--;
						astronave.AumentaPunteggio2();
					}
					bullet_alive = false;
				}
			}
			if (bullet_alive) {

				if (bullets[i].getSprite().getPosition().x < 0 || bullets[i].getSprite().getPosition().x > VideoMode::getDesktopMode().width
					|| bullets[i].getSprite().getPosition().y < 0 || bullets[i].getSprite().getPosition().y > VideoMode::getDesktopMode().height) {

					bullets.erase(bullets.begin() + i);
					i--;
					bullet_alive = false;
				}
			}
		}

						//COLLISIONE PROIETTILI BUNKER1 E ASTRONAVE

		for (int i = 0; i < bbullets.size(); i++) {

			bool astronave_vita = false;
			bool bbullet_alive = true;

			for (int j = 0; j < bunkers.size() && bbullet_alive; j++) {

				if (Collision::PixelPerfectTest(astronave.getSprite(), bbullets[i].getSprite())) {

					astronave.DiminuisciVita();
					astronave_vita = true;

					for (int z = 0; z < hearts.size() && astronave_vita; z++) {

						hearts.erase(hearts.begin() + z);
						z--;
						astronave_vita = false;
					}
					bbullets.erase(bbullets.begin() + i);
					i--;

					if (astronave.getVita() == 0) {

						gameover = true;
					}
					bbullet_alive = false;
				}
			}
			if (bbullet_alive) {

				//ELIMINA I PROIETTILI SE OLTREPASSANO LO SCHERMO

				if (bbullets[i].getSprite().getPosition().x < 0 || bbullets[i].getSprite().getPosition().x > VideoMode::getDesktopMode().width
					|| bbullets[i].getSprite().getPosition().y < 0 || bbullets[i].getSprite().getPosition().y > VideoMode::getDesktopMode().height) {

					bbullets.erase(bbullets.begin() + i);
					i--;
					bbullet_alive = false;
				}
			}
		}

							//COLLISIONE PROIETTILI BUNKER2 E ASTRONAVE

		for (int i = 0; i < bbullets2.size(); i++) {

			bool astronave_vita3 = false;
			bool bbullet2_alive2 = true;

			for (int j = 0; j < bunkers2.size() && bbullet2_alive2; j++) {

				if (Collision::PixelPerfectTest(astronave.getSprite(), bbullets2[i].getSprite())) {

					astronave.DiminuisciVita();
					astronave_vita3 = true;

					for (int z = 0; z < hearts.size() && astronave_vita3; z++) {

						hearts.erase(hearts.begin() + z);
						z--;
						astronave_vita3 = false;
					}

					bbullets2.erase(bbullets2.begin() + i);
					i--;

					if (astronave.getVita() == 0) {

						gameover = true;
					}
					bbullet2_alive2 = false;
				}
			}
			if (bbullet2_alive2) {

				//ELIMINA I PROIETTILI SE OLRTREPASSANO LO SCHERMO

				if (bbullets2[i].getSprite().getPosition().x < 0 || bbullets2[i].getSprite().getPosition().x > VideoMode::getDesktopMode().width
					|| bbullets2[i].getSprite().getPosition().y < 0 || bbullets2[i].getSprite().getPosition().y > VideoMode::getDesktopMode().height) {

					bbullets2.erase(bbullets2.begin() + i);
					i--;
					bbullet2_alive2 = false;
				}
			}
		}

		//COLLISIONE BBULLETS BUNKER COL TERRENO

		VertexArray duepunti5(Points, 2);


		for (int j = 0; j < bbullets.size(); j++) {

			bool trovato5 = false;

			for (int i = 0; i < 16 && !trovato5; i++) {

				if (bbullets[j].getposition().x >= terrain[i].position.x && bbullets[j].getposition().x <= terrain[i + 1].position.x) {

					duepunti5[0].position = terrain[i].position;
					duepunti5[1].position = terrain[i + 1].position;
					trovato5 = true;
				}
				else {

					trovato5 = false;
				}
			}
			float m1 = (duepunti5[1].position.y - duepunti5[0].position.y) / (duepunti5[1].position.x - duepunti5[0].position.x);
			float q1 = (((duepunti5[1].position.x * duepunti5[0].position.y) - (duepunti5[0].position.x * duepunti5[1].position.y)) / (duepunti5[1].position.x - duepunti5[0].position.x));

			if ((bbullets[j].getSprite().getPosition().x * m1) + q1 < bbullets[j].getSprite().getPosition().y) {

				bbullets.erase(bbullets.begin() + j);
				j--;
			}
			//}
		}

				//COLLISIONE RAGGIO TRAENTE E CARBURANTE1
		
		for (int i = 0; i < fuels.size(); i++) {

			if (rTraente.getGlobalBounds().intersects(fuels[i].getSprite().getGlobalBounds())) {

				astronave.addFuel1();
				fuels.erase(fuels.begin() + i);
				i--;
			}
		}

				//COLLISIONE RAGGIO TRAENTE E CARBURANTE2
		
		for (int j = 0; j < fuels2.size(); j++) {

			if (rTraente.getGlobalBounds().intersects(fuels2[j].getSprite2().getGlobalBounds())) {

				astronave.addFuel2();
				fuels2.erase(fuels2.begin() + j);
				j--;
			}
		}

				//ELIMINA I PROIETTILI QUANDO SEI NEL SISTEMA SOLARE
		
		if (sistema = false) {

			for (int i = 0; i < bbullets.size(); i++) {

				bbullets.erase(bbullets.begin() + i);
				i--;
			}
			for (int j = 0; j < bbullets2.size(); j++) {

				bbullets2.erase(bbullets2.begin() + j);
				j--;
			}
		}
		
				//GAMEOVER QUANDO FINISCI IL FUEL
		
		if (astronave.getFuelsizeX() <= 0) {

			gameover = true;
		}

		if (astronave.getSprite().getPosition().y <= 0) {

			sistema = true;
		}
	}

			//ELIMINA IL PIANETA QUANDO TUTTI I BUNKER VENGONO ELIMINATI

	if (bunkers.size() == 0 && bunkers2.size() == 0) {

		sistema = true;
		pianeti.erase(pianeti.begin() + cnt);
		cnt = 0;
		astronave.AumentaPunteggio3();
	}
}

void Engine::update(float dtAsSecond) {   // aggiorna il gioco

	astronave.update(dtAsSecond);

	if (pianeti.size() == 0) {

		getPianeti();
		astronave.AumentaPunteggio4();
	}

	if (!sistema) {

		pianeti[cnt].update(dtAsSecond);
		astronave.update2(dtAsSecond);
	}
	vector<Proiettile>& bullets = astronave.getBullets();

	if (sistema) {
	
		for (int i = 0; i < bullets.size(); i++) {

			bullets.erase(bullets.begin() + i);  // non puoi sparare se sei nel sistema solare
			i--;
		}
	}
}

void Engine::draw() {    //DISEGNA GLI ELEMENTI DEL GIOCO IN BASE A DOVE SI TROVA L'ASTRONAVE

	if (sistema) {

		Finestra.clear(Color::Black);
		Finestra.draw(backgroundSprite);
		Finestra.draw(astronave.getPunteggio());
		Finestra.draw(astronave.getSprite());

		for (int j = 0; j < pianeti.size(); j++) {

			Finestra.draw(pianeti[j].getPianetiSprite());
		}

		Finestra.draw(astronave.getFuelShape());
		Finestra.draw(astronave.getFuelShape1());

		vector<Sprite>& hearts = astronave.getHearts();

		for (int i = 0; i < hearts.size(); i++) {

			Finestra.draw(hearts[i]);
		}
	}
	else {

		Finestra.draw(backgroundSprite);
		Finestra.draw(astronave.getPunteggio());
		Finestra.draw(astronave.getSprite());
		Finestra.draw(pianeti[cnt].getTerreno());

		vector<Proiettile>& bullets = astronave.getBullets();

		for (int i = 0; i < bullets.size(); i++) {

			Finestra.draw(bullets[i].getSprite());
		}

		vector<Bunker>& bunkers = pianeti[cnt].getBunkers();

		for (int i = 0; i < bunkers.size(); i++) {

			Finestra.draw(bunkers[i].getSprite());
		}

		vector<Bunker>& bunkers2 = pianeti[cnt].getBunkers2();

		for (int i = 0; i < bunkers2.size(); i++) {

			Finestra.draw(bunkers2[i].getSprite2());
		}

		vector<Fuel>& fuels = pianeti[cnt].getFuels();

		for (int i = 0; i < fuels.size(); i++) {

			Finestra.draw(fuels[i].getSprite());
		}

		vector<Fuel>& fuels2 = pianeti[cnt].getFuels2();

		for (int i = 0; i < fuels2.size(); i++) {

			Finestra.draw(fuels2[i].getSprite2());
		}

		vector<Proiettile>& bbullets = pianeti[cnt].getBbullets();

		for (int j = 0; j < bbullets.size(); j++) {

			Finestra.draw(bbullets[j].getSprite());
		}

		vector<Proiettile>& bbullets2 = pianeti[cnt].getBbullets2();

		for (int j = 0; j < bbullets2.size(); j++) {

			Finestra.draw(bbullets2[j].getSprite());
		}

		vector<Sprite>& hearts = astronave.getHearts();

		for (int i = 0; i < hearts.size(); i++) {

			Finestra.draw(hearts[i]);
		}

		Finestra.draw(astronave.getFuelShape());
		Finestra.draw(astronave.getFuelShape1());

		if (raggio == true) {

			Finestra.draw(astronave.getrTraenteShape());
		}

		if (gameover) {

			Finestra.clear(Color::Black);
			Finestra.draw(GetGameOverSprite());
		}
	}

	Finestra.display();
}

vector<Pianeta>& Engine::getPianeti() {

	//CREA UN NUMERO CASUALE DI PIANETI ALL'INIZIO DEL GIOCO E OGNI QUAL VOLTA VIENE RIAVVIATO IL GIOCO

	int x = casuale();
	vector<float> coordx;
	vector<float> coordy;

	//I VETTORI 'coordx' e 'coordy' SONO IMPOSTATI IN MODO TALE DA NON AVERE MAI UN PIANETA SOVRAPPOSTO AD UN ALTRO

	for (int t = 0; t < x; t++) {

		coordx.push_back(float(rand() % (3 * VideoMode::getDesktopMode().width / 5) + 100.0));

		for (int t1 = 0; t1 < t; t1++) {

			if (coordx[t] <= coordx[t1] + 50 && coordx[t] >= coordx[t1] - 50) {

				coordx.erase(coordx.begin() + t);
				t--;
			}

		}
	}
	for (int t = 0; t < x; t++) {

		coordy.push_back(float(rand() % (4 * VideoMode::getDesktopMode().height / 5) + 100.0));

		for (int t1 = 0; t1 < t; t1++) {

			if (coordy[t] <= coordy[t1] + 50 && coordy[t] >= coordy[t1] - 50) {

				coordy.erase(coordy.begin() + t);
				t--;
			}
		}
	}

	//INSERISCE I PIANETI NEL VECTOR

	for (int i = 0; i < x; i++) {

		pianeti.push_back(Pianeta(Vector2f(coordx[i], coordy[i]), 100));
	}

	return pianeti;
}

Sprite Engine::GetGameOverSprite() {

	return gameOverSprite;
}

int Engine::casuale() {

	return rand() % 5 + 3;
}


