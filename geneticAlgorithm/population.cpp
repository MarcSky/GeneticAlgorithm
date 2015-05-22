#include "population.h"

Population::Population()
{
    population = new Chromosome[POPULATION_SIZE];
    nextPopulation = new Chromosome[POPULATION_SIZE];

    current_map = new bool[(BOARD_WIDTH) * (BOARD_HEIGHT)];
    populationFitness = 0;
    bestFitness = 0;
    bestSolution = NULL;

    computePopulationFitness();
}

Population::~Population()
{
    delete [] population;
    delete [] nextPopulation;
//    delete [] current_map;
}

bool Population::isAlive(int x, int y) {
    int power = 0;
    if((x-1) >= 0 && current_map[(x-1) + y * BOARD_HEIGHT]) power+=1;
    if((x-1) >= 0 && (y-1) >= 0 &&current_map[(x-1) + (y-1) * BOARD_HEIGHT]) power+=1;
    if((y-1) >= 0 && current_map[(x) + (y-1) * BOARD_HEIGHT]) power+=1;
    if((x+1) <= BOARD_WIDTH && (y-1) >=0 && current_map[(x+1) +(y-1) * BOARD_HEIGHT]) power+=1;
    if((x+1) <= BOARD_WIDTH && current_map[(x+1) + y * BOARD_HEIGHT]) power+=1;
    if((x+1) <= BOARD_WIDTH && (y+1) <= BOARD_HEIGHT && current_map[(x+1) +(y+1) * BOARD_HEIGHT]) power+=1;
    if((y+1) <= BOARD_HEIGHT && current_map[(x) + (y+1) * BOARD_HEIGHT]) power+=1;
    if((y+1) <= BOARD_HEIGHT && (x-1) >=0 && current_map[(x-1) + (y+1) * BOARD_HEIGHT]) power+=1;

    if (((current_map[x + y * BOARD_HEIGHT]) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void Population::crossover(Chromosome *a, Chromosome *b) {
    int point = qrand() % BOARD_WIDTH * BOARD_HEIGHT;
    bool temp[BOARD_WIDTH * BOARD_HEIGHT];
    memcpy(&temp, a->map, sizeof(bool) * BOARD_WIDTH * BOARD_HEIGHT);

    memcpy(&a->map[point], &b->map[point], sizeof(bool) * (BOARD_WIDTH * BOARD_HEIGHT - point));
    memcpy(&b->map[point], &temp[point], sizeof(bool) * (BOARD_WIDTH * BOARD_HEIGHT - point));
}

void Population::mutate(Chromosome *a) {
    int rate = qrand() % 100;
    if(rate > MUTATE_RATE) {
        int gen =  qrand() % BOARD_WIDTH * BOARD_HEIGHT;
        a->map[gen] =! a->map[gen];

        gen =  qrand() % BOARD_WIDTH * BOARD_HEIGHT;
        a->map[gen] =! a->map[gen];

        gen =  qrand() % BOARD_WIDTH * BOARD_HEIGHT;
        a->map[gen] =! a->map[gen];
    }
}

void Population::computePopulationFitness(void) {
    int bestF = 0;
    for(int p = 0 ; p < POPULATION_SIZE; p++) {
        int local_fitness = 0;
        memcpy(current_map, population[p].map, sizeof(bool) * BOARD_HEIGHT * BOARD_HEIGHT);
        for(int k = 0 ; k < BOARD_HEIGHT; k++) {
            for(int j = 0; j < BOARD_WIDTH; j++) {
                if(isAlive(k,j)) {
                    local_fitness += 1;
                }
            }
        }
        qDebug() << "Population " << p << ". Fitness " << local_fitness;
        population[p].fitness = local_fitness;
        populationFitness += local_fitness;
        if(bestF < local_fitness) {
            bestFitness = local_fitness; bestSolution = &population[p];
        }
    }
    bestSolutions.append(bestSolution);
}

int Population::roulette(void) {

    int random = qrand() % populationFitness;
    int sum = 0;

    for(int i = 0 ; i < POPULATION_SIZE; i++) {
        sum += population[i].fitness;
        if(sum >= random) {
            return i;
        }
    }

    return -1;
}

bool Population::solution() {

    for(int p = 0; p < POPULATION_SIZE; p++) {

        int index1 = 0;
        int index2 = 0;

        while(index1 <= 0 && index2 <= 0 && index1 == index2){
            index1 = roulette();
            index2 = roulette();
        }

        Chromosome a = population[index1];
        Chromosome b = population[index2];

        crossover(&a, &b);
        mutate(&a);
        mutate(&b);

        nextPopulation[p++] = a;
        nextPopulation[p++] = b;
    }
    memcpy(population, nextPopulation, sizeof(Chromosome) * POPULATION_SIZE);
    computePopulationFitness();
    buildCurrentMap();
    return true;
}

void Population::buildCurrentMap(void){
    memcpy(current_map, bestSolution->map, sizeof(bool) * BOARD_HEIGHT * BOARD_HEIGHT);
    for(int k = 0 ; k < BOARD_HEIGHT; k++) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            if(isAlive(k,j)) {
                current_map[j + k * BOARD_WIDTH] = true;
            } else {
                current_map[j + k * BOARD_WIDTH] = false;
            }
        }
    }
}

    bool * Population::getBestSolution(void){
        int bestI = 0;
        int bestF = 0;
        for(int i = 0; i < bestSolutions.size(); i++) {
            if(bestSolutions.at(i)->fitness > bestF) {
                bestF = bestSolutions.at(i)->fitness;
                bestI = i;
            }
        }

        memcpy(current_map, bestSolutions.at(bestI)->map, sizeof(bool) * BOARD_HEIGHT * BOARD_HEIGHT);
        for(int k = 0 ; k < BOARD_HEIGHT; k++) {
            for(int j = 0; j < BOARD_WIDTH; j++) {
                if(isAlive(k,j)) {
                    current_map[j + k * BOARD_WIDTH] = true;
                } else {
                    current_map[j + k * BOARD_WIDTH] = false;
                }
            }
        }
        qDebug() << "Best fitness "  << bestF;
        return current_map;
    }


