﻿#include "Border.h"

//AsBorder
//-------------------------------------------------------------------------------------------------------------------------
AsBorder::AsBorder()
   :Border_Blue_Pen(0), Border_White_Pen(0), Border_Blue_Brush(0), Border_White_Brush(0)
{
}
//-------------------------------------------------------------------------------------------------------------------------
void AsBorder::Init()
{// Инициализация компонентов для создания рамки уровня
   AsConfig::Create_Pen_Brush(69, 238, 255, Border_Blue_Pen, Border_Blue_Brush);
   AsConfig::Create_Pen_Brush(255, 255, 255, Border_White_Pen, Border_White_Brush);
}
//-------------------------------------------------------------------------------------------------------------------------
void AsBorder::Draw(HDC hdc, RECT& paint_area)
{// Рисуем рамку уровня
   int i;

   // 1.Рисуем левую раку
   for (i = 0; i < 50; i++)
      Draw_Element(hdc, 2, 1 + i * 4, false);

   // 2.Рисуем правую раку
   for (i = 0; i < 50; i++)
      Draw_Element(hdc, 201, 1 + i * 4, false);

   // 3.Рисуем верхнюю раку
   for (i = 0; i < 50; i++)
      Draw_Element(hdc, 3 + i * 4, 0, true);
}
//-------------------------------------------------------------------------------------------------------------------------
void AsBorder::Draw_Element(HDC hdc, int x, int y, bool top_border)
{// Рисуем отдельный повторяющийся элемент рамки уровня
   //1. Рисуем основу элемента  рамки
   SelectObject(hdc, Border_Blue_Pen);
   SelectObject(hdc, Border_Blue_Brush);

   if (top_border)
      Rectangle(hdc, x * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale, (y + 4) * AsConfig::Global_Scale);
   else
      Rectangle(hdc, (x + 1) * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale, (y + 4) * AsConfig::Global_Scale);

   //2. Рисуем кромку для элемента  рамки
   SelectObject(hdc, Border_White_Pen);
   SelectObject(hdc, Border_White_Brush);

   if (top_border)
      Rectangle(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale);
   else
      Rectangle(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 1) * AsConfig::Global_Scale, (y + 4) * AsConfig::Global_Scale);

   //3. Рисуем перфорацию для элемента  рамки
   SelectObject(hdc, AsConfig::BG_Pen);
   SelectObject(hdc, AsConfig::BG_Brush);

   if (top_border)
      Rectangle(hdc, (x + 2) * AsConfig::Global_Scale, (y + 2) * AsConfig::Global_Scale, (x + 3) * AsConfig::Global_Scale, (y + 3) * AsConfig::Global_Scale);
   else
      Rectangle(hdc, (x + 2) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 3) * AsConfig::Global_Scale, (y + 2) * AsConfig::Global_Scale);

}