/*
Snake Game in C language using graphics library.
*/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

int udir = 0; // Up direction
int ddir = 0; // Down direction
int ldir = 0; // Left direction
int rdir = 1; // Right direction
int x[500];
int y[500];
int s_len = 3, block_size = 10;
int food_x, food_y;
int maxx, maxy;

void dev_info()
{
  char *msg = "Developed by Ali Amir";
  char solid_pattern[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  int max_height = getmaxy();
  setfillpattern(solid_pattern, BLUE);
  bar(0, maxy + 1, maxx, max_height);
  settextstyle(0, 0, 3);
  outtextxy((maxx - textwidth(msg)) / 2, maxy + ((30 - textheight(msg)) / 2), msg);
}

void init_pos()
{
  int i;
  for (i = 0; i < 500; i++)
  {
    x[i] = -1;
    y[i] = -1;
  }
}

int collision()
{
  int i;
  for (i = 1; i < s_len; i++)
  {
    if (x[0] == x[i] && y[0] == y[i])
    {
      return 1;
    }
  }
  if (x[0] < 0 || x[0] > maxx || y[0] < 0 || y[0] > maxy)
  {
    return 1;
  }
  return 0;
}
void move()
{
  int i;
  for (i = s_len; i > 0; i--)
  {
    x[i] = x[(i - 1)];
    y[i] = y[(i - 1)];
  }
  if (udir)
  {
    y[0] -= block_size;
  }
  else if (ddir)
  {
    y[0] += block_size;
  }
  else if (ldir)
  {
    x[0] -= block_size;
  }
  else if (rdir)
  {
    x[0] += block_size;
  }
}
void locate_food()
{
  int r;
  srand(time(0));
  r = (rand() % maxx) / block_size;
  food_x = r * block_size;
  r = (rand() % maxy) / block_size;
  food_y = r * block_size;
}
void check_food()
{
  if (x[0] == food_x && y[0] == food_y)
  {
    s_len++;
    locate_food();
  }
}
void draw_board()
{
  int i;
  char solid_pattern[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  setbkcolor(WHITE);
  cleardevice();
  setfillpattern(solid_pattern, BLUE);
  bar(food_x, food_y, food_x + 10, food_y + 10);
  setfillpattern(solid_pattern, RED);
  bar(x[0], y[0], x[0] + block_size, y[0] + block_size);
  setfillpattern(solid_pattern, GREEN);
  for (i = 1; i < s_len; i++)
  {
    bar(x[i], y[i], x[i] + 10, y[i] + 10);
  }
  dev_info();
}

void change_dir(char key)
{
  if ((key == 'a' || key == 75) && !rdir)
  {
    ldir = 1;
    udir = 0;
    ddir = 0;
  }
  else if ((key == 'd' || key == 77) && !ldir)
  {
    rdir = 1;
    udir = 0;
    ddir = 0;
  }
  else if ((key == 's' || key == 80) && !udir)
  {
    ddir = 1;
    ldir = 0;
    rdir = 0;
  }
  else if ((key == 'w' || key == 72) && !ddir)
  {
    udir = 1;
    ldir = 0;
    rdir = 0;
  }
}
void init_game()
{
  int i;
  for (i = 0; i < s_len; i++)
  {
    x[i] = 50 - (i * block_size);
    y[i] = 50;
  }
  locate_food();
}

void game_over()
{
  char *msg = "GAME OVER";
  setbkcolor(BLACK);
  cleardevice();
  settextstyle(0, 0, 3);
  outtextxy((maxx - textwidth(msg)) / 2, (maxy - textheight(msg)) / 2, msg);
  getch();
}

int main()
{
  int gd = DETECT, gm;
  char key;
  clrscr();
  initgraph(&gd, &gm, "C://TURBOC3//BGI");
  maxx = getmaxx();
  maxy = getmaxy() - 30;
  setbkcolor(BLACK);
  cleardevice();
  init_pos();
  init_game();
  while (!collision())
  {
    delay(1500);
    if (kbhit())
    {
      key = getch();
      change_dir(key);
    }
    move();
    if (kbhit())
    {
      key = getch();
      change_dir(key);
    }
    check_food();
    if (kbhit())
    {
      key = getch();
      change_dir(key);
    }
    draw_board();
    if (kbhit())
    {
      key = getch();
      change_dir(key);
    }
  }
  game_over();
  closegraph();
  return 0;
}
