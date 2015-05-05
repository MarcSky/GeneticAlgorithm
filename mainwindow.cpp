#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    standart(new StandartWidget(this))
{
    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked()), standart,SLOT(startGame()));
    connect(ui->stopButton, SIGNAL(clicked()), standart,SLOT(stopGame()));
//    connect(ui->stopButton, SIGNAL(clicked()), standart,SLOT(startGame()));

    ui->standartGame->addWidget(standart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

}
