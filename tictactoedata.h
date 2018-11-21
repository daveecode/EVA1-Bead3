#ifndef TICTACTOEDATA_H
#define TICTACTOEDATA_H

#include <QVector>
#include <QString>

class TicTacToeData
{

public:

    TicTacToeData();

    QVector<QString> saveGameList() const; // mentett játékok lekérdezése

    bool loadGame(int gameIndex, QVector<int> &saveGameData); // játék betöltése
    bool saveGame(int gameIndex, const QVector<int> &saveGameData); // játék mentése
};

#endif // TICTACTOEDATA_H
