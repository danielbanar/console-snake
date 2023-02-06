#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <thread>
#include "time.h"

using namespace std::literals::chrono_literals;

constexpr int mapSize = 16;
int* map = new int[mapSize * mapSize];

enum Direction
{
	None, Right, Up, Left, Down
};

struct Coord
{
	static int mapSize;
	int x = 0, y = 0;
	Coord() {}
	Coord(const int& X, const int& Y) : x(X), y(Y) {}
	bool operator==(const Coord& other) const
	{
		return x == other.x && y == other.y;
	}
};
int GetIndex(const int& X, const int& Y)
{
	return mapSize * Y + X;
}
int GetIndex(const Coord& vec)
{
	return mapSize * vec.y + vec.x;
}
Coord GetPos(const int& index)
{
	return {index % mapSize, index / mapSize};
}

int UpIndex(const Coord& vec)
{
	return GetIndex(vec.x, vec.y - 1);
}
int UpIndex(const int& index)
{
	return UpIndex(GetPos(index));
}
Coord UpCoord(const Coord& vec)
{
	return GetPos(UpIndex(vec));
}
Coord UpCoord(const int& index)
{
	return UpCoord(GetPos(index));
}

int DownIndex(const Coord& vec)
{
	return GetIndex(vec.x, vec.y + 1);
}
int DownIndex(const int& index)
{
	return DownIndex(GetPos(index));
}
Coord DownCoord(const Coord& vec)
{
	return GetPos(DownIndex(vec));
}
Coord DownCoord(const int& index)
{
	return DownCoord(GetPos(index));
}

int LeftIndex(const Coord& vec)
{
	return GetIndex(vec.x - 1, vec.y);
}
int LeftIndex(const int& index)
{
	return LeftIndex(GetPos(index));
}
Coord LeftCoord(const Coord& vec)
{
	return GetPos(LeftIndex(vec));
}
Coord LeftCoord(const int& index)
{
	return LeftCoord(GetPos(index));
}

int RightIndex(const Coord& vec)
{
	return GetIndex(vec.x + 1, vec.y);
}
int RightIndex(const int& index)
{
	return RightIndex(GetPos(index));
}
Coord RightCoord(const Coord& vec)
{
	return GetPos(RightIndex(vec));
}
Coord RightCoord(const int& index)
{
	return RightCoord(GetPos(index));
}