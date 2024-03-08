﻿#include "Engine.h"

//AsEngine
//-------------------------------------------------------------------------------------------------------------------------
AsEngine::AsEngine()
: Game_State(EGS_Play_Level)
{
};
//-------------------------------------------------------------------------------------------------------------------------
void AsEngine::Init_Engine(HWND hwnd)
{// Настройка игры при старте
   
   SYSTEMTIME sys_time;
   FILETIME file_time;

   GetSystemTime(&sys_time);
   SystemTimeToFileTime(&sys_time, &file_time);

   srand(file_time.dwLowDateTime);

   AsConfig::Hwnd = hwnd;

   AsConfig::Setup_Color();
   AActive_Brick::Setup_Colors();


   Border.Init();
   Level.Init();
   Platform.Init();
   Ball.Init();

   ABall::Add_Hit_Checker(&Border);
   ABall::Add_Hit_Checker(&Level);
   ABall::Add_Hit_Checker(&Platform);

   Level.Set_Current_Level(ALevel::Level_01);

   Ball.Set_State(EBS_Normal, Platform.X_Pos + (Platform.Width / 2));

   Platform.Set_State(EPS_Normal);

   Platform.Redraw_Platform();
   
   SetTimer(AsConfig::Hwnd, Timer_ID, 1000 / AsConfig::FPS, 0);
}
//-------------------------------------------------------------------------------------------------------------------------
void AsEngine::Draw_Frame(HDC hdc, RECT &paint_area)
{// Отрисовка экрана игры
   SetGraphicsMode(hdc, GM_ADVANCED);

   Level.Draw(hdc, paint_area);
   Border.Draw(hdc, paint_area);
   Platform.Draw(hdc, paint_area);
   Ball.Draw(hdc, paint_area);
}
//-------------------------------------------------------------------------------------------------------------------------
int AsEngine::On_Key_Down(EKey_Type key_type)
{// Обработка клавиш управления
   int max_x_pos = AsConfig::Max_X_Pos - Platform.Width + 1;

   switch (key_type)
   {
   case EKT_Left:
      Platform.X_Pos -= Platform.X_Step;

      if (Platform.X_Pos < AsConfig::Border_X_Offset)
         Platform.X_Pos = AsConfig::Border_X_Offset;

      Platform.Redraw_Platform();
      break;

   case EKT_Right:
      Platform.X_Pos += Platform.X_Step;

      if (Platform.X_Pos > max_x_pos)
         Platform.X_Pos = max_x_pos;

      Platform.Redraw_Platform();
      break;


   case EKT_Space:
      if(Platform.Get_State() == EPS_Ready)
      {
         Ball.Set_State(EBS_Normal, Platform.X_Pos + (Platform.Width / 2));
         Platform.Set_State(EPS_Normal);
      }
      break;

   }
   return 0;
}
//-------------------------------------------------------------------------------------------------------------------------
int AsEngine::On_Timer()
{// Установка таймера для генерации кадров анимации
   ++AsConfig::Current_Timer_Tick;

   switch(Game_State)
   {
   case EGS_Test_Ball:
      Ball.Set_For_Test();
      Game_State = EGS_Play_Level;
      break;

   case EGS_Play_Level:
      Ball.Move();
      if(Ball.Get_State() == EBS_Lost)
      {
         Game_State = EGS_Lost_Ball;
         Platform.Set_State(EPS_Meltdown);
      }

      if(Ball.Is_Test_Finished() )
         Game_State = EGS_Test_Ball;
      break;

   case EGS_Lost_Ball:
      if(Platform.Get_State() == EPS_Missing)
      {
         Game_State = EGS_Restart_Level;
         Platform.Set_State(EPS_Roll_In);
      }
      break;

   case EGS_Restart_Level:
      if(Platform.Get_State() == EPS_Ready)
      {
         Game_State = EGS_Play_Level;
         Ball.Set_State(EBS_On_Platform, Platform.X_Pos + (Platform.Width / 2));
      }
      break;
   }

   Level.Act();

   //if(AsConfig::Current_Timer_Tick % 3 == 0)
   Platform.Act();

   return 0;
}


