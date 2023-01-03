#include "Game.h"

void Game::setDisplay(int Width, int Height) {
	display = al_create_display(Width, Height);
	al_set_window_position(display, 200, 200);
}

void Game::setDisplayMainValues() {
	display = al_create_display(screenW, screenH);
	al_set_window_position(display, 200, 200);
}
void Game::initTimers() {
	timer = al_create_timer(1.0 / fps);
	frameTimer = al_create_timer(1.0 / frameFPS);
	event_queue = al_create_event_queue();
}

void Game::registerValues() {
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void Game::LoadMap(string filename, vector<vector<int>>& map) {
	ifstream openfile(filename);
	if (openfile.is_open()) {
		string line;
		vector<int> row;
		int i = 0;
		while (getline(openfile, line))
		{
			stringstream iss(line);
			string val;
			while (getline(iss, val, ','))
				row.push_back(stoi(val));
			map.push_back(row);
			row.clear();
		}
	}
	else {
		cout << "EROR LOADING MAP";
	}
}

void initVectorsForMap(vector<int>& divIndex, vector<int>& modIndex, int width, int height) {
	const int tiles = width * height;
	for (int i = 0; i < tiles; ++i)
		divIndex.push_back(i / width),
		modIndex.push_back(i % width);
}

void Game::LoadMaps() {
	tileset = al_load_bitmap("D:\\csd2\\HY-454\\images\\tileset.png");
	initVectorsForMap(divIndex, modIndex, 12, 20);
	player = al_load_bitmap("D:\\csd2\\HY-454\\images\\player.png");
	LoadMap("D:\\csd2\\HY-454\\images\\map1.csv", map1);
	LoadMap("D:\\csd2\\HY-454\\images\\map2.csv", map2);
}

void Game::CameraUpdate(float* cameraPosition, float x, float y, int width, int height) {
	cameraPosition[0] = (x + width / 2) - (screenW / 2);
	cameraPosition[1] = (y + height / 2) - (screenH / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;
}


void Game::DrawMap(vector<vector<int>> map, ALLEGRO_BITMAP* tileset, vector<int> divIndex, vector<int> modIndex) {

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != -1) //an den einai -1
				al_draw_bitmap_region(tileset, blocksize * modIndex[map[i][j]]
					, divIndex[map[i][j]] * blocksize, blocksize, blocksize, j * blocksize, i * blocksize, NULL);
		}
	}
}

void Game::MainLoop() {

	al_start_timer(timer);
	al_start_timer(frameTimer);


	while (!done) {

		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;//CLOSE IF X
		else if (events.type == ALLEGRO_EVENT_TIMER) {
			if (events.timer.source == timer) {
				active = true;
				//MOVING
				al_get_keyboard_state(&keyState);
				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
					y += moveSpeed;
					dir = DOWN;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
					y -= moveSpeed;
					dir = UP;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
					x += moveSpeed;
					dir = RIGHT;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
					x -= moveSpeed;
					dir = LEFT;
				}
				else
					active = false;

				/*scrolling*/
				CameraUpdate(cameraPosition, x, y, 16, 16);

				al_identity_transform(&camera);
				al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
				al_use_transform(&camera);

			}

			else if (events.timer.source == frameTimer) {
				if (active)
					sourceX += al_get_bitmap_width(player) / 3;
				else
					sourceX = 16;
				if (sourceX >= al_get_bitmap_width(player))
					sourceX = 0;
				sourceY = dir;
			}
			draw = true;
		}
		if (draw)
		{
			ALLEGRO_BITMAP* subBitmap;
			subBitmap = al_create_sub_bitmap(player, sourceX, sourceY * 16, 16, 16);
			DrawMap(map2, tileset, divIndex, modIndex);
			DrawMap(map1, tileset, divIndex, modIndex);
			//al_draw_rectangle(x, y, x + 20, y + 20, player, 2.0);

			al_draw_bitmap(subBitmap, x, y, NULL);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_destroy_bitmap(subBitmap);
		}
	}

}

void Game::MainLoopIteration() {

}

void Game::Destroy() {
	al_destroy_bitmap(tileset);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(frameTimer);
	al_destroy_event_queue(event_queue);
}

