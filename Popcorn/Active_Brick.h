#pragma once

#include "Config.h"

//------------------------------------------------------------------------------------------------------------
enum EBrick_Type
{
	EBT_None,

	EBT_Red,
	EBT_Green,
	EBT_Unbreakable,
	EBT_Multihit_1,
	EBT_Multihit_2,
	EBT_Multihit_3,
	EBT_Multihit_4,
	EBT_Parachute,
	EBT_Teleport,
	EBT_Ad,
};
//------------------------------------------------------------------------------------------------------------

//AActive_Brick
//------------------------------------------------------------------------------------------------------------
class AActive_Brick
{
public:
	AActive_Brick(EBrick_Type brick_type, int level_x, int level_y);
	void Draw(HDC hdc, RECT& paint_area);
	void Act();
	bool Is_Finished();
	
	static void Setup_Colors();
	static unsigned char Get_Fading_Channel(unsigned char color, unsigned char bg_color, int step);
	static void Get_Fading_Color(const AColor& color, int step, HPEN& pen, HBRUSH& brush);

	int Fade_Step;
	EBrick_Type Brick_Type;
	RECT Brick_Rect;

	static const int Max_Fade_Step = 80;
	static HPEN Fading_Green_Brick_Pens[Max_Fade_Step];
	static HBRUSH Fading_Green_Brick_Brushes[Max_Fade_Step];
	static HPEN Fading_Red_Brick_Pens[Max_Fade_Step];
	static HBRUSH Fading_Red_Brick_Brushes[Max_Fade_Step];
};
//------------------------------------------------------------------------------------------------------------