#include "standartwidget.h"

StandartWidget::StandartWidget(QWidget *parent) :
    QWidget(parent),
    universeSize(50),
    timer(new QTimer(this))
{
    timer->setInterval(500);
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
//    connect(timer, SIGNAL(timeout()), this, SIGNAL(newGeneration()));
}

StandartWidget::~StandartWidget()
{
    delete [] universe;
    delete [] next;
}

void StandartWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

bool StandartWidget::isAlive(int k, int j) {
    int power = 0;
    power += universe[(k+1)*universeSize +  j];
    power += universe[(k-1)*universeSize + j];
    power += universe[k*universeSize + (j+1)];
    power += universe[k*universeSize + (j-1)];
    power += universe[(k+1)*universeSize + ( j-1)];
    power += universe[(k-1)*universeSize + (j+1)];
    power += universe[(k-1)*universeSize + (j-1)];
    power += universe[(k+1)*universeSize +  (j+1)];
    if (((universe[k*universeSize + j] == true) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void StandartWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    QColor gridColor = QColor("#000"); // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/universeSize; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/universeSize; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void StandartWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            if(universe[k*universeSize + j] == true) { // if there is any sense to paint it
                qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(QColor("#0f0"))); // fill cell with brush of main color
            }
        }
    }
}

void StandartWidget::newGeneration(){
    if(generations < 0)
        generations++;

    int notChanged=0;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            next[k*universeSize + j] = isAlive(k, j);
            if(next[k*universeSize + j] == universe[k*universeSize + j])
                notChanged++;
        }
    }
    if(notChanged == universeSize*universeSize) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        return;
    }
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            universe[k*universeSize + j] = next[k*universeSize + j];
        }
    }
    update();
    generations--;
    if(generations == 0) {
        stopGame();
        QMessageBox::information(this,
                                 tr("Game finished."),
                                 tr("Iterations finished."),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel);
    }
}


void StandartWidget::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
}

void StandartWidget::startGame(const int &number)
{
    generations = number;
    timer->start();
}

void StandartWidget::stopGame()
{
    timer->stop();
}

void StandartWidget::clear()
{
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j] = false;
        }
    }
    update();
}


