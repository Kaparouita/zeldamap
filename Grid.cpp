#include "Grid.h"

void SetGridTile(GridMap* m, int col, int row, GridIndex index);
void set4Grids(GridMap* m, int col, int row, int index);

void Grid::ComputeTileGridBlock1() {

}

/**
 * init all as EMPTY.
 *
 * \param m
 */
void initGridMap(GridMap* m) {
	for (int i = 0; i < GRID_MAX_WIDTH; i++) {
		for (int j = 0; j < GRID_MAX_HEIGHT; j++)
			grid[i][j] = GRID_EMPTY_TILE;
	}
}
/**
 * set grids as walkable or not.
 *
 * \param map
 */
void setGridMap(TileMap map) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++)
			(map[i][j] < 0 || map[i][j] == 61) ? set4Grids(&grid, i, j, -1) : set4Grids(&grid, i, j, 1);
	}
}
void set4Grids(GridMap* m, int col, int row, int index) {
	int gridCol = ((col + 1) * 2) - 1;
	int gridRow = ((row + 1) * 2) - 1;

	SetGridTile(m, gridCol, gridRow - 1, index);
	SetGridTile(m, gridCol - 1, gridRow, index);
	SetGridTile(m, gridCol - 1, gridRow - 1, index);
	SetGridTile(m, gridCol, gridRow, index);

}
void printGridMapValues(GridMap grid) {
	for (int i = 0; i < GRID_MAX_WIDTH; i++) {
		for (int j = 0; j < GRID_MAX_HEIGHT; j++)
		{
			if (grid[i][j] != GRID_EMPTY_TILE)
				cout << grid[i][j] << " ";
		}
		cout << "\n";
	}

}

void SetGridTile(GridMap* m, int col, int row, GridIndex index)
{
	(*m)[row][col] = index;
}
GridIndex GetGridTile(const GridMap* m, int col, int row)
{
	return (*m)[row][col];
}

void SetSolidGridTile(GridMap* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_SOLID_TILE);
}
void SetEmptyGridTile(GridMap* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_EMPTY_TILE);
}
void SetGridTileFlags(GridMap* m, Dim col, Dim row, GridIndex flags)
{
	SetGridTile(m, col, row, flags);
}
void SetGridTileTopSolidOnly(GridMap* m, Dim col, Dim row)
{
	SetGridTileFlags(m, row, col, GRID_TOP_SOLID_MASK);
}
bool Grid::CanPassGridTile(GridMap* m, Dim col, Dim row) // i.e. checks if flags set
{
	int index = GetGridTile(m, row, col);
	if (index == GRID_SOLID_TILE || index == GRID_EMPTY_TILE)
		return  false;
	return true;
}


int main() {

	app::App app;
	app.Initialise();
	app.Load();

	//initGridMap(&grid);
	setGridMap(app.GetGame().map2);
	printGridMapValues(grid);
	app.Main();

}
