#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class TextureManager{

private:
	
	Texture* bulletTexture;
	Texture* bunkerTexture;
	Texture* fuelTexture;
	Texture* pianetiTexture;
	Texture* fuelTexture2;
	Texture* bunkerTexture2;
	Texture* gameOverTexture;
	Texture* heartTexture;
	Texture* AstronaveTexture;
	Texture* sfondoTexture;

public:

	void loadAllTextures();

	Texture * getBulletTexture();
	Texture * getBunkerTexture();
	Texture * getBunkerTexture2();
	Texture * getFuelTexture();
	Texture * getPianetiTexture();
	Texture * getFuelTexture2();
	Texture * getGameOverTexture();
	Texture * getHeartTexture();
	Texture * getAstronaveTexture();
	Texture * getsfondoTexture();
};

extern TextureManager textureManager;