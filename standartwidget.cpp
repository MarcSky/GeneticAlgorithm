#include "standartwidget.h"
#include <iostream>
#include <stdlib.h>
StandartWidget::StandartWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    currentMap = new bool[(BOARD_WIDTH) * (BOARD_HEIGHT)];
//    nextMap = new bool[(BOARD_WIDTH  + 2) * (BOARD_HEIGHT+2)];
    stopFlag = false;
    generations = 0;
    population = new Population();
    memset(currentMap, false, sizeof(bool)*(BOARD_WIDTH) * (BOARD_HEIGHT));
//    memset(nextMap, false, sizeof(bool)*(BOARD_WIDTH + 2) * (BOARD_HEIGHT + 2));
    bestSolutionFind = false;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

StandartWidget::~StandartWidget()
{
    delete [] currentMap;
    delete population;
//    delete [] nextMap;
}

void StandartWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
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
    for(int k = 0; k < BOARD_WIDTH; k++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            if(currentMap[k * BOARD_HEIGHT + j]) { // if there is any sense to paint it
                qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(QColor("#0f0"))); // fill cell with brush of main color
            }
        }
    }
}

void StandartWidget::newGeneration(){
    if(generations < 5) {
        if(population->solution()) {

            currentMap = population->getCurrentMap();

            std::cout<<"-----КАРТА------" <<std::endl;
            for(int i = 0; i < BOARD_WIDTH; i++) {
                for(int j = 0; j < BOARD_HEIGHT; j++){
                    std::cout << currentMap[j + i * BOARD_HEIGHT] << " ";
                }
                std::cout<<std::endl;
            }
            std::cout<<"-----КАРТА------" <<std::endl;

            currentMap = population->getCurrentMap();
        }
        update();
        generations++;
    } else {
        if(!bestSolutionFind) {
            qDebug() << "best solution";
            currentMap = population->getBestSolution();
            update();
            qDebug() << "best solution";
            bestSolutionFind = true;
        }
    }
}


void StandartWidget::resetUniverse() {
    delete [] currentMap;
//    delete [] nextMap;
    currentMap = new bool[(BOARD_WIDTH) * (BOARD_HEIGHT)];
//    nextMap = new bool[(BOARD_WIDTH) * (BOARD_HEIGHT)];
    memset(currentMap, false, sizeof(bool)*(BOARD_WIDTH) * (BOARD_HEIGHT));
//    memset(nextMap, false, sizeof(bool)*(BOARD_WIDTH) * (BOARD_HEIGHT));
}

void StandartWidget::startGame() {
    timer->start();
}

void StandartWidget::stopGame() {
    timer->stop();
    update();
}

void StandartWidget::clear() {
    for(int k = 1; k <= BOARD_HEIGHT; k++) {
        for(int j = 1; j <= BOARD_WIDTH; j++) {
            currentMap[k*BOARD_WIDTH + j] = false;
        }
    }
    update();
}
