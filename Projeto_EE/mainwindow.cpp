#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <limits>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_Ajuda_itemClicked(QListWidgetItem *item)
{
    QString nomeItem = item->text();
    if(nomeItem == "Login"){

    }
}

