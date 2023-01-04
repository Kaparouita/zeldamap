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
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define TileSetWidth 12
#define TileSetHeight 21
#define TILES TileSetWidth*TileSetHeight
#define X_MOVEMENT 8
#define Y_MOVEMENT 8
#define MOVE_SPEED 4
#define FPS_TIMER 20
#define FPS_FRAME 15
#define MAX_WIDTH 1024
#define MAX_HEIGHT 256

typedef unsigned short Index; // [MSB X][LSB Y]
typedef int Dim; // [MSB X][LSB Y]
typedef vector<vector<int>> TileMap;

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
	//ALLEGRO_BITMAP* player;
	ALLEGRO_EVENT events;


	float cameraPosition[2] = { 0,0 };
	bool active = false, draw = true, done = false;
	float x = X_MOVEMENT, y = Y_MOVEMENT;
	int dir = DOWN, sourceX = 8, sourceY = 0;

	int divIndex[TILES];
	int modIndex[TILES];

	/**
	 * Given a csv file fill a 2d vector with its values.
	 */
	void LoadMap(string filename, vector<vector<int>>& map);
public:
	TileMap map1;
	TileMap map2;

	void SetTile(TileMap* m, Dim col, Dim row, Index index);

	Index GetTile(const TileMap* m, Dim col, Dim row);


	ALLEGRO_DISPLAY* GetDisplay() { return display; }

	/**
	 * load map1/map2 and init tileset.
	 */
	void LoadMaps();
	/**
	 * set display of the window.
	 */
	void setDisplay(int Width, int Height);
	/**
	 * set display with already defined values.
	 */
	void setDisplayMainValues();
	/**
	 * init timer/fpstimer.
	 */
	void initTimers();
	/**
	 * register timer/dispay/key.
	 */
	void registerValues();
	/**
	 * update camera on movement.
	 */
	void CameraUpdate(float* cameraPosition, float x, float y, int width, int height);
	/**
	 * Draw a map given a 2d vector.
	 */
	void DrawMap(vector<vector<int>> map, ALLEGRO_BITMAP* tileset, int divIndex[], int modIndex[]);

	/**
	 * main loop for program.
	 */
	void MainLoop();
	void MainLoopIteration();

	/**
	 * destroy allegro objects.
	 */
	void Destroy();
};

#endif // !Game_h


