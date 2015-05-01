#include "ga.h"

Genetic::Genetic()
{
    population = new QList<Chromosome>;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        Chromosome m;
        population->push_back(m);
    }

    for(int i = 0; i < POPULATION_SIZE; i++) {
        qDebug() << (*population)[i].getNumber();//list->at(i).getBits();
        (*population)[i].calcFitness();
    }
    generation = 0;

    qDebug() << getTotalFitness();
}

Genetic::~Genetic(){
    delete population;
}

void Genetic::init(void) {
    population = new QList<Chromosome>;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        Chromosome m;
        population->push_back(m);
    }

    for(int i = 0; i < POPULATION_SIZE; i++) {
        qDebug() << (*population)[i].getBits();//list->at(i).getBits();
    }
    generation = 0;
}

float Genetic::getTotalFitness(void) {
    float total = 0.0f;
    for(int i = 0; i < population->size(); i++) {
        total = (*population)[i].getFitness();
    }
    return total;
}

void Genetic::mutate(void) {

}

void Genetic::roulette(void) {
//    for(auto &s: population) {
        
//    }
}
