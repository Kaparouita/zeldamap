#include "Grid.h"

void Grid::ComputeTileGridBlock1() {

}

void setGridMap(TileMap map) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++)
			(map[i][j] < 0 || map[i][j] == 61) ? grid[i][j] = false : grid[i][j] = true;
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
bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags) // i.e. checks if flags set
{
	return GetGridTile(m, row, col) & flags != 0;
}


int main() {
	app::App app;
	app.Initialise();
	app.Load();

	Grid grid1;

	setGridMap(app.GetGame().map2);

	cout << GetGridTile(&grid, 5, 10);

}
