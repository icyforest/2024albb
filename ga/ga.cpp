#include"ga.h"
#include"maze.h"
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cmath>

void setup_pop(population_cr* population) {
	srand((unsigned int)time(nullptr));
	population->is_running = 1;

	population->pop_size = POPULATION_MAX - 10;
	population->gene_length = CHRONOSOME_MAX - 10;
	population->chronosome_lenth = CHRONOSOME_MAX - 10;

	population->crossover_rate = 0.7f;
	population->mutation_rate = 0.001f;

	population->highest_fitness_score = -1.0f;
	population->total_fitness_score = -1.0f;
	population->fittest_geneme = -1;

	population->generation = 0;

	for (int i = 0; i < population->pop_size; i++) {
		for (int j = 0; j < population->chronosome_lenth; j++) {
			population->genemes[i].genes[j] = rand() % 4;
		}
		population->genemes[i].fitness = tes_go_geneme(& (population->genemes[i]),
														  population->chronosome_lenth,
														  population);
		population->total_fitness_score += population->genemes[i].fitness;
		if (population->highest_fitness_score < population->genemes[i].fitness) {
			population->highest_fitness_score = population->genemes[i].fitness;
			population->fittest_geneme = i;
		}
	}
}//初始化
double tes_go_geneme(geneme_cr* geneme_temp,int length_max,population_cr* population) {
	int x = ma.stx, y = ma.sty;
	for (int i = 0; i < length_max; i++) {
		int a = x, b = y;
		switch (geneme_temp->genes[i])
		{
		case 0:
			x -= 1;
			break;
		case 1:
			y -= 1;
			break;
		case 2:
			x += 1;
			break;
		case 3:
			y += 1;
			break;
		default:
			printf("888");
			break;
		}
		if (x == ma.edx && y == ma.edy) {
			population->is_running = false;
			return 1.0f;
		}
		if (x > 0 && y > 0 && x < MAX - 1 && y < MAX - 1 && ma.maze[x][y] != WALL) {
			continue;
		}
		x = a;
		y = b;
	}
	int a_ed = abs(ma.edx - x); a_ed *= a_ed;
	int b_ed = abs(ma.edy - y); b_ed *= b_ed;
	return 1 / (sqrt(a_ed + b_ed) + 1);
}
//计算适应度
void update_fitness(population_cr* population) {
	population->highest_fitness_score = -1.0f;
	population->total_fitness_score = -1.0f;
	population->fittest_geneme = -1;
	population->total_fitness_score = 0.0;
	for (int i = 0; i < population->pop_size; i++) {
		population->genemes[i].fitness = tes_go_geneme(&(population->genemes[i]),
														population->chronosome_lenth,
														population);
		population->total_fitness_score += population->genemes[i].fitness;
		if (population->highest_fitness_score < population->genemes[i].fitness) {
			population->highest_fitness_score = population->genemes[i].fitness;
			population->fittest_geneme = i;
		}
	}
}//更新适应度

bool compare(population_cr *population, int a, int b) {
	for(int i = 0; i < population->pop_size; i++) {
		if(population->genemes[a].genes[i] != population->genemes[b].genes[i]) {
			return false;
		}
	}
	return true;
}

void mutation(population_cr *population) {
	for(int i = 0 ; i < population->pop_size; i++) {
		for(int j = 0;j < population->chronosome_lenth; j++) {
			if(rand() / (double)RAND_MAX < population->mutation_rate) {
				population->genemes[i].genes[j] = rand() % 4;
			}
		}
	}
}//变异

void crossover(population_cr *population, int a, int b) {
	if(rand() / (double)RAND_MAX < population->crossover_rate ||
		compare(population,a,b)) {
		return;
	}
	int start = rand() % population->chronosome_lenth;
	for(int i = start; i < population->chronosome_lenth; i++) {
		population->genemes[a].genes[i] ^= population->genemes[b].genes[i];
		population->genemes[b].genes[i] ^= population->genemes[a].genes[i];
		population->genemes[a].genes[i] ^= population->genemes[b].genes[i];
	}
}//重组

int wheel_selection(population_cr *population){
	double select_score = (rand() / (double)RAND_MAX) * population->total_fitness_score;
	double total = 0.0;
	int selected_geneme = 0;
	for (int i = 0; i < population->pop_size; i++) {
		total += population->genemes[i].fitness;
		if (total > select_score) {
			selected_geneme = i;
			break;
		}
	}
	return selected_geneme;
}/**/

void main_inherit(population_cr* population){
	if (population->is_running == 1 && population->generation < 120) {
		int a = wheel_selection(population);
		int b = wheel_selection(population);
		crossover(population, a, b);
		mutation(population);
		update_fitness(population);
	}
}//主遗传函数
