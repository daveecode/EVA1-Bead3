#ifndef DATADB_H
#define DATADB_H
#include "dataui.h"

class DataDb : public DataUi
{
public:

    DataDb();
    ~DataDb();

    bool isAvailable() const;
    QVector<QString> saveGameList() const;
    bool loadGame(int gameIndex, QVector<int> &saveGameData);
    bool saveGame(int gameIndex, const QVector<int> &saveGameData);
};

#endif // DATADB_H
