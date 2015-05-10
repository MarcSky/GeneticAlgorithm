#ifndef STANDARTWIDGET_H
#define STANDARTWIDGET_H

#include <QWidget>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "geneticAlgorithm/ga.h"

class StandartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StandartWidget(QWidget *parent = 0);
    ~StandartWidget();
    double totalFitness;
    void roulette();
    void crossover(void);
    void mutate(Chromosome *c);
    void crossover(Chromosome *d, Chromosome *a, Chromosome *b);

    float getTotalFitness(void);

signals:

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void run(void);
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
    bool isAlive(int k, int j);
    void resetUniverse();// reset the size of universe
    bool stopFlag;
    bool *currentMap;
    bool *nextMap;
    Chromosome *population;
    int bestFitness;
    Chromosome bestChromosome;
};

#endif // STANDARTWIDGET_H
