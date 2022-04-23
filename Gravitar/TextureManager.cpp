#include "TextureManager.h"

TextureManager textureManager;

void TextureManager::loadAllTextures(){

	bulletTexture = new Texture();
	bulletTexture -> loadFromFile("proiettile.jpg");
	bulletTexture->setSmooth(true);

	bunkerTexture = new Texture();
	bunkerTexture -> loadFromFile("bunker1.png");
	bunkerTexture->setSmooth(true);

	bunkerTexture2 = new Texture();
	bunkerTexture2 -> loadFromFile("bunker2.png");
	bunkerTexture2->setSmooth(true);

	fuelTexture = new Texture();
	fuelTexture -> loadFromFile("fuel1.png");
	fuelTexture->setSmooth(true);

	fuelTexture2 = new Texture();
	fuelTexture2->loadFromFile("fuel2.png");
	fuelTexture2->setSmooth(true);

	pianetiTexture = new Texture();
	pianetiTexture -> loadFromFile("Planet.png");
	pianetiTexture->setSmooth(true);

	gameOverTexture = new Texture();
	gameOverTexture -> loadFromFile("gameover.png");

	heartTexture = new Texture();
	heartTexture->loadFromFile("heart.png");
	heartTexture->setSmooth(true);

	AstronaveTexture = new Texture();
	AstronaveTexture->loadFromFile("ship.png");
	AstronaveTexture->setSmooth(true);

	sfondoTexture = new Texture();
	sfondoTexture->loadFromFile("sfondo.jpg");
	sfondoTexture->setSmooth(true);
}

Texture * TextureManager::getBulletTexture(){

	return bulletTexture;
}

Texture * TextureManager::getBunkerTexture(){

	return bunkerTexture;
}

Texture * TextureManager::getBunkerTexture2(){

	return bunkerTexture2;
}

Texture * TextureManager::getFuelTexture(){

	return fuelTexture;
}

Texture * TextureManager::getPianetiTexture(){

	return pianetiTexture;
}

Texture * TextureManager::getFuelTexture2(){

	return fuelTexture2;
}

Texture * TextureManager::getGameOverTexture(){

	return gameOverTexture;
}

Texture * TextureManager::getHeartTexture(){

	return heartTexture;
}

Texture * TextureManager::getAstronaveTexture()
{
	return AstronaveTexture;
}

Texture * TextureManager::getsfondoTexture()
{
	return sfondoTexture;
}
