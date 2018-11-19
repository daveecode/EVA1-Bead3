#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configdialog.h"
#include "tictactoewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QMenu *gameMenu;
    QMenu *dataMenu;
    QAction *newGameAction;
    QAction *exitGameAction;
    QAction *configGameAction;
    QAction *saveGameAction;
    QAction *loadGameAction;

    ConfigDialog *dialog;
    TicTacToeWidget *widget;
};

#endif // MAINWINDOW_H
