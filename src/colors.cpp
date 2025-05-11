#include "../include/colors.h"

Color darkGrey = {26, 31, 40, 255};
Color green = {47, 230, 23, 255};
Color red = {232, 18, 18, 255};
Color orange = {226, 116, 17, 255};
Color yellow = {237, 234, 4, 255};
Color purple = {166, 0, 247, 255};
Color cyan = {21, 204, 209, 255};
Color blue = {13, 64, 216, 255};
Color lightBlue = {59, 85, 162, 255};
Color darkBlue = {44, 44, 127, 255};

std::vector<Color> GetCellColors()
{
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}

void ChangeColors(unsigned char value){
    green=IncreaseColorValues(green,value);
    red=IncreaseColorValues(red,value);
    orange=IncreaseColorValues(orange,value);
    yellow=IncreaseColorValues(yellow,value);
    purple=IncreaseColorValues(purple,value);
    cyan=IncreaseColorValues(cyan,value);
    blue=IncreaseColorValues(blue,value);
}

Color IncreaseColorValues(Color color, unsigned char value){
    unsigned char r = color.r;
    unsigned char g = color.g;
    unsigned char b= color.b;
    r+=value;
    g+=value;
    b+=value;
    if(r>255){
        r=0;
    }
    if(g>255){
        g=0;
    }
    if(b>255){
        b=0;
    }
    return {r,g,b,255};
}