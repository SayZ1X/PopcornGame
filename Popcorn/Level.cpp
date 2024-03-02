#include "Level.h"

char ALevel::Level_01[AsConfig::Level_Height][AsConfig::Level_Width] =
{// Масив блоков для уровня
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char ALevel::Test_Level[AsConfig::Level_Height][AsConfig::Level_Width] =
{// Масив блоков для уровня
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


//ALevel
//-------------------------------------------------------------------------------------------------------------------------
ALevel::ALevel()
   : Letter_Pen(0), Brick_Red_Pen(0), Brick_Green_Pen(0), Brick_Red_Brush(0), Brick_Green_Brush(0), Level_Rect{}, Active_Bricks_Count(0)
{
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Init()
{// Инициализация уровня 
   Letter_Pen = CreatePen(PS_SOLID, AsConfig::Global_Scale, RGB(255, 255, 255));

   AsConfig::Create_Pen_Brush(AsConfig::Red_Brick_Color, Brick_Red_Pen, Brick_Red_Brush);
   AsConfig::Create_Pen_Brush(AsConfig::Green_Brick_Color, Brick_Green_Pen, Brick_Green_Brush);

   Level_Rect.left = AsConfig::Level_X_Offset * AsConfig::Global_Scale;
   Level_Rect.top = AsConfig::Level_Y_Offset * AsConfig::Global_Scale;
   Level_Rect.right = Level_Rect.left + AsConfig::Cell_Width * AsConfig::Level_Width * AsConfig::Global_Scale;
   Level_Rect.bottom = Level_Rect.top + AsConfig::Cell_Height * AsConfig::Level_Height * AsConfig::Global_Scale;

   memset(Current_Level, 0, sizeof(Current_Level) );
   memset(Active_Bricks, 0, sizeof(Active_Bricks) );
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Set_Current_Level(char level[AsConfig::Level_Height][AsConfig::Level_Width])
{
   memcpy(Current_Level, level, sizeof(Current_Level));
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Draw(HDC hdc, RECT& paint_area)
{// Вывод всех керпичей уровня
   int i;
   RECT intersection_rect;

   if (!IntersectRect(&intersection_rect, &paint_area, &Level_Rect))
      return;

   for (int i = 0; i < AsConfig::Level_Height; i++)
      for (int j = 0; j < AsConfig::Level_Width; j++)
         Draw_Brick(hdc, AsConfig::Level_X_Offset + j * AsConfig::Cell_Width, AsConfig::Level_Y_Offset + i * AsConfig::Cell_Height, (EBrick_Type)Current_Level[i][j]);

   for(i = 0; i < Active_Bricks_Count; i++)
   {
      if(Active_Bricks[i] != 0)
         Active_Bricks[i]->Draw(hdc, paint_area);
   }
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Act()
{// смена состояния кирпича на активный у всех активных кирпичей, которые у нас есть
   int i;

   for (i = 0; i < Active_Bricks_Count; i++)
   {
      if (Active_Bricks[i] != 0)
      {
         Active_Bricks[i]->Act();

         if(Active_Bricks[i]->Is_Finished() )
         {
            delete Active_Bricks[i];
            Active_Bricks[i] = 0;
         }
      }
   }
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Add_Active_Brick(int brick_x, int brick_y)
{// Добавление активного кирпича в который ударил мячик в масив для активных кирпичей
   int i;
   EBrick_Type brick_type;
   AActive_Brick* active_brick;

   if(Active_Bricks_Count >= AsConfig::Max_Active_Bricks_Count)
      return; // Активных кирпичей слишком много!

   brick_type = (EBrick_Type)Current_Level[brick_y][brick_x];

   switch (brick_type)
   {
   case EBT_None:
      return;

   case EBT_Red:
   case EBT_Green:
      active_brick = new AActive_Brick(brick_type, brick_x, brick_y);
      break;

   default:
      return;
   }

   // Добавляем новый активный кирпич на первое свободное место   
   for (i = 0; i < AsConfig::Max_Active_Bricks_Count; i++)
   {
      if (Active_Bricks[i] == 0)
      {
         Active_Bricks[i] = active_brick;
         ++Active_Bricks_Count;
         break;
      }
   }
}
//-------------------------------------------------------------------------------------------------------------------------
bool ALevel::Check_Vertical_Hit(double next_x_pos, double next_y_pos, int level_x, int level_y, ABall* ball, double &reflection_pos)
{// Проверяем попадание мячика по вертикали

   if (ball->Is_Moving_Up() )
   {// Проверяем попадание в нижнюю грань
      if (Hit_Circle_On_Line(next_y_pos - Current_Brick_Low_Y, next_x_pos, Current_Brick_Left_X, Current_Brick_Right_X, ball->Radius, reflection_pos))
      {
         // Проверяем возможность отскочить от нижней грани
         if (level_y < AsConfig::Level_Height - 1 && Current_Level[level_y + 1][level_x] == 0)
            return true;
         else
            return false;
      }
   }
   else
   {// Проверяем попадание в верхнюю грань
      if (Hit_Circle_On_Line(next_y_pos - Current_Brick_Top_Y, next_x_pos, Current_Brick_Left_X, Current_Brick_Right_X, ball->Radius, reflection_pos))
      {
         // Проверяем возможность отскочить от верхней грани
         if (level_y > 0 && Current_Level[level_y - 1][level_x] == 0)
            return true;
         else
            return false;
      }
   }

   return false;
}
//-------------------------------------------------------------------------------------------------------------------------
bool ALevel::Check_Horizontal_Hit(double next_x_pos, double next_y_pos, int level_x, int level_y, ABall* ball, double& reflection_pos)
{// Проверяем попадание мячика по горизонтали

   if (!ball->Is_Moving_Left() )
   {// Проверяем попадание в левую грань
      if (Hit_Circle_On_Line(Current_Brick_Left_X - next_x_pos, next_y_pos, Current_Brick_Top_Y, Current_Brick_Low_Y, ball->Radius, reflection_pos))
      {
         // Проверяем возможность отскочить от левой грани
         if (level_x > 0 && Current_Level[level_y][level_x - 1] == 0)
            return true;
         else
            return false;
      }
   }
   else
   {// Проверяем попадание в правую грань
      if (Hit_Circle_On_Line(Current_Brick_Right_X - next_x_pos, next_y_pos, Current_Brick_Top_Y, Current_Brick_Low_Y, ball->Radius, reflection_pos))
      {
         // Проверяем возможность отскочить от правой грани
         if (level_x < AsConfig::Level_Width - 1 && Current_Level[level_y][level_x + 1] == 0)
            return true;
         else
            return false;
      }
   }

   return false;
}
//-------------------------------------------------------------------------------------------------------------------------
bool ALevel::Check_Hit(double next_x_pos, double next_y_pos, ABall* ball)
{// Корректируем позицию при отражении от кирпичей
   int i, j;
   double direction;
   double min_ball_x, max_ball_x;
   double min_ball_y, max_ball_y;
   int min_level_x, max_level_x;
   int min_level_y, max_level_y;
   bool got_horizontal_hit, got_vertical_hit;
   double horizontal_reflection_pos, vertical_reflection_pos;

   if(next_y_pos + ball->Radius > AsConfig::Level_Y_Offset + (AsConfig::Level_Height - 1) * AsConfig::Cell_Height + AsConfig::Brick_Height)
      return false;

   direction = ball->Get_Direction();

   min_ball_x = next_x_pos - ball->Radius;
   max_ball_x = next_x_pos + ball->Radius;
   min_ball_y = next_y_pos - ball->Radius;
   max_ball_y = next_y_pos + ball->Radius;

   min_level_x = (int)( (min_ball_x - AsConfig::Level_X_Offset) / (double)AsConfig::Cell_Width);
   max_level_x = (int)( (max_ball_x - AsConfig::Level_X_Offset) / (double)AsConfig::Cell_Width);
   min_level_y = (int)( (min_ball_y - AsConfig::Level_Y_Offset) / (double)AsConfig::Cell_Height);
   max_level_y = (int)( (max_ball_y - AsConfig::Level_Y_Offset) / (double)AsConfig::Cell_Height);

   for (i = max_level_y; i >= min_level_y; i--)
   {
      Current_Brick_Top_Y = AsConfig::Level_Y_Offset + i * AsConfig::Cell_Height;
      Current_Brick_Low_Y = AsConfig::Level_Y_Offset + i * AsConfig::Cell_Height + AsConfig::Brick_Height;

      for (j = min_level_x; j <= max_level_x; j++)
      {
         if (Current_Level[i][j] == 0)
            continue;

         Current_Brick_Left_X = AsConfig::Level_X_Offset + j * AsConfig::Cell_Width;
         Current_Brick_Right_X = Current_Brick_Left_X + AsConfig::Brick_Width;

         got_horizontal_hit = Check_Horizontal_Hit(next_x_pos, next_y_pos, j, i, ball, horizontal_reflection_pos);
         got_vertical_hit = Check_Vertical_Hit(next_x_pos, next_y_pos, j, i, ball, vertical_reflection_pos);

         if(got_horizontal_hit && got_vertical_hit)
         {
            if(vertical_reflection_pos < horizontal_reflection_pos)
               ball->Reflect(true);
            else
               ball->Reflect(false);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Add_Active_Brick(j, i);


            return true;
         }
         else if(got_horizontal_hit)
         {
            ball->Reflect(false);
            Add_Active_Brick(j, i);
            return true;
         }
         else if(got_vertical_hit)
         {
            ball->Reflect(true);
            Add_Active_Brick(j, i);
            return true;
         }
      }
   }
   return false;
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Draw_Brick(HDC hdc, int x, int y, EBrick_Type brick_type)
{// Отрисовка "кирпича"

   HPEN pen;
   HBRUSH brush;

   switch (brick_type)
   {
   case EBT_None:
      return;

   case EBT_Red:
      pen = Brick_Red_Pen;
      brush = Brick_Red_Brush;
      break;

   case EBT_Green:
      pen = Brick_Green_Pen;
      brush = Brick_Green_Brush;
      break;

   default:
      return;
   }

   SelectObject(hdc, pen);
   SelectObject(hdc, brush);

   RoundRect(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + AsConfig::Brick_Width) * AsConfig::Global_Scale, (y + AsConfig::Brick_Height) * AsConfig::Global_Scale, 2 * AsConfig::Global_Scale, 2 * AsConfig::Global_Scale);
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Set_Brick_Letter_Colors(bool is_switch_color, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush)
{// Установка цвета для лицевой стороны падающего кирпича с буквой
   if (is_switch_color)
   {
      front_pen = Brick_Green_Pen;
      front_brush = Brick_Green_Brush;

      back_pen = Brick_Red_Pen;
      back_brush = Brick_Red_Brush;
   }
   else
   {
      front_pen = Brick_Red_Pen;
      front_brush = Brick_Red_Brush;

      back_pen = Brick_Green_Pen;
      back_brush = Brick_Green_Brush;
   }
}
//-------------------------------------------------------------------------------------------------------------------------
void ALevel::Draw_Brick_Letter(HDC hdc, int x, int y, EBrick_Type brick_type, ELetter_Type letter_type, int rotation_step)
{// Вывод падающей буквы

   bool switch_color;
   double offset;
   double rotation_angle; // преобразование шага в угол поворота
   int brick_half_height = AsConfig::Brick_Height * AsConfig::Global_Scale / 2;
   int brick_half_offset;
   HPEN front_pen, back_pen;
   HBRUSH front_brush, back_brush;
   XFORM xform, old_xform;

   if (!(brick_type == EBT_Green || brick_type == EBT_Red))
      return;// кирпичики с буковкой могут быть только таких цветов;

   // Корректируем шаг вращения и угол поворота
   rotation_step = rotation_step % 16;

   if (rotation_step < 8)
      rotation_angle = 2.0 * M_PI / 16.0 * (double)rotation_step;
   else
      rotation_angle = 2.0 * M_PI / 16.0 * (double)(8L - (long long)rotation_step);

   if (rotation_step > 4 && rotation_step <= 12)
   {
      if (brick_type == EBT_Green)
         switch_color = true;
      else
         switch_color = false;
   }
   else
   {
      if (brick_type == EBT_Red)
         switch_color = true;
      else
         switch_color = false;
   }

   Set_Brick_Letter_Colors(switch_color, front_pen, front_brush, back_pen, back_brush);

   if (rotation_step == 4 || rotation_step == 12)
   {
      //Выводим фон
      SelectObject(hdc, back_pen);
      SelectObject(hdc, back_brush);

      Rectangle(hdc, x, y + brick_half_height - AsConfig::Global_Scale, x + AsConfig::Brick_Width * AsConfig::Global_Scale, y + brick_half_height);

      //Выводим передний план
      SelectObject(hdc, front_pen);
      SelectObject(hdc, front_brush);

      Rectangle(hdc, x, y + brick_half_height, x + AsConfig::Brick_Width * AsConfig::Global_Scale, y + brick_half_height + AsConfig::Global_Scale - 1);
   }
   else
   {
      SetGraphicsMode(hdc, GM_ADVANCED);

      // Настраиваем матрицу "переворота" буквы
      xform.eM11 = 1.0f;
      xform.eM12 = 0.0f;
      xform.eM21 = 0.0f;
      xform.eM22 = (float)cos(rotation_angle);
      xform.eDx = (float)x;
      xform.eDy = (float)y + (float)brick_half_height;
      GetWorldTransform(hdc, &old_xform);
      SetWorldTransform(hdc, &xform);

      // Выводим фон
      SelectObject(hdc, back_pen);
      SelectObject(hdc, back_brush);

      offset = 3.0 * (1.0 - fabs(xform.eM22)) * (double)AsConfig::Global_Scale;
      brick_half_offset = (int)round(offset);
      Rectangle(hdc, 0, -brick_half_height - brick_half_offset, AsConfig::Brick_Width * AsConfig::Global_Scale, brick_half_height - brick_half_offset);

      // Выводим передний план
      SelectObject(hdc, front_pen);
      SelectObject(hdc, front_brush);

      Rectangle(hdc, 0, -brick_half_height, AsConfig::Brick_Width * AsConfig::Global_Scale, brick_half_height);

      if (rotation_step > 4 && rotation_step <= 12)
      {
         if (letter_type == ELT_O)
         {
            SelectObject(hdc, Letter_Pen);
            Ellipse(hdc, 0 + 5 * AsConfig::Global_Scale, (-5 * AsConfig::Global_Scale) / 2, 0 + 10 * AsConfig::Global_Scale, 5 * AsConfig::Global_Scale / 2);
         }
      }

      SetWorldTransform(hdc, &old_xform);
   }
}
//-------------------------------------------------------------------------------------------------------------------------

