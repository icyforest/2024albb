#include<cstdio>
#include<windows.h>
#include<conio.h>

const int MAX = 12;
int map[MAX][MAX];
int end_game;
const int BLACK = 1;
const int WHITE = -1;
const int NO = 0;

typedef struct point_ {
    int x, y;
    long long score;
}point;

void display_map(bool jud);
point score_judge(int x, int y, int inverse);
int win_judge();
void hide_cursor();
void towhere(short a,short b);
void game_start();
point ai_main_algorithm(const point p,int generation,int inverse);

int main()
{
    while (1) {
        system("cls");
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                map[i][j] = 0;
            }
        }
        char c = _getch();
        if (c == 27) {
            printf("thanks for playing\n");
            return 0;
        }
        end_game = 0;
        game_start();
    }
    return 0;
}


void hide_cursor() {
    CONSOLE_CURSOR_INFO my_cursor = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &my_cursor);
}

void towhere(short a, short b) {
    COORD coord = { a,b };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void display_map(bool jud) {
    system("cls");
    printf(" ");
    for (int j = 0; j < MAX - 1; j++) {
        printf("%d", j);
    }
    printf("\n");
    for (int i = 1; i < MAX - 1; i++) {
        printf("%2d", i);
        for (int j = 1; j < MAX - 1; j++) {
            if (map[i][j] == 0) {
                printf("-");
            }
            else if (map[i][j] == 1) {
                printf("X");
            }
            else if (map[i][j] == -1) {
                printf("O");
            }
        }
        printf("\n");
    }
    if (jud) {
        printf("ai is thinking...");
    }
    else {
        printf("input 2 numbers:");
    }
}

point score_judge(int x, int y, int inverse) {
    point temp = { x,y,0ll };
    if (x <= 0 || y <= 0 || x > MAX - 2 || y > MAX - 2) {
        return temp;
    }
    if (map[x][y + 1] == inverse && y + 1 < MAX - 1) {
        if (map[x][y + 2] == inverse && y + 2 < MAX - 1) {
            if (map[x][y + 3] == inverse && y + 3 < MAX - 1) {
                if (map[x][y + 4] == inverse && y + 4 < MAX - 1) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x][y + 4] == inverse * -1
                    && y + 4 < MAX - 1) || y + 4 >= MAX - 1) {
                    if ((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0) {
                        temp.score += 100;
                    }
                    else if (map[x][y - 1] == inverse && y - 1 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0) {
                    temp.score += 1000;
                }
                else if (map[x][y - 1] == inverse && y - 1 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (map[x][y - 1] == inverse && y - 1 > 0) {
                if (map[x][y - 2] == inverse && y - 2 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x][y - 2] == inverse * -1 && y - 2 > 0)
                    || y - 2 <= 0) {
                    if ((map[x][y + 3] == inverse * -1 && y + 3 < MAX - 1)
                        || y + 3 >= MAX - 1) {
                        temp.score += 100;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x][y + 3] == inverse * -1 && y + 3 < MAX - 1)
                    || y + 3 >= MAX + 1) {
                    temp.score += 1000;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0)
                && ((map[x][y + 3] == inverse * -1 && y + 3 < MAX - 1) || y + 3 >= MAX - 1)) {
                temp.score += 10;
            }
            else if (((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0)
                || ((map[x][y + 3] == inverse * -1 && y + 3 < MAX - 1) || y + 3 >= MAX - 1)) {
                temp.score += 100;
            }
            else {
                temp.score += 1000;
            }
        }
        else if (map[x][y - 1] == inverse && y - 1 > 0) {
            if (map[x][y - 2] == inverse && y - 2 > 0) {
                temp.score += 2147483647;
                temp.score *= inverse;
                return temp;
            }
            else if ((map[x][y - 2] == inverse * -1 && y - 2 > 0) || y - 2 <= 0) {
                if ((map[x][y + 2] == inverse * -1 && y + 2 < MAX - 1) || y + 2 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if ((map[x][y + 2] == inverse * -1 && y + 2 < MAX - 1) || y + 2 >= MAX - 1) {
                temp.score += 1000;
            }
            else {
                temp.score += 10000;
            }
        }//
        else if (((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0)
            && ((map[x][y + 2] == inverse * -1 && y + 2 < MAX - 1) || y + 2 >= MAX - 1)) {
            temp.score += 1;
        }
        else if (((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0)
            || ((map[x][y + 2] == inverse * -1 && y + 2 < MAX - 1) || y + 2 >= MAX - 1)) {
            temp.score += 10;
        }
        else {
            temp.score += 100;
        }
    }
    else {
        if (map[x][y - 1] == inverse && y - 1 > 0) {
            if (map[x][y - 2] == inverse && y - 2 > 0) {
                if (map[x][y - 3] == inverse && y - 3 > 0) {
                    if (map[x][y - 4] == inverse && y - 4 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else if (((map[x][y - 4] == inverse * -1 && y - 4 > 0) || y - 4 <= 0)
                        && ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1)) {
                        temp.score += 100;
                    }
                    else if ((map[x][y - 4] == inverse * -1 && y - 4 > 0) || y - 4 <= 0) {
                        temp.score += 1000;
                    }
                    else if ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1) {
                        temp.score += 1000;
                    }
                    else {
                        temp.score += 10000;
                    }
                }
                else if (((map[x][y - 3] == inverse * -1 && y - 3 > 0) || y - 3 <= 0)
                    && ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1)) {
                    temp.score += 10;
                }
                else if ((map[x][y - 3] == inverse * -1 && y - 3 > 0) || y - 3 <= 0) {
                    temp.score += 100;
                }
                else if ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if (((map[x][y - 2] == inverse * -1 && y - 2 > 0) || y - 2 <= 0)
                && ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1)) {
                temp.score += 1;
            }
            else if ((map[x][y - 2] == inverse * -1 && y - 2 > 0) || y - 2 <= 0) {
                temp.score += 10;
            }
            else if ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1) {
                temp.score += 10;
            }
            else {
                temp.score += 100;
            }
        }
        else if (((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0)
            && ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1)) {
            temp.score += 0;
        }
        else if ((map[x][y - 1] == inverse * -1 && y - 1 > 0) || y - 1 <= 0) {
            temp.score += 1;
        }
        else if ((map[x][y + 1] == inverse * -1 && y + 1 < MAX - 1) || y + 1 >= MAX - 1) {
            temp.score += 1;
        }
        else {
            temp.score += 5;
        }
    }
    if (map[x + 1][y] == inverse && x + 1 < MAX - 1) {
        if (map[x + 2][y] == inverse && x + 2 < MAX - 1) {
            if (map[x + 3][y] == inverse && x + 3 < MAX - 1) {
                if (map[x + 4][y] == inverse && x + 4 < MAX - 1) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x + 4][y] == inverse * -1
                    && x + 4 < MAX - 1) || x + 4 >= MAX - 1) {
                    if ((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0) {
                        temp.score += 100;
                    }
                    else if (map[x - 1][y] == inverse && x - 1 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0) {
                    temp.score += 1000;
                }
                else if (map[x - 1][y] == inverse && x - 1 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (map[x - 1][y] == inverse && x - 1 > 0) {
                if (map[x - 2][y] == inverse && x - 2 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x - 2][y] == inverse * -1 && x - 2 > 0)
                    || x - 2 <= 0) {
                    if ((map[x + 3][y] == inverse * -1 && x + 3 < MAX - 1)
                        || x + 3 >= MAX - 1) {
                        temp.score += 100;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x + 3][y] == inverse * -1 && x + 3 < MAX - 1)
                    || x + 3 >= MAX + 1) {
                    temp.score += 1000;
                }
                else {
                    temp.score += 10000;
                }
            }//
            else if (((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0)
                && ((map[x + 3][y] == inverse * -1 && x + 3 < MAX - 1) || x + 3 >= MAX - 1)) {
                temp.score += 10;
            }
            else if (((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0)
                || ((map[x + 3][y] == inverse * -1 && x + 3 < MAX - 1) || x + 3 >= MAX - 1)) {
                temp.score += 100;
            }
            else {
                temp.score += 1000;
            }
        }
        else if (map[x - 1][y] == inverse && x - 1 > 0) {
            if (map[x - 2][y] == inverse && x - 2 > 0) {
                temp.score += 2147483647;
                temp.score *= inverse;
                return temp;
            }
            else if ((map[x - 2][y] == inverse * -1 && x - 2 > 0) || x - 2 <= 0) {
                if ((map[x + 2][y] == inverse * -1 && x + 2 < MAX - 1) || x + 2 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if ((map[x + 2][y] == inverse * -1 && x + 2 < MAX - 1) || x + 2 >= MAX - 1) {
                temp.score += 1000;
            }
            else {
                temp.score += 10000;
            }
        }
        else if (((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0)
            && ((map[x + 2][y] == inverse * -1 && x + 2 < MAX - 1) || x + 2 >= MAX - 1)) {
            temp.score += 1;
        }
        else if (((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0)
            || ((map[x + 2][y] == inverse * -1 && x + 2 < MAX - 1) || x + 2 >= MAX - 1)) {
            temp.score += 10;
        }
        else {
            temp.score += 100;
        }
    }
    else {
        if (map[x - 1][y] == inverse && x - 1 > 0) {
            if (map[x - 2][y] == inverse && x - 2 > 0) {
                if (map[x - 3][y] == inverse && x - 3 > 0) {
                    if (map[x - 4][y] == inverse && x - 4 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else if (((map[x - 4][y] == inverse * -1 && x - 4 > 0) || x - 4 <= 0)
                        && ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1)) {
                        temp.score += 100;
                    }
                    else if ((map[x - 4][y] == inverse * -1 && x - 4 > 0) || x - 4 <= 0) {
                        temp.score += 1000;
                    }
                    else if ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1) {
                        temp.score += 1000;
                    }
                    else {
                        temp.score += 10000;
                    }
                }
                else if (((map[x - 3][y] == inverse * -1 && x - 3 > 0) || x - 3 <= 0)
                    && ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1)) {
                    temp.score += 10;
                }
                else if ((map[x - 3][y] == inverse * -1 && x - 3 > 0) || x - 3 <= 0) {
                    temp.score += 100;
                }
                else if ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if (((map[x - 2][y] == inverse * -1 && x - 2 > 0) || x - 2 <= 0)
                && ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1)) {
                temp.score += 1;
            }
            else if ((map[x - 2][y] == inverse * -1 && x - 2 > 0) || x - 2 <= 0) {
                temp.score += 10;
            }
            else if ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1) {
                temp.score += 10;
            }
            else {
                temp.score += 100;
            }
        }
        else if (((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0)
            && ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1)) {
            temp.score += 0;
        }
        else if ((map[x - 1][y] == inverse * -1 && x - 1 > 0) || x - 1 <= 0) {
            temp.score += 1;
        }
        else if ((map[x + 1][y] == inverse * -1 && x + 1 < MAX - 1) || x + 1 >= MAX - 1) {
            temp.score += 1;
        }
        else {
            temp.score += 5;
        }
    }
    if (map[x + 1][y + 1] == inverse && y + 1 < MAX - 1 && x + 1 < MAX - 1) {
        if (map[x + 2][y + 2] == inverse && y + 2 < MAX - 1 && x + 2 < MAX - 1) {
            if (map[x + 3][y + 3] == inverse && y + 3 < MAX - 1 && x + 3 < MAX - 1) {
                if (map[x + 4][y + 4] == inverse && y + 4 < MAX - 1 && x + 4 < MAX - 1) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x + 4][y + 4] == inverse * -1 && y + 4 < MAX - 1 && x + 4 < MAX - 1)
                    || y + 4 >= MAX - 1 || x + 4 >= MAX - 1) {
                    if ((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
                        || y - 1 <= 0 || x - 1 <= 0) {
                        temp.score += 100;
                    }
                    else if (map[x - 1][y - 1] == inverse && y - 1 > 0 && x - 1 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
                    || y - 1 <= 0 || x - 1 <= 0) {
                    temp.score += 1000;
                }
                else if (map[x - 1][y - 1] == inverse && y - 1 > 0 && x - 1 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (map[x - 1][y - 1] == inverse && y - 1 > 0 && x - 1 > 0) {
                if (map[x - 2][y - 2] == inverse && y - 2 > 0 && x - 2 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x - 2][y - 2] == inverse * -1 && y - 2 > 0 && x - 2 > 0)
                    || y - 2 <= 0 || x - 2 <= 0) {
                    if ((map[x + 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x + 3 < MAX - 1)
                        || y + 3 >= MAX - 1 || x + 3 >= MAX - 1) {
                        temp.score += 100;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x][y + 3] == inverse * -1 && y + 3 < MAX - 1)
                    || y + 3 >= MAX + 1) {
                    temp.score += 1000;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
                || y - 1 <= 0 || x - 1 <= 0)
                && ((map[x + 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x + 3 < MAX - 1)
                    || y + 3 >= MAX - 1 || x + 3 >= MAX - 1)) {
                temp.score += 10;
            }
            else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
                || y - 1 <= 0 || x - 1 <= 0)
                || ((map[x + 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x + 3 < MAX - 1)
                    || y + 3 >= MAX - 1 || x + 3 >= MAX - 1)) {
                temp.score += 100;
            }
            else {
                temp.score += 1000;
            }
        }
        else if (map[x - 1][y - 1] == inverse && y - 1 > 0 && x - 1 > 0) {
            if (map[x - 2][y - 2] == inverse && y - 2 > 0 && x - 2 > 0) {
                temp.score += 2147483647;
                temp.score *= inverse;
                return temp;
            }
            else if ((map[x - 2][y - 2] == inverse * -1 && y - 2 > 0 && x - 2 > 0)
                || y - 2 <= 0 || x - 2 <= 0) {
                if ((map[x + 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x + 2 < MAX - 1)
                    || y + 2 >= MAX - 1 || x + 2 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if ((map[x + 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x + 2 < MAX - 1)
                || y + 2 >= MAX - 1 || x + 2 >= MAX - 1) {
                temp.score += 1000;
            }
            else {
                temp.score += 10000;
            }
        }//
        else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
            || y - 1 <= 0 || x - 1 <= 0)
            && ((map[x + 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x + 2 < MAX - 1)
                || y + 2 >= MAX - 1 || x + 2 >= MAX - 1)) {
            temp.score += 1;
        }
        else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
            || y - 1 <= 0 || x - 1 <= 0)
            || ((map[x + 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x + 2 < MAX - 1)
                || y + 2 >= MAX - 1 || x + 2 >= MAX - 1)) {
            temp.score += 10;
        }
        else {
            temp.score += 100;
        }
    }
    else {
        if (map[x - 1][y - 1] == inverse && y - 1 > 0 && x - 1 > 0) {
            if (map[x - 2][y - 2] == inverse && y - 2 > 0 && x - 2 > 0) {
                if (map[x - 3][y - 3] == inverse && y - 3 > 0 && x - 3 > 0) {
                    if (map[x - 4][y - 4] == inverse && y - 4 > 0 && x - 4 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else if (((map[x - 4][y - 4] == inverse * -1 && y - 4 > 0 && x - 4 > 0)
                        || y - 4 <= 0 || x - 4 <= 0)
                        && ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                            || y + 1 >= MAX - 1 || x + 1 >= MAX - 1)) {
                        temp.score += 100;
                    }
                    else if ((map[x - 4][y - 4] == inverse * -1 && y - 4 > 0 && x - 4 > 0)
                        || y - 4 <= 0 || x - 4 <= 0) {
                        temp.score += 1000;
                    }
                    else if ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                        || y + 1 >= MAX - 1 || x + 1 >= MAX - 1) {
                        temp.score += 1000;
                    }
                    else {
                        temp.score += 10000;
                    }
                }
                else if (((map[x - 3][y - 3] == inverse * -1 && y - 3 > 0 && x - 3 > 0)
                    || y - 3 <= 0 || x - 3 <= 0)
                    && ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                        || y + 1 >= MAX - 1 || x + 1 >= MAX - 1)) {
                    temp.score += 10;
                }
                else if ((map[x - 3][y - 3] == inverse * -1 && y - 3 > 0 && x - 3 > 0)
                    || y - 3 <= 0 || x - 3 <= 0) {
                    temp.score += 100;
                }
                else if ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                    || y + 1 >= MAX - 1 || x + 1 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if (((map[x - 2][y - 2] == inverse * -1 && y - 2 > 0 && x - 2 > 0)
                || y - 2 <= 0 || x - 2 <= 0)
                && ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                    || y + 1 >= MAX - 1 || x + 1 >= MAX - 1)) {
                temp.score += 1;
            }
            else if ((map[x - 2][y - 2] == inverse * -1 && y - 2 > 0 && x - 2 > 0)
                || y - 2 <= 0 || x - 2 <= 0) {
                temp.score += 10;
            }
            else if ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                || y + 1 >= MAX - 1 || x + 1 >= MAX - 1) {
                temp.score += 10;
            }
            else {
                temp.score += 100;
            }
        }
        else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
            || y - 1 <= 0 || x - 1 <= 0)
            && ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
                || y + 1 >= MAX - 1 || x + 1 >= MAX - 1)) {
            temp.score += 0;
        }
        else if ((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
            || y - 1 <= 0 || x - 1 <= 0) {
            temp.score += 1;
        }
        else if ((map[x + 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x + 1 < MAX - 1)
            || y + 1 >= MAX - 1 || x + 1 >= MAX - 1) {
            temp.score += 1;
        }
        else {
            temp.score += 5;
        }
    }
    if (map[x + 1][y - 1] == inverse && y - 1 > 0 && x + 1 < MAX - 1) {
        if (map[x + 2][y - 2] == inverse && y - 2 > 0 && x + 2 < MAX - 1) {
            if (map[x + 3][y - 3] == inverse && y - 3 > 0 && x + 3 < MAX - 1) {
                if (map[x + 4][y - 4] == inverse && y - 4 > 0 && x + 4 < MAX - 1) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x + 4][y - 4] == inverse * -1 && y - 4 > 0 && x + 4 < MAX - 1)
                    || y - 4 <= 0 || x + 4 >= MAX - 1) {
                    if ((map[x - 1][y + 1] == inverse * -1 && y + 1 <= MAX - 1 && x - 1 > 0)
                        || y + 1 >= MAX - 1 || x - 1 <= 0) {
                        temp.score += 100;
                    }
                    else if (map[x - 1][y + 1] == inverse && y + 1 < MAX - 1 && x - 1 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x - 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x - 1 > 0)
                    || y + 1 >= MAX - 1 || x - 1 <= 0) {
                    temp.score += 1000;
                }
                else if (map[x - 1][y + 1] == inverse && y + 1 < MAX - 1 && x - 1 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (map[x - 1][y + 1] == inverse && y + 1 < MAX - 1 && x - 1 > 0) {
                if (map[x - 2][y + 2] == inverse && y + 2 < MAX - 1 && x - 2 > 0) {
                    temp.score += 2147483647;
                    temp.score *= inverse;
                    return temp;
                }
                else if ((map[x - 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x - 2 > 0)
                    || y + 2 >= MAX - 1 || x - 2 <= 0) {
                    if ((map[x + 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x + 3 < MAX - 1)
                        || y + 3 >= MAX - 1 || x + 3 >= MAX - 1) {
                        temp.score += 100;
                    }
                    else {
                        temp.score += 1000;
                    }
                }
                else if ((map[x + 3][y - 3] == inverse * -1 && y - 3 > 0 && x + 3 < MAX - 1)
                    || y - 3 <= 0 || x + 3 >= MAX - 1) {
                    temp.score += 1000;
                }
                else {
                    temp.score += 10000;
                }
            }
            else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
                || y - 1 <= 0 || x - 1 <= 0)
                && ((map[x + 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x + 3 < MAX - 1)
                    || y + 3 >= MAX - 1 || x + 3 >= MAX - 1)) {
                temp.score += 10;
            }
            else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
                || y - 1 <= 0 || x - 1 <= 0)
                || ((map[x + 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x + 3 < MAX - 1)
                    || y + 3 >= MAX - 1 || x + 3 >= MAX - 1)) {
                temp.score += 100;
            }
            else {
                temp.score += 1000;
            }
        }
        else if (map[x - 1][y - 1] == inverse && y - 1 > 0 && x - 1 > 0) {
            if (map[x - 2][y + 2] == inverse && y + 2 < MAX - 1 && x - 2 > 0) {
                temp.score += 2147483647;
                temp.score *= inverse;
                return temp;
            }
            else if ((map[x - 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x - 2 > 0)
                || y + 2 >= MAX - 1 || x - 2 <= 0) {
                if ((map[x + 2][y - 2] == inverse * -1 && y - 2 > 0 && x + 2 < MAX - 1)
                    || x + 2 >= MAX - 1 || y - 2 <= 0) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if ((map[x][y + 2] == inverse * -1 && y + 2 < MAX - 1) || y + 2 >= MAX - 1) {
                temp.score += 1000;
            }
            else {
                temp.score += 10000;
            }
        }//
        else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
            || y - 1 <= 0 || x - 1 <= 0)
            && ((map[x + 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x + 2 < MAX - 1)
                || y + 2 >= MAX - 1 || x + 2 >= MAX - 1)) {
            temp.score += 1;
        }
        else if (((map[x - 1][y - 1] == inverse * -1 && y - 1 > 0 && x - 1 > 0)
            || y - 1 <= 0 || x - 1 <= 0)
            || ((map[x + 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x + 2 < MAX - 1)
                || y + 2 >= MAX - 1 || x + 2 >= MAX - 1)) {
            temp.score += 10;
        }
        else {
            temp.score += 100;
        }
    }
    else {
        if (map[x - 1][y + 1] == inverse && y + 1 < MAX - 1 && x - 1 > 0) {
            if (map[x - 2][y + 2] == inverse && y + 2 < MAX - 1 && x - 2 > 0) {
                if (map[x - 3][y + 3] == inverse && y + 3 < MAX - 1 && x - 3 > 0) {
                    if (map[x - 4][y + 4] == inverse && y + 4 < MAX - 1 && x - 4 > 0) {
                        temp.score += 2147483647;
                        temp.score *= inverse;
                        return temp;
                    }
                    else if (((map[x - 4][y + 4] == inverse * -1 && y + 4 < MAX - 1 && x - 4 > 0)
                        || y + 4 > MAX - 1 || x - 4 <= 0)
                        && ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                            || y - 1 <= 0 || x + 1 >= MAX - 1)) {
                        temp.score += 100;
                    }
                    else if ((map[x - 4][y + 4] == inverse * -1 && y + 4 < MAX - 1 && x - 4 > 0)
                        || y + 4 >= MAX - 1 || x - 4 <= 0) {
                        temp.score += 1000;
                    }
                    else if ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                        || y - 1 <= 0 || x + 1 >= MAX - 1) {
                        temp.score += 1000;
                    }
                    else {
                        temp.score += 10000;
                    }
                }
                else if (((map[x - 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x - 3 > 0)
                    || y + 3 >= MAX - 1 || x - 3 <= 0)
                    && ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                        || y - 1 <= 0 || x + 1 >= MAX - 1)) {
                    temp.score += 10;
                }
                else if ((map[x - 3][y + 3] == inverse * -1 && y + 3 < MAX - 1 && x - 3 > 0)
                    || y + 3 >= MAX - 1 || x - 3 <= 0) {
                    temp.score += 100;
                }
                else if ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                    || y + 1 <= 0 || x + 1 >= MAX - 1) {
                    temp.score += 100;
                }
                else {
                    temp.score += 1000;
                }
            }
            else if (((map[x - 2][y + 2] == inverse * -1 && y + 2 < MAX - 1 && x - 2 > 0)
                || y + 2 >= MAX - 1 || x - 2 <= 0)
                && ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                    || y - 1 <= 0 || x + 1 >= MAX - 1)) {
                temp.score += 1;
            }
            else if ((map[x - 2][y + 2] == inverse * -1 && y - 2 < MAX - 1 && x - 2 > 0)
                || y + 2 >= MAX - 1 || x - 2 <= 0) {
                temp.score += 10;
            }
            else if ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                || y - 1 <= 0 || x + 1 >= MAX - 1) {
                temp.score += 10;
            }
            else {
                temp.score += 100;
            }
        }
        else if (((map[x - 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x - 1 > 0)
            || y + 1 >= MAX - 1 || x - 1 <= 0)
            && ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
                || y - 1 <= 0 || x + 1 >= MAX - 1)) {
            temp.score += 0;
        }
        else if ((map[x - 1][y + 1] == inverse * -1 && y + 1 < MAX - 1 && x - 1 > 0)
            || y + 1 >= MAX - 1 || x - 1 <= 0) {
            temp.score += 1;
        }
        else if ((map[x + 1][y - 1] == inverse * -1 && y - 1 > 0 && x + 1 < MAX - 1)
            || y - 1 <= 0 || x + 1 >= MAX - 1) {
            temp.score += 1;
        }
        else {
            temp.score += 5;
        }
    }//unfinished
    temp.score *= inverse;
    return temp;
}

