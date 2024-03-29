#pragma once
#include "WIDTHHEIGHT.h"

class MapManager
{
public:
	~MapManager() {}

	static MapManager* Instance()
	{
		if (s_pInstance == nullptr) s_pInstance = new MapManager();
		return s_pInstance;
	}

	void SetMap(int map_x, int map_y, int value);
	void CreateMap(int x, int y);
	bool IsTileThere(int x, int y);

	void Clean();
private:
	MapManager() {}

	// LoadFiles에서 불러온 맵 지도
	int loadedTileMap[MAP_MAX_HEIGHT][MAP_MAX_WIDTH] = { 0 };
	static MapManager* s_pInstance;
};
typedef MapManager TheMap;