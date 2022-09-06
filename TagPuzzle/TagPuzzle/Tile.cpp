#include "Tile.h"

Tile::Tile(int value, int x, int y)
{
    this->value = (char) value;
    correctX = x;
    correctY = y;
}

char Tile::GetValue()
{
    return value;
}

bool Tile::CheckPlacement(int x, int y)
{
    return (x == correctX && y == correctY);
}
