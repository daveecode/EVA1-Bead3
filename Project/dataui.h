#ifndef TICTACTOEDATA_H
#define TICTACTOEDATA_H

#include <QVector>
#include <QString>

class TicTacToeData
{
public:

    TicTacToeData() { }
    virtual ~TicTacToeData() { }

    virtual bool isAvailable() const { return false; }
    virtual QVector<QString> saveGameList() const = 0;

    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0;
    virtual bool saveGame(int gameIndex, const QVector<int> &saveGameData) = 0;
};

#endif // TICTACTOEDATA_H
