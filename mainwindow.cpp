#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //setMinimumSize(500, 500);
    setWindowTitle(trUtf8("Potyogós amőba"));

    newGameAction = new QAction(trUtf8("Ú&j játék"), this);
    newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    newGameAction->setStatusTip(trUtf8("Új játék indítása standard mérettel(8x5)"));

    configGameAction = new QAction(trUtf8("Új játék beállítása"), this);
    configGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    configGameAction->setStatusTip(trUtf8("Új játék beállítása"));

    exitGameAction = new QAction(trUtf8("Kilépés"), this);
    exitGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    exitGameAction->setStatusTip(trUtf8("Kilépés a játékból"));

    saveGameAction = new QAction(trUtf8("Játék mentése"), this);
    saveGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    saveGameAction->setStatusTip(trUtf8("Játék mentése"));

    loadGameAction = new QAction(trUtf8("Játék betöltése"), this);
    loadGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    loadGameAction->setStatusTip(trUtf8("Meglévő játék betöltése"));

    gameMenu = menuBar()->addMenu(trUtf8("&Játék"));
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(configGameAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitGameAction);

    dataMenu = menuBar()->addMenu(trUtf8("&Műveletek"));
    dataMenu->addAction(saveGameAction);
    dataMenu->addAction(loadGameAction);

    dialog = new ConfigDialog;

    widget = new TicTacToeWidget(this);
    setFixedSize(widget->width(), widget->height() + menuBar()->height());
    setCentralWidget(widget);

    connect(exitGameAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(configGameAction, SIGNAL(triggered(bool)), dialog, SLOT(exec()));
}

MainWindow::~MainWindow()
{

}
