#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{
}

GameWidget::paintEvent(QPaintEvent *p) {
    QPainter painter(this);

    int width = size().width() - 3;
    int height = size().height() - 5;

    painter.fillRect(0, 0, width, height, QColor(220,220,220));
    painter.drawText(10, 10, "Machine " + QString::number(id));
}
