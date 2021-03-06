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

    firstLabel = new QLabel(trUtf8("X játékos: "), this);
    secondLabel = new QLabel(trUtf8("O játékos: "), this);
    labels = new QHBoxLayout;

    labels->addWidget(firstLabel);
    labels->addWidget(secondLabel);


    dialog = new ConfigDialog;

    widget = new TicTacToeWidget(this);
    setFixedSize(widget->width(), widget->height() + menuBar()->height() + statusBar()->height());
    setCentralWidget(widget);

    setLayout(labels);

    statusBar()->addWidget(firstLabel);
    statusBar()->addWidget(secondLabel);

    connect(exitGameAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(configGameAction, SIGNAL(triggered(bool)), dialog, SLOT(exec()));
    connect(newGameAction, SIGNAL(triggered(bool)), this, SLOT(sendData()));
    connect(dialog, SIGNAL(accepted()), this, SLOT(sendData()));
    connect(saveGameAction, SIGNAL(triggered(bool)), widget, SLOT(setSave()));
    connect(loadGameAction, SIGNAL(triggered(bool)), widget, SLOT(setLoad()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::sendData()
{

    widget->newGame(dialog->columns(), dialog->rows());
    setFixedSize(widget->width(), widget->height() + menuBar()->height() + statusBar()->height());
    firstLabel->setText(trUtf8("X játékos: ") + dialog->firstPlayerName());
    secondLabel->setText(trUtf8("O játékos: ") + dialog->secondPlayerName());
}
