#pragma once

#include "Config.h"
#include "Level.h"
//ABall
//------------------------------------------------------------------------------------------------------------
class ABall
{
public:
	ABall();

	void Init();
	void Draw(HDC hdc, RECT& paint_area);
	void Move(ALevel* level, int platform_x_pos, int platform_width);

private:
	double Ball_Direction;
	int Ball_X_Pos, Ball_Y_Pos;
	double Ball_Speed;

	HPEN Ball_Pen;
	HBRUSH Ball_Brush;
	RECT Ball_Rect, Prev_Ball_Rect;
};
//------------------------------------------------------------------------------------------------------------