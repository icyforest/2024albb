#pragma once

#define CHRONOSOME_MAX 510
#define POPULATION_MAX 110

typedef struct geneme {
    char genes[CHRONOSOME_MAX];
    double fitness;
}geneme_cr;
typedef struct population_s {
    int pop_size;//总数

    geneme_cr genemes[POPULATION_MAX];//基因数

    double crossover_rate;//杂交度
    double mutation_rate;//突变度

    int gene_length;//基因长度
    int chronosome_lenth;//染色体长度

    int fittest_geneme;//最适应的基因编号
    double highest_fitness_score;//最高分
    double total_fitness_score;//最低分

    int generation;//代数

    bool is_running;//判断是否在运行
}population_cr;//结构体部分

double tes_go_geneme(geneme_cr* geneme_temp,int length_max, population_cr* population);//测试走路
void setup_pop(population_cr* population);
void update_fitness(population_cr* population);
bool compare(population_cr* population,int a,int b);

void mutation(population_cr* population);
void crossover(population_cr* population,int a,int b);

int wheel_selection(population_cr* population);

void main_inherit(population_cr * population);//遗传的主程序
