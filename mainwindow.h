#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "standartwidget.h"
#include "geneticwidget.h"
#include "geneticAlgorithm/ga.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StandartWidget *standart;
    GeneticWidget *genetic;
};

#endif // MAINWINDOW_H
