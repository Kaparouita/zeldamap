#include<allegro5\allegro5.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>

#include<iostream>
#include<fstream>
#include <sstream>
#include<cctype>
#include<stdio.h>
#include<string>
#include<vector>

#define screenW 640 //platos 640
#define screenH 480 //ypsos 480
#define blocksize 16

using namespace std;

int mapsizex, mapsizey, loadCounterX = 0, loadCounterY = 0;

//GIA CSV
void Loadmap(string filename, vector<vector<int>>& map) {

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
/*
//GIA TXT
void Loadmap(string filename, vector<vector<int>>& map) {

	ifstream openfile;
	openfile.open(filename);
	if (openfile.is_open()) {
		openfile >> mapsizex >> mapsizey;
		vector<int> tmp;

		while (!openfile.eof()) {
			int getn;// current number
			openfile >> getn;
			tmp.push_back(getn); //push back to temp vector
			loadCounterX++;
			if (loadCounterX >= mapsizex)
			{
				map.push_back(tmp); //push back current row
				tmp.clear();        //clear the vector
				loadCounterX = 0;
			}
		}
	}
	else {
		cout << "EROR LOADING MAP";
	}
}
*/

void CameraUpdate(float* cameraPosition, float x, float y, int width, int height) {
	cameraPosition[0] = (x + width / 2) - (screenW / 2);
	cameraPosition[1] = (y + height / 2) - (screenH / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;


}

void DrawMap(vector<vector<int>> map, ALLEGRO_BITMAP* tileset, vector<int> divIndex, vector<int> modIndex);
void initVectorsForMap(vector<int>& divIndex, vector<int>& modIndex, int width, int height);

int main() {

	enum Direction { DOWN, LEFT, RIGHT, UP };

	ALLEGRO_DISPLAY* display;
	const float fps = 60.0;
	const float frameFPS = 15.0;

	if (!al_init())
		al_show_native_message_box(NULL, "ERROR", NULL, "Fail init", NULL, NULL);


	display = al_create_display(screenW, screenH);

	if (!display)
		al_show_native_message_box(NULL, "ERROR", NULL, "Fail to create to display", NULL, NULL);

	al_set_window_position(display, 200, 200);
	bool active = false, draw = true, done = false;
	float x = 10, y = 10, moveSpeed = 5;
	int dir = DOWN, sourceX = 32, sourceY = 0;


	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TRANSFORM camera;

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / fps);
	ALLEGRO_TIMER* frameTimer = al_create_timer(1.0 / frameFPS);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());



	float cameraPosition[2] = { 0,0 };



	//----------------------LOAD MAP--------------------------------//
	vector<vector<int>> map1;
	vector<vector<int>> map2;
	vector<int> divIndex;
	vector<int> modIndex;

	Loadmap("D:\\csd2\\HY-454\\map1.csv", map1); //path
	Loadmap("D:\\csd2\\HY-454\\map2.csv", map2);

	ALLEGRO_BITMAP* tileset;
	ALLEGRO_BITMAP* player = al_load_bitmap("D:\\csd2\\HY-454\\player.png");
	//ALLEGRO_COLOR player = al_map_rgb(44, 117, 255);
	tileset = al_load_bitmap("D:\\csd2\\HY-454\\tileset.png");
	initVectorsForMap(divIndex, modIndex, 12, 20);


	al_start_timer(timer);
	al_start_timer(frameTimer);


	while (!done) {
		ALLEGRO_EVENT events;
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
					sourceX = 32;
				if (sourceX >= al_get_bitmap_width(player))
					sourceX = 0;
				sourceY = dir;
			}
			draw = true;
		}
		if (draw)
		{
			ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(player, sourceX, sourceY * 16, 16, 16);

			DrawMap(map2, tileset, divIndex, modIndex);
			DrawMap(map1, tileset, divIndex, modIndex);
			//al_draw_rectangle(x, y, x + 20, y + 20, player, 2.0);

			al_draw_bitmap(subBitmap, x, y, NULL);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_destroy_bitmap(subBitmap);
		}
	}

	al_destroy_bitmap(tileset);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(frameTimer);
	al_destroy_event_queue(event_queue);

	return 0;
}


void initVectorsForMap(vector<int>& divIndex, vector<int>& modIndex, int width, int height) {
	const int tiles = width * height;
	for (int i = 0; i < tiles; ++i)
		divIndex.push_back(i / width),
		modIndex.push_back(i % width);
}

void DrawMap(vector<vector<int>> map, ALLEGRO_BITMAP* tileset, vector<int> divIndex, vector<int> modIndex) {

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != -1) //an den einai -1
				al_draw_bitmap_region(tileset, blocksize * modIndex[map[i][j]]
					, divIndex[map[i][j]] * blocksize, blocksize, blocksize, j * blocksize, i * blocksize, NULL);
		}
	}
}