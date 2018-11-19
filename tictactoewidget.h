#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H
#include "tictactoemodel.h"
#include "datadb.h"
#include <QWidget>
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

private slots:

    void model_GameWon(TicTacToeModel::Player winner);
    void model_GameOver();
    void model_fieldChanged(int x, int y, TicTacToeModel::Player player);

private:

    QVector<QLineF> tableGraphics; // tábla grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> playerXGraphics;
    QRectF playerOGraphics;

    TicTacToeModel *model;
    DataDb *data;

};

#endif // TICTACTOEWIDGET_H
