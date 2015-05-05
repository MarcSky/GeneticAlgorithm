#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <QtCore>

#define CHROMOSOME_SIZE 8
#define MUTATE_RATE 10
#define POPULATION_SIZE 30
#define HEIGHT 50
#define WIDTH 50

class Chromosome
{
public:
    Chromosome();
    ~Chromosome();
    void calcFitness(void);
    void initRandomeBits(void);
    unsigned char x, y;
    double fitness;

private:

};

#endif // CHROMOSOME_H
