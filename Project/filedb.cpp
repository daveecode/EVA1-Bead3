#include "filedb.h"
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>

FileDb::FileDb()
{

}

FileDb::~FileDb()
{

}

bool FileDb::isAvailable() const
{
    return true;
}

QVector<QString> FileDb::saveGameList() const
{
    QVector<QString> result(5);

    for (int i = 0; i < 5; i++)
    {
        if (QFile::exists("game" + QString::number(i) + ".sav"))
        {
            QFileInfo info("game"+ QString::number(i) + ".sav");
            result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
        }
    }

    return result;
}

bool FileDb::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    for (int i = 0; i < saveGameData.size(); i++)
        saveGameData[i] = stream.readLine().toInt();

    file.close();

    return true;
}

bool FileDb::saveGame(int gameIndex, const QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);

    for (int i = 0; i < saveGameData.size(); i++)
        stream << saveGameData[i] << endl;

    file.close();

    return true;
}
