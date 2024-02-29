#include "Config.h"

//AColor
//-------------------------------------------------------------------------------------------------------------------------
AColor::AColor(unsigned char r, unsigned char g, unsigned char b)
: R(r), G(g), B(b)
{
}
//-------------------------------------------------------------------------------------------------------------------------




//AsConfig
int AsConfig::Current_Timer_Tick = 0;
bool AsConfig::Level_Has_Floor = true;

const AColor AsConfig::BG_Color(9, 25, 43);
const AColor AsConfig::Red_Brick_Color(209, 51, 88);
const AColor AsConfig::Green_Brick_Color(0, 240, 181);

HPEN AsConfig::BG_Pen;
HBRUSH AsConfig::BG_Brush;
HWND AsConfig::Hwnd;

const double AsConfig::Moving_Step_Size = 1.0 / AsConfig::Global_Scale;
//-------------------------------------------------------------------------------------------------------------------------
void AsConfig::Create_Pen_Brush(unsigned char r, unsigned char g, unsigned char b, HPEN& pen, HBRUSH& brush)
{// Создания пары кисти и карандаша для определённого цвета
   pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
   brush = CreateSolidBrush(RGB(r, g, b));
}
//-------------------------------------------------------------------------------------------------------------------------
void AsConfig::Create_Pen_Brush(const AColor &color, HPEN& pen, HBRUSH& brush)
{// Перегрузка метода для создания пары кисти и карандаша
   pen = CreatePen(PS_SOLID, 0, RGB(color.R, color.G, color.B));
   brush = CreateSolidBrush(RGB(color.R, color.G, color.B));
}
//-------------------------------------------------------------------------------------------------------------------------
void AsConfig::Setup_Color()
{// Установка цвета фона
   Create_Pen_Brush(AsConfig::BG_Color, BG_Pen, BG_Brush);
}
//-------------------------------------------------------------------------------------------------------------------------
int AsConfig::Rand(int range)
{// Устанавлывает границу для рандомизации числа 
   return (rand() * range) / RAND_MAX;
}

