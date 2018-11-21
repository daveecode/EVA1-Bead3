#ifndef TICTACTOEMODEL_H
#define TICTACTOEMODEL_H

#include <QObject>
#include "tictactoedata.h"

class TicTacToeModel : public QObject
{
    Q_OBJECT

public:

    enum Player { NoPlayer, XPlayer, OPlayer, None };

    explicit TicTacToeModel(int columns = 8, int rows = 5);
    virtual ~TicTacToeModel(); //nem feltétlen kell definiálni

    void newGame(int c, int r); //új játék létrehozása
    void stepGame(int x, int y); // játék léptetése
    bool loadGame(int gameIndex); // játék betöltése
    bool saveGame(int gameIndex); // játék mentése
    Player getField(int x, int y) const;
    QVector<QString> saveGameList() const;

    int steps;
    int tableColumns;
    int tableRows;
    Player current;

signals:

    void gameOver();
    void gameWon(TicTacToeModel::Player winner);
    void fieldChanged(int x, int y, TicTacToeModel::Player player);

private:

    Player **gameTable;
    TicTacToeData dataAccess;

    void checkGame();

};

#endif // TICTACTOEMODEL_H
