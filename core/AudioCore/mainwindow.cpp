#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QDebug>
#include <qcustomplot.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot(QVector<double> y,QCustomPlot* widget){
    widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    widget->addGraph();
    qDebug() << "in plot";
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    QVector<double> x(y.size());
    for (int i = 0; i < y.size(); i ++) { x[i] = i; }
    widget->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    widget->xAxis->setLabel("x");
    widget->yAxis->setLabel("y");

    //Установим область, которая будет показываться на графике
    widget->xAxis->setRange(0, y.size());//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];
    for (int i=1; i<x.size(); i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }
    widget->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    widget->replot();
}
