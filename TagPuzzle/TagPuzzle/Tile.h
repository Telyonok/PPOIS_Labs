#pragma once
class Tile
{
public:
	Tile(int value, int x, int y);
	char GetValue();
	bool GheckPlacement(int x, int y);
private:
	char value;
	int correctX;
	int correctY;
};

