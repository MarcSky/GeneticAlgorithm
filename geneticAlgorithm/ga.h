#ifndef GA_H
#define GA_H
#include <QtCore>

#define CHROMOSOME_SIZE 8
#define MUTATE_RATE 10
#define POPULATION_SIZE 5
#define BOARD_WIDTH POPULATION_SIZE
#define BOARD_HEIGHT POPULATION_SIZE
class Chromosome
{
public:
    Chromosome();
    ~Chromosome();
    unsigned int x, y;
    double fitness;
    Chromosome operator=(Chromosome const &b) {
        this->x = b.x;
        this->y = b.y;
    }

private:

};

class Genetic
{
public:
    Genetic();
    ~Genetic();
public:

private:
    unsigned int generation;
    double totalFitness;

    QList<Chromosome> *population;
    void roulette();
    void crossover(void);
    void mutate(Chromosome *c);
    void crossover(Chromosome *a, Chromosome *b);
    void run(void);
    float getTotalFitness(void);
};

#endif // GA_H
