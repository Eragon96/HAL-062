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
    m_player->setMinimumSize(640,480);
    ui->centralWidget->layout()->addWidget(m_player);

    connect(ui->snapButton, SIGNAL(clicked()), m_player, SLOT(takeSnapshot()));
    connect(ui->playButton, &QPushButton::clicked, [=](){ int portNumber = this->ui->portLineEdit->text().toInt();
                                                                QString capsContent = this->ui->capsLineEdit->text();
                                                                m_player->playRTP(portNumber, capsContent);});
}

MainWindow::~MainWindow()
{
    delete ui;
}
