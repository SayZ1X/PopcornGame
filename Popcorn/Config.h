﻿#pragma once

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

//AColor
//-------------------------------------------------------------------------------------------------------------------------
class AColor
{
public:
	AColor(unsigned char r, unsigned char g, unsigned char b);

	int Get_RGB() const;

	unsigned char R, G, B;
};
//-------------------------------------------------------------------------------------------------------------------------




//AsConfig
//-------------------------------------------------------------------------------------------------------------------------
class AsConfig
{
public:
	static void Create_Pen_Brush(unsigned char r, unsigned char g, unsigned char b, HPEN& pen, HBRUSH& brush);
	static void Create_Pen_Brush(const AColor& color, HPEN& pen, HBRUSH& brush);
	static void Setup_Color();
	static int Rand(int range);

	static const AColor BG_Color, Red_Brick_Color, Green_Brick_Color;

	static int Current_Timer_Tick;
	static bool Level_Has_Floor;

	static HPEN BG_Pen;
	static HBRUSH BG_Brush;
	static HWND Hwnd;

	static HPEN Letter_Pen, Brick_Red_Pen, Brick_Green_Pen;
	static HBRUSH Brick_Red_Brush, Brick_Green_Brush;

	static const double Moving_Step_Size;

	static const int Global_Scale = 3;
	static const int Border_X_Offset = 6;
	static const int Border_Y_Offset = 4;
	static const int Level_Width = 12; //Ширина уровня в ячейках
	static const int Level_Height = 14; //Высота уровня в ячейках 
	static const int Level_X_Offset = 8;
	static const int Level_Y_Offset = 6;
	static const int Brick_Width = 15;
	static const int Brick_Height = 7;
	static const int Cell_Width = 16;
	static const int Cell_Height = 8;
	static const int Max_X_Pos = Level_X_Offset + Cell_Width * Level_Width;
	static const int Max_Y_Pos = 199;
	static const int Platform_Y_Pos = 185;
	static const int FPS = 20;
	static const int Max_Active_Bricks_Count = 10;
	static const int Max_Falling_Letters_Count = 10;
	static const int Hits_Per_Letter = 3; //шанс на выпадение буквы = 1.0 / Hit_Per_Letter
};
//-------------------------------------------------------------------------------------------------------------------------