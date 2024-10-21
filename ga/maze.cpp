#include "maze.h"
#include<windows.h>
#include<cstdio>

const int ROAD = 1;//用const便于阅读和标记,,,记下来
const int WALL = 0;//初始化为0
const int PL = 2;

maze_m ma;

static void hide_cursor(void) {
    CONSOLE_CURSOR_INFO my_cur = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &my_cur);
    return;
}
static void towhere(void) {
    COORD pos = { 0,0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return;
}

void setup_maze(int x, int y) {//随机造迷宫
	ma.maze[x][y] = ROAD;
	int direct[4][2] = { { 1, 0},{-1, 0},{ 0, -1},{ 0, 1} };
	//方向随机化
	for (int i = 0; i < 4; i++) {
		int c = rand() % 4;/*
		swap_my(&direct[c][0], &direct[0][0]);
		swap_my(&direct[c][1], &direct[0][1]);*/
		int t = direct[c][0];
		direct[c][0] = direct[0][0];
		direct[0][0] = t;
		t = direct[c][1];
		direct[c][1] = direct[0][1];
		direct[0][1] = t;
	}
	for (int i = 0; i < 4; i++) {
		int tx = x, ty = y;
		int shrt_dis = rand() % 6 + 1;//顺着一个方向挖
		while (shrt_dis > 0) {
			tx += direct[i][0];
			ty += direct[i][1];
			if (ma.maze[tx][ty] == ROAD) //不回头
				break;
			int jud = 0;
			for (int j = tx - 1; j <= tx + 1; j++) {
				for (int k = ty - 1; k <= ty + 1; k++) {
					//下面的是四个方向
					if (abs(k - ty) + abs(j - tx) == 1 && ma.maze[j][k] == ROAD)
						jud += 1;
				}
			}
			if (jud > 1)//判断过回头路，要是两个方向有的话就要被挖穿了。。。
				break;
			shrt_dis -= 1;
			ma.maze[tx][ty] = ROAD;
		}
		if (shrt_dis <= 0) {
			setup_maze(tx, ty);//递归继续走！
		}
	}
	return;
}
int originize_maze(int st, int ed) {
	//防挖迷宫的时候挖出来(就是方便判断)
	for (int i = 0; i < MAX; i++) {
		ma.maze[i][0] = ROAD;
		ma.maze[0][i] = ROAD;
		ma.maze[i][MAX - 1] = ROAD;
		ma.maze[MAX - 1][i] = ROAD;
	}
	ma.stx = st; ma.sty = ed;
	setup_maze(st, ed + 1);
	//	CreateMaze(st, ed + 1);
	ma.maze[st][ed] = PL;
	for (int i = MAX - 3; i > 0; i--) {
		if (ma.maze[i][MAX - 3] == ROAD) {
			ma.maze[i][MAX - 2] = ROAD;
			return i;
		}
	}
	return -1;
}
int move_pl(char tool, int* x, int* y, int mark) {
	int a = *x, b = *y;
	switch (tool) {
	case 0:
		*x -= 1;
		break;
	case 1:
		*y -= 1;
		break;
	case 2:
		*x += 1;
		break;
	case 3:
		*y += 1;
		break;
	default:
		return mark;
	}
	if (*x > 0 && *y > 0 && *x < MAX - 1 && *y < MAX - 1 && ma.maze[*x][*y] != WALL) {
		ma.maze[a][b] = ROAD;
		ma.maze[*x][*y] = PL;
		mark -= 10;
		return mark;
	}
	*x = a;
	*y = b;
	return mark;
}
static bool complete_m(int x, int y) {
	if (x == ma.edx && y == MAX - 2) {
		return 1;
	}
	return 0;
}
void picture_maze(int mark) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j <= MAX; j++) {
			if (ma.maze[i][j] == ROAD)
				printf("  ");//中文输入，小子！
			if (ma.maze[i][j] == WALL)
				printf("口");
			if (ma.maze[i][j] == PL)
				printf("大");
		}
		printf("\n");
	}
	return;
}