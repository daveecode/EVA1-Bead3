#include "tictactoewidget.h"
#include "datadb.h"
#include <QMessageBox>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{

    setFixedSize(800, 500);
    /*tableGraphics.append(QLineF(0, 66, 200, 66));
    tableGraphics.append(QLineF(0, 132, 200, 132));
    tableGraphics.append(QLineF(0, 198, 200, 198));
    tableGraphics.append(QLineF(66, 0, 66, 200));
    tableGraphics.append(QLineF(132, 0, 132, 200));
    tableGraphics.append(QLineF(198, 0, 198, 200));*/

    data = new DataDb();
    model = new TicTacToeModel(data);

    for(int i = 1; i < 5; ++i) {

        tableGraphics.append(QLineF(0, i*100, 800, i*100));
    }

    for(int i = 1; i < 8; ++i) {

        tableGraphics.append(QLineF(i*100, 0, i*100, 500));
    }

    playerXGraphics.append(QLineF(20, 20, 80, 80));
    playerXGraphics.append(QLineF(20, 80, 80, 20));
    playerOGraphics = QRectF(20.0, 20.0, 60.0, 60.0);

    connect(model, SIGNAL(fieldChanged(int,int,TicTacToeModel::Player)), this, SLOT(model_fieldChanged(int,int,TicTacToeModel::Player)));
    connect(model, SIGNAL(gameWon(TicTacToeModel::Player)), this, SLOT(model_GameWon(TicTacToeModel::Player)));

    model->newGame();

}

TicTacToeWidget::~TicTacToeWidget()
{

}

void TicTacToeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::red);
    painter.drawLines(tableGraphics);

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate(i * 500.0 / 5 , j * 800.0 / 8); // elmozdítjuk a rajzpontot a megfelelő mezőre

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
    int x = event->pos().x() * 8 / width();
    int y = event->pos().y() * 5 / height();

    model->stepGame(x,y);
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
        QMessageBox::information(this, trUtf8("Tic-Tac-Toe"), trUtf8("Játék vége! Az X nyerte a játékot!"));
        model->newGame();
        break;
    case TicTacToeModel::OPlayer:
        QMessageBox::information(this, trUtf8("Tic-Tac-Toe"), trUtf8("Játék vége! A O nyerte a játékot!"));
        model->newGame();
        break;
    }
}

void TicTacToeWidget::model_GameOver()
{
    QMessageBox::information(this, trUtf8("Tic-Tac-Toe"), trUtf8("Játék vége! A játék döntetlen lett!"));
    model->newGame();
}
