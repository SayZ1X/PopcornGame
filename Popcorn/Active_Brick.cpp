﻿#include "Active_Brick.h"

//AActive_Brick
//-------------------------------------------------------------------------------------------------------------------------
HPEN  AActive_Brick::Fading_Green_Brick_Pens[Max_Fade_Step];
HBRUSH  AActive_Brick::Fading_Green_Brick_Brushes[Max_Fade_Step];
HPEN  AActive_Brick::Fading_Red_Brick_Pens[Max_Fade_Step];
HBRUSH  AActive_Brick::Fading_Red_Brick_Brushes[Max_Fade_Step];
//-------------------------------------------------------------------------------------------------------------------------
AActive_Brick::AActive_Brick(EBrick_Type brick_type, int level_x, int level_y)
   :Fade_Step(0), Brick_Type(brick_type), Brick_Rect{}
{
   Brick_Rect.left = (AsConfig::Level_X_Offset + level_x * AsConfig::Cell_Width) * AsConfig::Global_Scale;
   Brick_Rect.top = (AsConfig::Level_Y_Offset + level_y * AsConfig::Cell_Height) * AsConfig::Global_Scale;
   Brick_Rect.right = Brick_Rect.left + AsConfig::Brick_Width * AsConfig::Global_Scale;
   Brick_Rect.bottom = Brick_Rect.top + AsConfig::Brick_Height * AsConfig::Global_Scale;
}
//-------------------------------------------------------------------------------------------------------------------------
void AActive_Brick::Draw(HDC hdc, RECT& paint_area)
{// Отрисовка карпича
   switch(Brick_Type)
   {
   case EBT_Green:
      SelectObject(hdc, Fading_Green_Brick_Pens[Fade_Step]);
      SelectObject(hdc, Fading_Green_Brick_Brushes[Fade_Step]);
      break;

   case EBT_Red:
      SelectObject(hdc, Fading_Red_Brick_Pens[Fade_Step]);
      SelectObject(hdc, Fading_Red_Brick_Brushes[Fade_Step]);
      break;
   }

   RoundRect(hdc, Brick_Rect.left, Brick_Rect.top, Brick_Rect.right, Brick_Rect.bottom, 2 * AsConfig::Global_Scale, 2 * AsConfig::Global_Scale);
}
//-------------------------------------------------------------------------------------------------------------------------
void AActive_Brick::Act()
{// Установка активного кирпича
   if (Fade_Step < Max_Fade_Step - 1)
   {
      ++Fade_Step;
      InvalidateRect(AsConfig::Hwnd, &Brick_Rect, FALSE);
   }
}
//-------------------------------------------------------------------------------------------------------------------------
bool AActive_Brick::Is_Finished()
{
   if (Fade_Step >= Max_Fade_Step - 1)
      return true;
   else
      return false;
}
//-------------------------------------------------------------------------------------------------------------------------
void AActive_Brick::Setup_Colors()
{// заполнения масива цветами для угасания кирпича
   for (int i = 0; i < Max_Fade_Step; i++)
   {
      Get_Fading_Color(AsConfig::Green_Brick_Color, i, Fading_Green_Brick_Pens[i], Fading_Green_Brick_Brushes[i]);
      Get_Fading_Color(AsConfig::Red_Brick_Color, i, Fading_Red_Brick_Pens[i], Fading_Red_Brick_Brushes[i]);
   }
}
//-------------------------------------------------------------------------------------------------------------------------
unsigned char AActive_Brick::Get_Fading_Channel(unsigned char color, unsigned char bg_color, int step)
{// Вычисляем промежуточные цвета определённого канала RGB для угасания кирпича
   return color - step * (color - bg_color) / (Max_Fade_Step - 1);
}
//-------------------------------------------------------------------------------------------------------------------------
void AActive_Brick::Get_Fading_Color(const AColor &color, int step, HPEN &pen, HBRUSH &brush)
{// Вычисляем промежуточные цвета для угасания кирпича
   unsigned char r, g, b;

   r = Get_Fading_Channel(color.R, AsConfig::BG_Color.R, step);
   g = Get_Fading_Channel(color.G, AsConfig::BG_Color.G, step);
   b = Get_Fading_Channel(color.B, AsConfig::BG_Color.B, step);

   AsConfig::Create_Pen_Brush(r, g, b, pen, brush);
}
