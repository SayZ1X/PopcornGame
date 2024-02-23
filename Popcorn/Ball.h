#pragma once

#include "Config.h"
#include "Level.h"

enum EBall_State
{
	EBS_Normal,
	EBS_Lost,
	EBS_On_Platform
};

//ABall
//------------------------------------------------------------------------------------------------------------
class ABall
{
public:
	ABall();

	void Init();
	void Draw(HDC hdc, RECT& paint_area);
	void Move(ALevel* level, int platform_x_pos, int platform_width);
	EBall_State Get_State();
	void Set_State(EBall_State new_state, int x_pos);

private:
	void Redraw_Ball();

	EBall_State Ball_State;

	double Ball_Direction;
	double Ball_X_Pos, Ball_Y_Pos;
	double Ball_Speed;

	HPEN Ball_Pen;
	HBRUSH Ball_Brush;
	RECT Ball_Rect, Prev_Ball_Rect;

	static const double Start_Ball_Y_Pos;
};
//------------------------------------------------------------------------------------------------------------