#include "Engine/Core/Application.h"
#include "Game/Core/LevelLayer.h"
#include <iostream>


int main()
{

	Tassathras::Application app;

	app.pushLayer(new Game::LevelLayer());
	app.run();


	return 0;
}
