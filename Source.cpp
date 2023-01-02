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

#define screenW 800 //platos 640
#define screenH 600 //ypsos 480
#define blocksize 40

using namespace std;

int mapsizex, mapsizey, loadCounterX = 0, loadCounterY = 0;


void LoadTileInfo(const char* filename, ALLEGRO_BITMAP* tileset) {
	tileset = al_load_bitmap(filename);
}

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
void DrawMap(vector<vector<int>> map, ALLEGRO_BITMAP* tileset, vector<int> divIndex, vector<int> modIndex);
void initVectorsForMap(vector<int>& divIndex, vector<int>& modIndex, int width, int height);

int main() {



	ALLEGRO_DISPLAY* display;
	float fps = 60.0;
	bool done = false;

	if (!al_init())
		al_show_native_message_box(NULL, "ERROR", NULL, "Fail init", NULL, NULL);


	display = al_create_display(screenW, screenH);

	if (!display)
		al_show_native_message_box(NULL, "ERROR", NULL, "Fail to create to display", NULL, NULL);

	al_set_window_position(display, 200, 200);
	al_init_primitives_addon();
	al_init_image_addon();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / fps);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));


	vector<vector<int>> map;
	vector<int> divIndex;
	vector<int> modIndex;

	Loadmap("D:\\csd2\\HY-454\\testcsv.csv", map); //path

	ALLEGRO_BITMAP* tileset;
	tileset = al_load_bitmap("D:\\csd2\\HY-454\\tileset.png");
	LoadTileInfo("D:\\csd2\\HY-454\\tileset.png", tileset);
	initVectorsForMap(divIndex, modIndex, 12, 20);
	//al_set_target_bitmap(tileset);

	al_start_timer(timer);


	while (!done) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		else if (events.type == ALLEGRO_EVENT_TIMER) {}

		DrawMap(map, tileset, divIndex, modIndex);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_bitmap(tileset);
	al_destroy_display(display);
	al_destroy_timer(timer);
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
			al_draw_bitmap_region(tileset, 16 * modIndex[map[i][j]]
				, divIndex[map[i][j]] * 16, 16, 16, j * 16, i * 16, NULL);
		}
	}
}