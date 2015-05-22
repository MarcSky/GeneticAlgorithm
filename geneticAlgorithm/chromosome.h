#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <QtCore>
#include <iostream>
#include <stdlib.h>

#define CHROMOSOME_SIZE 8
#define MUTATE_RATE 10
#define POPULATION_SIZE 20
#define BOARD_WIDTH POPULATION_SIZE
#define BOARD_HEIGHT POPULATION_SIZE

class Chromosome
{
public:
    Chromosome();
    ~Chromosome();
    bool map[(BOARD_WIDTH) * (BOARD_HEIGHT)];
    int fitness;

    Chromosome& operator=(Chromosome const &b) {
        if( this != &b){
            memcpy(&map,&(b.map),sizeof(bool) * BOARD_WIDTH * BOARD_HEIGHT);
            fitness = b.fitness;
        }
        return *this;
    }

//    bool operator==( Chromosome &a, Chromosome &b )
//    {
//        if(a.fitness != b.fitness) return false;
//        for(int i = 0 ; i < BOARD_WIDTH; i ++) {
//            for(int j = 0; j < BOARD_HEIGHT; j++) {
//                if(a.map[j + i * BOARD_HEIGHT] != b.map[j + i * BOARD_HEIGHT]) return false;
//            }
//        }
//        return true;
//    }

private:
};


#endif // CHROMOSOME_H
