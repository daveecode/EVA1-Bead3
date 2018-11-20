#include "tictactoewidget.h"
#include "datadb.h"
#include <QMessageBox>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{


    data = new DataDb();
    model = new TicTacToeModel(data);

    /*setFixedSize(model->tableColumns * 100, model->tableRows * 100);

    for(int i = 1; i < model->tableRows; ++i) {

        tableGraphics.append(QLineF(0, i*100, model->tableColumns * 100, i*100));
    }

    for(int i = 1; i < model->tableColumns; ++i) {

        tableGraphics.append(QLineF(i*100, 0, i*100, model->tableRows * 100));
    }

    playerXGraphics.append(QLineF(20, 20, 80, 80));
    playerXGraphics.append(QLineF(20, 80, 80, 20));
    playerOGraphics = QRectF(20.0, 20.0, 60.0, 60.0);*/

    newGame(model->tableColumns, model->tableRows);

    connect(model, SIGNAL(fieldChanged(int,int,TicTacToeModel::Player)), this, SLOT(model_fieldChanged(int,int,TicTacToeModel::Player)));
    connect(model, SIGNAL(gameWon(TicTacToeModel::Player)), this, SLOT(model_GameWon(TicTacToeModel::Player)));
    connect(model, SIGNAL(gameOver()), this, SLOT(model_GameOver()));

    //model->newGame(model->tableColumns, model->tableRows);

}

TicTacToeWidget::~TicTacToeWidget()
{

}

void TicTacToeWidget::newGame(int c, int r) // Miért nem töltődik újra a mainwindow action, ha van paraméter??????
{

    model->newGame(c, r);

    if(c != model->tableColumns || r != model->tableRows) {

        c = model->tableColumns;
        r = model->tableRows;
    }

    setFixedSize(c * 100, r * 100);

    for(int i = 1; i < r; ++i) {

        tableGraphics.append(QLineF(0, i*100, c * 100, i*100));
    }

    for(int i = 1; i < c; ++i) {

        tableGraphics.append(QLineF(i*100, 0, i*100, r * 100));
    }

    playerXGraphics.append(QLineF(20, 20, 80, 80));
    playerXGraphics.append(QLineF(20, 80, 80, 20));
    playerOGraphics = QRectF(20.0, 20.0, 60.0, 60.0);


    update();
}

void TicTacToeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::red);
    painter.drawLines(tableGraphics);

    for(int i = 0; i < model->tableColumns; i++)
    {
        for(int j = 0; j < model->tableRows; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate(i * model->tableRows * 100.0 / model->tableRows , j * model->tableColumns * 100.0 / model->tableColumns); // elmozdítjuk a rajzpontot a megfelelő mezőre

            // mező kirajzolása a játékos függvényében
            switch (model->getField(i, j))
            {
            case TicTacToeModel::XPlayer:
                painter.setPen(QPen(Qt::blue, 4)); // toll beállítása
                painter.drawLines(playerXGraphics); // megfelelõ grafika kirajzolása
                break;
            case TicTacToeModel::OPlayer:
                painter.setPen(QPen(Qt::black, 2)); // toll beállítása
                painter.drawEllipse(playerOGraphics);
                break;
            }
            painter.restore(); // visszatöltjük a korábbi állapotot
        }
    }

    ///játékosok grafikája jöjjön ide, de azelőtt definiálni kell a modellt és az adatelérést, mivel a játékosokat majd az update segítségével rajzoljuk ki minden mezőváltozás után.
}

void TicTacToeWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x() * model->tableColumns / width();
    int y = event->pos().y() * model->tableRows / height();

    model->stepGame(x,y);
}

void TicTacToeWidget::setSave()
{
    if (saveGameWidget == NULL) // ha még egyszer sem nyitották meg az ablakot
    {
        saveGameWidget = new SaveWidget;
        connect(saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
    }

    // beállítjuk a listát, és megnyitjuk az ablakot
    saveGameWidget->setGameList(model->saveGameList());
    saveGameWidget->open();
}

void TicTacToeWidget::saveGame()
{
    if (model->saveGame(saveGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, trUtf8("Tic-Tac-Toe"), trUtf8("Játék sikeresen mentve!"));
    }

    else

    {
        QMessageBox::warning(this, trUtf8("Tic-Tac-Toe"), trUtf8("A játék mentése sikertelen!"));
    }
}

void TicTacToeWidget::setLoad()
{
    if (loadGameWidget == NULL) // ha még egyszer sem nyitották meg az ablakot
    {
        loadGameWidget = new LoadWidget;
        connect(loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
    }

    // beállítjuk a listát, és megnyitjuk az ablakot
    loadGameWidget->setGameList(model->saveGameList());
    loadGameWidget->open();
}

void TicTacToeWidget::loadGame()
{
    if (model->loadGame(loadGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, trUtf8("JTic-Tac-Toe"), trUtf8("Játék betöltve, következik: ") + ((model->current == TicTacToeModel::XPlayer) ? "X" : "O") + "!");
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Tic-Tac-Toe"), trUtf8("A játék betöltése sikertelen!"));
    }
}

void TicTacToeWidget::model_fieldChanged(int x, int y, TicTacToeModel::Player player)
{
    update();
}

void TicTacToeWidget::model_GameWon(TicTacToeModel::Player winner)
{
    switch (winner)
    {

    case TicTacToeModel::XPlayer:

        QMessageBox::information(this, trUtf8("Potyogós amőba"), trUtf8("Játék vége! Az X nyerte a játékot!"));
        //model->newGame(model->tableColumns, model->tableRows);
        newGame(model->tableColumns, model->tableRows);
        break;

    case TicTacToeModel::OPlayer:

        QMessageBox::information(this, trUtf8("Potyogós amőba"), trUtf8("Játék vége! A O nyerte a játékot!"));
        model->newGame(model->tableColumns, model->tableRows);
        break;
    }
}

void TicTacToeWidget::model_GameOver()
{
    QMessageBox::information(this, trUtf8("Potyogós amőba"), trUtf8("Játék vége! A játék döntetlen lett!"));
    model->newGame(model->tableColumns, model->tableRows);
}
