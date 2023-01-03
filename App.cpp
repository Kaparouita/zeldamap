#include "App.h"

using namespace app;

void App::Initialise() {
	if (!al_init())
		al_show_native_message_box(NULL, "ERROR", NULL, "Fail init", NULL, NULL);

	game.setDisplayMainValues();

	if (!game.GetDisplay())
		al_show_native_message_box(NULL, "ERROR", NULL, "Fail to create to display", NULL, NULL);

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	game.initTimers();
}

void App::Load() {
	game.registerValues();
	game.LoadMaps();
}

void App::Run() {
	game.MainLoop();
}

void App::RunIteration() {

}

void App::Clear() {
	game.Destroy();
}


void App::Main() {
	Initialise();
	Load();
	Run();
	//Clear();
}

Game& App::GetGame() {
	return game;
}
const Game& App::GetGame() const {
	return game;
}



int main() {
	App app;
	app.Main();
}


