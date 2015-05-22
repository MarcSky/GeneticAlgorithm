#include "chromosome.h"

Chromosome::Chromosome(){
    fitness = 0;
    for(int k = 1; k <= BOARD_HEIGHT; k++) {
        for(int j = 1; j <= BOARD_WIDTH; j++) {
            map[k*BOARD_WIDTH + j] = qrand() % 2;
        }
    }
}

Chromosome::~Chromosome() {

}
