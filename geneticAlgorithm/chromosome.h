#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <QtCore>
#define CHROMOSOME_SIZE 8
#define MUTATE_RATE 10
#define POPULATION_SIZE 30

class Chromosome
{
public:
    Chromosome();
    ~Chromosome();
    void calcFitness(void);
//    QString getBits(void);
//    void setBits(const QString);
    void initRandomeBits(void);
//    int getNumber(void);
    unsigned char x, y;
    double fitness;

private:
    //QString bits;
};

#endif // CHROMOSOME_H
