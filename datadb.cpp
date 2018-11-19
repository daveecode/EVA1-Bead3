#include "datadb.h"
#include <QVariant>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

DataDb::DataDb()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setDatabaseName("game");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("root");

    database.open();
}

DataDb::~DataDb()
{
    QSqlDatabase::database().close();
}

bool DataDb::isAvailable() const
{
    return QSqlDatabase::database().isOpen();
}

QVector<QString> DataDb::saveGameList() const
{
    QVector<QString> result(5);

    QSqlQuery query;
    query.exec("select id, saveTime from games"); // adatbázisban futtatjuk a lekérdezést a sorszámra és a dátumra

    while (query.next())
    {
        result[query.value(0).toInt()] = "[" + query.value(0).toString() + "] " + query.value(1).toString();
    }

    return result;
}

bool DataDb::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QSqlQuery query;
    query.exec("select stepCount, currentPlayer, tableData from games where id = " + QString::number(gameIndex));

    if (!query.next()) // ha nincs eredmény, akkor nincs ilyen mentés
        return false;

    saveGameData.resize(42);

    // betöltjük a mentés egyes elemeit
    saveGameData[0] = query.value(0).toInt();
    saveGameData[1] = query.value(1).toInt();

    for (int i = 0; i < 40; i++)
        saveGameData[i + 2] = query.value(2).toString()[i].toLatin1();

    return true;
}

bool DataDb::saveGame(int gameIndex, const QVector<int> &saveGameData)
{
    QSqlQuery query;

    // kitötöljük a korábbi játékállást (ha volt)
    query.exec("remove from game where id = " + QString::number(gameIndex));

    QString tableData; // a tábal kitöltését egy adatként mentjük el
    for (int i = 2; i < 42; i++)
        tableData += QChar::fromLatin1(saveGameData[i]);

    // beszúrjuk az adatokat
    return query.exec("insert into games (id, saveTime, stepCount, currentPlayer, tableData) values(" +
                      QString::number(gameIndex) + ",'" + QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss") + "'," +
                      QString::number(saveGameData[0]) + "," + QString::number(saveGameData[1]) + ",'" + tableData + "'");
}
