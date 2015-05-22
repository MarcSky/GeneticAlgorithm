#ifndef STANDARTWIDGET_H
#define STANDARTWIDGET_H

#include <QWidget>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "geneticAlgorithm/population.h"

class StandartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StandartWidget(QWidget *parent = 0);
    ~StandartWidget();

signals:

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();


public slots:
    void startGame(); // start
    void stopGame(); // finish
    void clear(); // clear

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;
    int generations;
    void resetUniverse();// reset the size of universe
    bool stopFlag;
    bool *currentMap;
//    bool *nextMap;
    Population *population;
    bool bestSolutionFind;

};

#endif // STANDARTWIDGET_H
