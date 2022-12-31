#include<allegro5\allegro5.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_primitives.h>

#include<iostream>
#include<fstream>
#include <sstream>
#include<cctype>
#include<stdio.h>
#include<string>
#include<vector>

#define screenW 640 //platos
#define screenH 480 //ypsos
#define blocksize 40

using namespace std;

int mapsizex, mapsizey, loadCounterX = 0, loadCounterY = 0;

//GIA CSV
/*
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
}*/
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

void DrawMap(vector<vector<int>> map);

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
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / fps);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));


	vector<vector<int>> map;

	Loadmap("D:\\csd2\\HY-454\\test.txt", map); //path

	al_start_timer(timer);


	while (!done) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		else if (events.type == ALLEGRO_EVENT_TIMER) {}

		DrawMap(map);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

void DrawMap(vector<vector<int>> map) {
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++) {

			if (map[i][j] == 0)
				al_draw_filled_rectangle(j * blocksize, i * blocksize, j * blocksize + blocksize, i * blocksize + blocksize, al_map_rgb(0, 0, 255));
			else if (map[i][j] == 1)
				al_draw_filled_rectangle(j * blocksize, i * blocksize, j * blocksize + blocksize, i * blocksize + blocksize, al_map_rgb(0, 255, 0));

			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}