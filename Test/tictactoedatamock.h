#ifndef TICTACTOEDATAMOCK_H
#define TICTACTOEDATAMOCK_H
#include "tictactoedata.h"

class TicTacToeDataMock : public TicTacToeData
{
    bool isAvailable() const { return true; }

    QVector<QString> saveGameList() const
    {
        return QVector<QString>(5);
    }

    bool loadGame(int gameIndex, QVector<int> &saveGameData)
    {
        //saveGameData.resize(11); // minden érték 0 lesz
        saveGameData[1] = 1; // kivéve a rákövetkező játékos

        qDebug() << "game loaded to slot (" << gameIndex << ") with values: ";
        for (int i = 0; i < 11; i++)
            qDebug() << saveGameData[i] << " ";
        qDebug() << endl;

        return true;
    }

    bool saveGame(int gameIndex, const QVector<int> &saveGameData)
    {
        qDebug() << "game saved to slot (" << gameIndex << ") with values: ";
        for (int i = 0; i < 11; i++)
            qDebug() << saveGameData[i] << " ";
        qDebug() << endl;

        return true;
    }
};

#endif // TICTACTOEDATAMOCK_H
