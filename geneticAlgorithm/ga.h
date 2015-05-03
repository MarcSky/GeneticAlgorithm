#ifndef GA_H
#define GA_H
#include <QtCore>
#include "chromosome.h"

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
    void mutate(Chromosome *c);
    void crossover(Chromosome *a, Chromosome *b);
    float getTotalFitness(void);
};

#endif // GA_H
