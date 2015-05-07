#include "ga.h"

Chromosome::Chromosome(){
    qDebug() << "tut";
    fitness = 0;
//    x = qrand() % BOARD_WIDTH;
//    y = qrand() % BOARD_HEIGHT;
    for(int k = 1; k <= BOARD_HEIGHT; k++) {
        for(int j = 1; j <= BOARD_WIDTH; j++) {
//            int x = qrand() % BOARD_WIDTH;
//            int y = qrand() % BOARD_HEIGHT;
            map[k*BOARD_WIDTH + j] = qrand()%2;
        }
    }
    //memset(map, false, sizeof(bool)*(BOARD_WIDTH) * (BOARD_HEIGHT));

}

Chromosome::~Chromosome() {

}
