#include<cstdio>
#include<cstring>
#include<cmath>//绝对值处理
#include<iostream>
#include"ga.h"
#include"maze.h"

int main() {
	srand((unsigned)time(NULL));
	int x = rand() % (MAX - 4) + 2, y = 1;
	ma.edx = originize_maze(x, y);
	ma.edy = MAX - 2;
	population_cr* population = (population_cr*)malloc(sizeof(population_cr));
	setup_pop(population);
	while(population->is_running == 1) {
		main_inherit(population);
	}
	int final_ans = population->fittest_geneme;
	int mark = 50000;
	for(int i = 0;i < population->chronosome_lenth;i ++) {
		int step = population->genemes[final_ans].genes[i];
		move_pl(step,&x,&y,mark);
		picture_maze(mark);
		if(x == ma.edx && y == ma.edy) {
			break;
		}
	}
	printf("%lf",population->genemes[population->fittest_geneme].fitness);
	return 0;
}