#ifndef TICTACTOEDATA_H
#define TICTACTOEDATA_H

#include <QVector>
#include <QString>

class TicTacToeData // az adatelérés típusa (absztrakt osztály)
{
public:
    TicTacToeData() { }
    virtual ~TicTacToeData() { }

    virtual bool isAvailable() const { return false; } // rendelkezésre állás lekérdezése
    virtual QVector<QString> saveGameList() const = 0; // mentett játékok lekérdezése

    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0; // játék betöltése
    virtual bool saveGame(int gameIndex, const QVector<int> &saveGameData) = 0; // játék mentése
};

#endif // TICTACTOEDATA_H
