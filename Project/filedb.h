#ifndef FILEDB_H
#define FILEDB_H
#include "dataui.h"


class FileDb : public TicTacToeData
{

public:

    FileDb();
    ~FileDb();

    bool isAvailable() const;
    QVector<QString> saveGameList() const;
    bool loadGame(int gameIndex, QVector<int> &saveGameData);
    bool saveGame(int gameIndex, const QVector<int> &saveGameData);
};

#endif // FILEDB_H