int win_judge() {
    int win = 0;
    bool full = true;
    for (int i = 1; i < MAX - 1; i++) {
        for (int j = 1; j < MAX - 1; j++) {
            if (map[i][j] == 0) {
                full = false;
                break;
            }
        }
    }
    for (int i = 1; i < MAX - 1; i++) {
        for (int j = 1; j < MAX - 5; j++) {
            if (map[i][j] == BLACK && map[i][j + 1] == BLACK
                && map[i][j + 2] == BLACK && map[i][j + 3] == BLACK
                && map[i][j + 4] == BLACK) {
                return BLACK;
            }
            if (map[i][j] == WHITE && map[i][j + 1] == WHITE
                && map[i][j + 2] == WHITE && map[i][j + 3] == WHITE
                && map[i][j + 4] == WHITE) {
                return WHITE;
            }
        }
    }
    for (int i = 1; i < MAX - 5; i++) {
        for (int j = 1; j < MAX - 1; j++) {
            if (map[i][j] == BLACK && map[i + 1][j] == BLACK
                && map[i + 2][j] == BLACK && map[i + 3][j] == BLACK
                && map[i + 4][j] == BLACK) {
                return BLACK;
            }
            if (map[i][j] == WHITE && map[i + 1][j] == WHITE
                && map[i + 2][j] == WHITE && map[i + 3][j] == WHITE
                && map[i + 4][j] == WHITE) {
                return WHITE;
            }
        }
    }
    for (int i = 1; i < MAX - 5; i++) {
        for (int j = 1; j < MAX - 5; j++) {
            if (map[i][j] == BLACK && map[i + 1][j + 1] == BLACK
                && map[i + 2][j + 2] == BLACK && map[i + 3][j + 3] == BLACK
                && map[i + 4][j + 4] == BLACK) {
                return BLACK;
            }
            if (map[i][j] == WHITE && map[i + 1][j + 1] == WHITE
                && map[i + 2][j + 2] == WHITE && map[i + 3][j + 3] == WHITE
                && map[i + 4][j + 4] == WHITE) {
                return WHITE;
            }
        }
    }
    for (int i = 1; i < MAX - 5; i++) {
        for (int j = MAX - 1; j > 4; j--) {
            if (map[i][j] == BLACK && map[i + 1][j - 1] == BLACK
                && map[i + 2][j - 2] == BLACK && map[i + 3][j - 3] == BLACK
                && map[i + 4][j - 4] == BLACK) {
                return BLACK;
            }
            if (map[i][j] == WHITE && map[i + 1][j - 1] == WHITE
                && map[i + 2][j - 2] == WHITE && map[i + 3][j - 3] == WHITE
                && map[i + 4][j - 4] == WHITE) {
                return WHITE;
            }
        }
    }
    if (full) {
        return 3;
    }
    return win;
}

