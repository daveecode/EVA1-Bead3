#ifndef DATAUI_H
#define DATAUI_H

#include <QVector>

class DataUi
{

public:

    DataUi() {}
    virtual ~DataUi() {}

    virtual bool isAvailable() const { return false; }
    virtual QVector<QString> saveGameList() const = 0;
    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0;
    virtual bool saveGame(int gameIndex, const QVector<int> &saveGameData) = 0;
};

#endif // DATAUI_H
