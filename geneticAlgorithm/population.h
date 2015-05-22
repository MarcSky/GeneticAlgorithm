#ifndef POPULATION_H
#define POPULATION_H
#include "chromosome.h"
#include <iostream>
class Population
{
public:
    Population();
    ~Population();
    bool solution(void);
    void crossover(Chromosome *a, Chromosome *b);
    void mutate(Chromosome *a);
    int roulette(void);
    bool * getCurrentMap() const{
        std::cout<<"---------Популяция-----------"<<std::endl;
        for(int i = 0; i < BOARD_WIDTH; i++) {
            for(int j = 0; j < BOARD_HEIGHT; j++){
                std::cout << current_map[j + i * BOARD_HEIGHT] << " ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"---------Популяция-----------"<<std::endl;
        return current_map;
    }
    bool * getBestSolution(void);


private:
    bool isAlive(int x, int y);
    void computePopulationFitness(void);

    void buildCurrentMap(void);

    bool *current_map;
    Chromosome * population;
    Chromosome * nextPopulation;

    Chromosome * bestSolution;
    int bestFitness;
    int populationFitness;
    QList <Chromosome*> bestSolutions;
};

#endif // POPULATION_H