point ai_main_algorithm(const point p, int generation, int inverse) {
    if (generation == 4) {
        return score_judge(p.x, p.y, inverse);
    }
    long long score = score_judge(p.x, p.y, inverse).score;
    long long temp_max = -21474836480;
    point ans = { -1,-1,0ll };
    for (int i = 1; i < MAX - 1; i++) {
        for (int j = 1; j < MAX - 1; j++) {
            if (map[i][j] != 0) {
                continue;
            }
            point temp = { i,j,0ll };
            if (ans.x == -1) {
                ans = temp;
            }
            map[i][j] = inverse * -1;
            long long score_temp = score + ai_main_algorithm(temp, generation + 1, inverse * -1).score;
            if (score_temp > temp_max) {
                temp_max = score_temp;
                ans = temp; ans.score = temp_max;
            }
            map[i][j] = NO;
        }
    }
    return ans;
}

void game_start() {
    bool jud = 0;
    int x = 6, y = 6;
    point p;
    display_map(jud);
    while (!end_game) {
        jud = 0;
        p.x = x; p.y = y;
        p = ai_main_algorithm(p, 1, WHITE);
        /**/
        if (p.x <= 0 || p.y <= 0 || p.x > MAX - 2 || p.y > MAX - 2) {
            end_game = 3;
            break;
        }
        map[p.x][p.y] = BLACK;
        display_map(jud);
        end_game = win_judge();
        if (end_game) {
            break;
        }
        jud = 1;
        scanf_s("%d%d", &x, &y);
        if (x >= 11 || y >= 11 || x < 1 || y < 1 || map[x][y] != NO) {
            display_map(0);
            continue;
        }
        map[x][y] = WHITE;
        display_map(jud);
        end_game = win_judge();
    }
    system("cls");
    switch (end_game) {
    case 1://ai
        printf("ai win");
        break;
    case -1://pl
        printf("you win");
        break;
    case 3:
        printf("ai don't want to play");
        break;
    default:
        printf("what's this");
        break;
    }
    Sleep(1000);
}
