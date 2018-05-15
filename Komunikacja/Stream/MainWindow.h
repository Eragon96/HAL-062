//
// Created by marcin on 13.05.18.
//

#ifndef STREAM_MAINWINDOW_H
#define STREAM_MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include "Player.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Player *m_player;
};


#endif //STREAM_MAINWINDOW_H
