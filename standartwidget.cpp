#include "standartwidget.h"
#include <iostream>
StandartWidget::StandartWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    population = new Chromosome[POPULATION_SIZE];
    currentMap = new bool[(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2)];
    nextMap = new bool[(BOARD_WIDTH  + 2) * (BOARD_HEIGHT+2)];
    stopFlag = false;
    generations = 3;
    memset(currentMap, false, sizeof(bool)*(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2));
    memset(nextMap, false, sizeof(bool)*(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2));
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));

//
}

StandartWidget::~StandartWidget()
{
    delete population;
    delete [] currentMap;
    delete [] nextMap;
}

void StandartWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

bool StandartWidget::isAlive(int k, int j) {
    int power = 0;
    power += currentMap[(k+1)*BOARD_HEIGHT + j];
    power += currentMap[(k-1)*BOARD_HEIGHT + j];
    power += currentMap[k*BOARD_HEIGHT + (j+1)];
    power += currentMap[k*BOARD_HEIGHT + (j-1)];
    power += currentMap[(k+1)*BOARD_HEIGHT + ( j-1)];
    power += currentMap[(k-1)*BOARD_HEIGHT + (j+1)];
    power += currentMap[(k-1)*BOARD_HEIGHT + (j-1)];
    power += currentMap[(k+1)*BOARD_HEIGHT +  (j+1)];
    if (((currentMap[k*BOARD_HEIGHT + j]) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void StandartWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    QColor gridColor = QColor("#000"); // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/BOARD_WIDTH; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/BOARD_HEIGHT; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void StandartWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/BOARD_WIDTH;
    double cellHeight = (double)height()/BOARD_HEIGHT;
    for(int k=0; k < BOARD_WIDTH; k++) {
        for(int j=0; j <BOARD_HEIGHT; j++) {
            if(currentMap[k*BOARD_HEIGHT + j]) { // if there is any sense to paint it
                qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(QColor("#0f0"))); // fill cell with brush of main color
            }
        }
    }
}

void StandartWidget::newGeneration(Chromosome *pool){
    qDebug() << "~~~~~~~~~~~New generations~~~~~~~~~~~~~~~";
    int notChanged=0;
    int a=  pool[0].x;
    int b=  pool[0].y;
    for(int k=1; k <= BOARD_HEIGHT; k++) {
        for(int j=1; j <= BOARD_WIDTH; j++) {
            if(pool[(k-1)*BOARD_WIDTH + (j-1)].x < BOARD_WIDTH && pool[(k-1)*BOARD_WIDTH + (j-1)].y < BOARD_HEIGHT) {

                currentMap[k*BOARD_WIDTH + j] = true;

            }
        }
    }

    for(int y = 1 ; y < BOARD_HEIGHT; y++) {
        for(int x = 1; x < BOARD_WIDTH; x++) {

            nextMap[y * BOARD_WIDTH + x] = isAlive(y,x);
            if(nextMap[y * POPULATION_SIZE + x] == currentMap[y * POPULATION_SIZE + x])
                notChanged++;
        }
    }

    if(notChanged == POPULATION_SIZE) {
        stopFlag = true;
        qDebug() << "=================Game is off================";
    }

    for(int k=1; k <= BOARD_HEIGHT; k++) {
        for(int j=1; j <= BOARD_WIDTH; j++) {
            currentMap[k*BOARD_WIDTH + j] = nextMap[k*BOARD_WIDTH + j];
        }
    }

    update();
}


void StandartWidget::resetUniverse()
{
    delete [] currentMap;
    delete [] nextMap;
    currentMap = new bool[(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2)];
    nextMap = new bool[(BOARD_WIDTH  + 2) * (BOARD_HEIGHT+2)];
    memset(currentMap, false, sizeof(bool)*(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2));
    memset(nextMap, false, sizeof(bool)*(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2));
}

void StandartWidget::startGame()
{
//    generations = 3;
//    gameFlag = false;
//    run();
    timer->start();
}

void StandartWidget::stopGame()
{
//    gameFlag = true;
    timer->stop();
}

void StandartWidget::clear()
{
    for(int k = 1; k <= BOARD_HEIGHT; k++) {
        for(int j = 1; j <= BOARD_WIDTH; j++) {
            currentMap[k*BOARD_WIDTH + j] = false;
        }
    }
//    gameEnds(true);
    update();
}

void StandartWidget::mutate(Chromosome *c) {
    int rate = qrand()%100;
    if (rate > MUTATE_RATE) {
        unsigned char bit = qrand() % (sizeof(char) * 8);
        c->x = (~(c->x << bit));
        c->y = (~(c->y << bit));
    }
}

void StandartWidget::crossover(Chromosome *d, Chromosome *a, Chromosome *b) {
    unsigned char crosspointX = qrand() % (sizeof(char) * 8);
    unsigned char crosspointY = qrand() % (sizeof(char) * 8);

//    Chromosome *temp;

//    if (qrand()%2) {
//        temp = a;
//        a = b;
//        b = temp;
//    }

    //=====Координата X
    unsigned int iMask = 1;
    iMask <<=crosspointX;
    iMask -= iMask;

    unsigned int iChrom1_end = a->x & iMask;
    unsigned int iChrom2_end = b->x & iMask;

    unsigned int iMask2 = ~iMask;
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

    d->x = a->x;
    d->y = a->y;

}



void StandartWidget::run(void) {
    Chromosome data[POPULATION_SIZE * POPULATION_SIZE];

//    while(!stopFlag) {
        for(int i = 0; i < POPULATION_SIZE; i++){
            for(int j = 0; j < POPULATION_SIZE; j++) {


                crossover(&data[i * POPULATION_SIZE + j], &population[i], &population[j]);

                mutate(&data[i * POPULATION_SIZE + j]);
                newGeneration(data);

            }
        }
//        stopFlag = true;
//    }
}



