#pragma once

#define MAX 22
extern const int ROAD;//用const便于阅读和标记,,,记下来
extern const int WALL;//初始化为0
extern const int PL;

static void hide_cursor(void);
static void towhere(void);//最后打步骤的操作

void setup_maze(int x, int y);
int originize_maze(int st, int ed);
void picture_maze(int mark);
int move_pl(char tool, int* x, int* y, int mark);
static bool complete_m(int x, int y);//maze相关

typedef struct Maze {
    int maze[MAX][MAX];
    int stx, edx;
    int sty, edy;
    int ma_weight, ma_height;
}maze_m;

extern maze_m ma;
