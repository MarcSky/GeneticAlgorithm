#include "chromosome.h"

Chromosome::Chromosome(){
    fitness = 0.0;
    initRandomeBits();
}

Chromosome::~Chromosome() {

}

void Chromosome::initRandomeBits(void) {
    x = qrand() % WIDTH;
    y = qrand() % HEIGHT;
}


void Chromosome::calcFitness(void) {
    fitness = 0.0f;
}
