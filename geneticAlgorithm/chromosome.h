#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <QtCore>
#define CHROMOSOME_SIZE 10
#define MUTATE_RATE 1
#define CROSSOVER_RATE 70

class Chromosome
{
public:
    Chromosome();
    ~Chromosome();
    double getFitness(void);
    void setFitness(double);
    void calcFitness(void);
    QString getBits(void);
    void setBits(const QString);
    void initRandomeBits(void);
    int getNumber(void);
private:
    QString bits;
    double fitness;
};

#endif // CHROMOSOME_H
