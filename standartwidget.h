#ifndef STANDARTWIDGET_H
#define STANDARTWIDGET_H

#include <QWidget>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

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
    void startGame(const int &number = -1); // start
    void stopGame(); // finish
    void clear(); // clear

protected:
    void paintEvent(QPaintEvent *);

private:
    int universeSize;
    bool* universe; // map
    bool* next; // map
    QTimer * timer;
    int generations;
    bool isAlive(int k, int j);
    void resetUniverse();// reset the size of universe

};

#endif // STANDARTWIDGET_H
