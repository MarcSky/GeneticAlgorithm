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
//    unsigned int x, y;
    bool map[(BOARD_WIDTH+2) * (BOARD_HEIGHT+2)];
    int fitness;
    Chromosome operator=(Chromosome const &b) {
//        this->x = b.x;
//        this->y = b.y;
    }

private:

};
#endif // GA_H
