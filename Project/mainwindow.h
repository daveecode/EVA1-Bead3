#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLayout>
#include "configdialog.h"
#include "tictactoewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void sendData();
    void sizeSlot();

private:

    QMenu *gameMenu;
    QMenu *dataMenu;
    QAction *newGameAction;
    QAction *exitGameAction;
    QAction *configGameAction;
    QAction *saveGameAction;
    QAction *loadGameAction;

    QLabel *firstLabel;
    QLabel *secondLabel;
    QHBoxLayout *labels;

    ConfigDialog *dialog;
    TicTacToeWidget *widget;
};

#endif // MAINWINDOW_H
