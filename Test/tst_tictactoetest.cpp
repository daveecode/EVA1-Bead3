#include <QString>
#include <QtTest>
#include "tictactoemodel.h"
#include "tictactoedatamock.h"

class TicTacToeTest : public QObject
{
    Q_OBJECT


private:

    TicTacToeModel *model;
    TicTacToeData *data;

private slots:

    void initTestCase();
    void cleanupTestCase();
    void newGameTestCase();
    void stepGameTestCase();
    void saveGameTestCase();
    void loadGameTestCase();
};

void TicTacToeTest::initTestCase()
{
    data = new TicTacToeDataMock;
    model = new TicTacToeModel(data);
}

void TicTacToeTest::cleanupTestCase()
{
    delete model;
    delete data;
}

void TicTacToeTest::newGameTestCase()
{
    model->newGame(8,5);

    QVERIFY(model->tableColumns == 8);
    QVERIFY(model->tableRows == 5);

    for(int i = 0; i < 8; ++i) {

        for(int j = 0; j < 5; ++j) {

            QVERIFY(model->getField(i,j) == TicTacToeModel::NoPlayer);
        }
    }

    QCOMPARE(model->steps, 0);

    for(int i = 10; i < 50; ++i) {

        for(int j = 0; j < 5; ++j) {

            QVERIFY(model->getField(i,j) == TicTacToeModel::None);
        }
    }

    QVERIFY(model->current == TicTacToeModel::XPlayer);
}

void TicTacToeTest::stepGameTestCase()
{
    model->newGame(10,6);
    model->stepGame(0,0);

    QVERIFY(model->steps == 1);
    QCOMPARE(model->getField(0,0), TicTacToeModel::NoPlayer);
    QCOMPARE(model->getField(0,5), TicTacToeModel::XPlayer);
    QCOMPARE(model->current, TicTacToeModel::OPlayer);

    model->stepGame(2,2);

    QCOMPARE(model->getField(2,5), TicTacToeModel::OPlayer);

    model->stepGame(0,2);

    QVERIFY(model->getField(0,4) == TicTacToeModel::XPlayer);

}

void TicTacToeTest::saveGameTestCase()
{
    model->newGame(8,5);
    model->stepGame(1,3);
    model->stepGame(0,0);
    model->stepGame(3,4);
    model->stepGame(7,4);

    model->saveGame(0);

    QCOMPARE(model->steps, 4);
}

void TicTacToeTest::loadGameTestCase()
{
    model->newGame(8,5);

    model->stepGame(6,4);
    model->stepGame(1,2);

    model->loadGame(0);

    QCOMPARE(model->steps, 0);
    QCOMPARE(model->current, TicTacToeModel::XPlayer);
}

QTEST_APPLESS_MAIN(TicTacToeTest)

#include "tst_tictactoetest.moc"
