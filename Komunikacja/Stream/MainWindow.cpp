//
// Created by marcin on 13.05.18.
//

#include "MainWindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_player = new Player(this);
    ui->centralWidget->layout()->addWidget(m_player);

    connect(ui->snapButton, SIGNAL(clicked()), m_player, SLOT(takeSnapshot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}