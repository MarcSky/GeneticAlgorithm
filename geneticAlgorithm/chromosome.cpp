#include "chromosome.h"

Chromosome::Chromosome(){
    fitness = 0.0;
    initRandomeBits();
    qDebug() << "ok";
}

Chromosome::~Chromosome() {

}

//double Chromosome::getFitness(void) {
//    return fitness;
//}

//void Chromosome::setFitness(double f) {
//    fitness = f;
//}

void Chromosome::initRandomeBits(void) {
//    for (int i = 0; i < CHROMOSOME_SIZE - 1; i++) {
//        char x = (qrand() % 2) ? '1' : '0';
//        bits += x;
//    }
//    x = qrand() % WIDTHBOARD;
//    y = qrand() % HEIGTBOARD;
}

//void Chromosome::setBits(const QString b) {
////    bits = b;
//}

//QString Chromosome::getBits(void) {
//    return "bits";
//}

void Chromosome::calcFitness(void) {
    //x2+x
//    int value = getNumber();
//    fitness = 1.0 * (value * value + value);
    fitness = 0.0f;
}

//int Chromosome::getNumber(void) {
//   return 0;//bits.toInt(0, 2);
//}
