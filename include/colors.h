#pragma once
#include<raylib.h>
#include<vector>

extern Color darkGrey;
extern Color green;
extern Color red;
extern Color orange;
extern Color yellow;
extern Color purple;
extern Color cyan;
extern Color blue;
extern Color lightBlue;
extern Color darkBlue;


std::vector<Color> GetCellColors();
void ChangeColors(unsigned char value);
Color IncreaseColorValues(Color color, unsigned char value);