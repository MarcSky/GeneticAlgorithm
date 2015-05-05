#include "ga.h"

Genetic::Genetic()
{

}

Genetic::~Genetic(){
    delete population;
}

float Genetic::getTotalFitness(void) {
    float total = 0.0f;
//    for(int i = 0; i < population->size(); i++) {
//        total = (*population)[i].getFitness();
//    }
    return total;
}

void Genetic::mutate(Chromosome *c) {
    int rate = qrand()%100;
    if (rate > MUTATE_RATE) {
        unsigned char bit = qrand() % (sizeof(char) * 8);
        c->x = (~(c->x << bit));
        c->y = (~(c->y << bit));
    }
}

void Genetic::crossover(Chromosome *a, Chromosome *b) {
    unsigned char crosspointX = qrand() % (sizeof(char) * 8);
    unsigned char crosspointY = qrand() % (sizeof(char) * 8);

    Chromosome *temp;

    if (qrand()%2) {
        temp = a;
        a = b;
        b = temp;
    }

    //=====Координата X
    unsigned char iMask = 1;
    iMask <<=crosspointX;
    iMask -= iMask;

    unsigned char iChrom1_end = a->x & iMask;
    unsigned char iChrom2_end = b->x & iMask;

    unsigned char iMask2 = ~iMask;
    a->x &= iMask2;
    b->x &= iMask2;

    a->x |= iChrom2_end;
    b->x |= iChrom1_end;

    //=====Координата Y
    iMask = 1;
    iMask <<=crosspointY;
    iMask -= iMask;

    iChrom1_end = a->y & iMask;
    iChrom2_end = b->y & iMask;

    iMask2 = ~iMask;
    a->y &= iMask2;
    b->y &= iMask2;

    a->y |= iChrom2_end;
    b->y |= iChrom1_end;
}

void Genetic::roulette(void) {
//    for(auto &s: population) {
        
//    }
}

void Genetic::run(void) {
    population = new QList<Chromosome>;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        Chromosome m;
        population->push_back(m);
    }

    generation = 0;

    qDebug() << getTotalFitness();

}

Chromosome::Chromosome(){
    qDebug() << "tut";
    fitness = 0.0;
    x = qrand() % BOARD_WIDTH;
    y = qrand() % BOARD_HEIGHT;
}

Chromosome::~Chromosome() {

}
