#pragma once
#include<allegro5\allegro5.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<vector>
#include <string>
#include<fstream>
#include <sstream>
#include<cctype>
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>

using namespace std;

#ifndef Game_h
#define Game_h


#define screenW 640 //platos 640
#define screenH 480 //ypsos 480
#define blocksize 16


class Game {

protected:
	enum Direction { DOWN, LEFT, RIGHT, UP }; //movement
	ALLEGRO_DISPLAY* display;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TRANSFORM camera;
	ALLEGRO_TIMER* timer;
	ALLEGRO_TIMER* frameTimer;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_BITMAP* tileset;
	ALLEGRO_BITMAP* player;
	ALLEGRO_EVENT events;


	const float fps = 60.0;
	const float frameFPS = 15.0;
	float cameraPosition[2] = { 0,0 };
	bool active = false, draw = true, done = false;
	float x = 10, y = 10, moveSpeed = 5;
	int dir = DOWN, sourceX = 16, sourceY = 0;

	vector<vector<int>> map1;
	vector<vector<int>> map2;
	vector<int> divIndex;
	vector<int> modIndex;

	/**
	 * Given a csv file fill a 2d vector with its values.
	 */
	void LoadMap(string filename, vector<vector<int>>& map);
public:

	ALLEGRO_DISPLAY* GetDisplay() { return display; }

	/**
	 * load map1/map2 and init tileset.
	 */
	void LoadMaps();
	void setDisplay(int Width, int Height);
	void setDisplayMainValues();
	void initTimers();
	void registerValues();
	void CameraUpdate(float* cameraPosition, float x, float y, int width, int height);
	void DrawMap(vector<vector<int>> map, ALLEGRO_BITMAP* tileset, vector<int> divIndex, vector<int> modIndex);

	void MainLoop();
	void MainLoopIteration();

	void Destroy();
};

#endif // !Game_h


