#ifndef TICTACTOEMODEL_H
#define TICTACTOEMODEL_H

#include <QObject>
#include "dataui.h"

class TicTacToeModel : public QObject
{
    Q_OBJECT

public:

    enum Player { NoPlayer, XPlayer, OPlayer, None };

    explicit TicTacToeModel(TicTacToeData *data, int columns = 8, int rows = 5);
    virtual ~TicTacToeModel(); //nem feltétlen kell definiálni

    void newGame(int c, int r);
    void stepGame(int x, int y);
    bool loadGame(int gameIndex);
    bool saveGame(int gameIndex);
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
    void changeTable();

private:

    Player **gameTable;
    TicTacToeData *dataAccess;

    void checkGame();

};

#endif // TICTACTOEMODEL_H
