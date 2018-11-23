#ifndef TICTACTOEDATA_H
#define TICTACTOEDATA_H

#include <QVector>
#include <QString>

class TicTacToeData
{

public:

    TicTacToeData();

    QVector<QString> saveGameList() const;

    bool loadGame(int gameIndex, QVector<int> &saveGameData);
    bool saveGame(int gameIndex, const QVector<int> &saveGameData);
};

#endif // TICTACTOEDATA_H
