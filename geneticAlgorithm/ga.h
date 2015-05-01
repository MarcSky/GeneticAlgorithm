#ifndef GA_H
#define GA_H
#include <QtCore>
#include "chromosome.h"
#define POPULATION_SIZE 2500

class Genetic
{
public:
    Genetic();
    ~Genetic();
public:
    void step(void);
    void init(void);

private:
    unsigned int generation;
    double totalFitness;

    QList<Chromosome> *population;
    void roulette();
    void crossover(void);
    void mutate(void);
    float getTotalFitness(void);
};

#endif // GA_H
