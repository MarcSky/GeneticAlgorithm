#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    standart(new StandartWidget(this))
{
    ui->setupUi(this);
    qDebug() << sizeof(char);
    //ui->standartGame->addWidget(standart);
//    qDebug() << "start genetic algorithm";
//    Genetic g;
//    qDebug() << "end geentic algorithm";
}

MainWindow::~MainWindow()
{
    delete ui;
}
