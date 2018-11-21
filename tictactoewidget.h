#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H
#include "tictactoemodel.h"
#include "tictactoedata.h"
#include "savewidget.h"
#include "loadwidget.h"
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPainter>
#include <QMouseEvent>

class TicTacToeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToeWidget(QWidget *parent = nullptr);
    ~TicTacToeWidget();

protected:

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

public slots:

    void newGame(int c, int r);
    void saveGame();
    void loadGame();
    void setSave();
    void setLoad();

private slots:

    void model_GameWon(TicTacToeModel::Player winner);
    void model_GameOver();
    void model_fieldChanged(int x, int y, TicTacToeModel::Player player);

private:

    QVector<QLineF> tableGraphics; // tábla grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> playerXGraphics;
    QRectF playerOGraphics;

    QLabel *_first;
    QLabel *_second;
    QHBoxLayout *labels;

    TicTacToeModel *model;
    TicTacToeData *data;
    SaveWidget *saveGameWidget;
    LoadWidget *loadGameWidget;

};

#endif // TICTACTOEWIDGET_H
