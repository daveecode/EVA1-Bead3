#include "tictactoemodel.h"

TicTacToeModel::TicTacToeModel(DataUi *dataAccess, int columns, int rows)
{

    _dataAccess = dataAccess;
    tableColumns = columns;
    tableRows = rows;

    gameTable = new Player*[tableColumns];

    for(int i = 0; i < tableColumns; ++i) {

        gameTable[i] = new Player[tableRows];
    }
}

TicTacToeModel::~TicTacToeModel()
{
    delete[] gameTable;
}

void TicTacToeModel::newGame(int c, int r)
{

    if(tableColumns != c || tableRows != r) {

        delete[] gameTable;
        tableColumns = c;
        tableRows = r;

        gameTable = new Player*[tableColumns];

        for(int i = 0; i < tableColumns; ++i) {

            gameTable[i] = new Player[tableRows];
        }
    }

    for(int i = 0; i < tableColumns; ++i) {

        for(int j = 0; j < tableRows; ++j) {

            gameTable[i][j] = TicTacToeModel::NoPlayer;
        }
    }

    steps = 0;
    current = TicTacToeModel::XPlayer;
}

void TicTacToeModel::stepGame(int x, int y)
{
    if(steps >= tableColumns * tableRows) {

        return;
    }


    if(getField(x,y) == TicTacToeModel::None) {

        return;
    }

    if(gameTable[x][y] != 0) {

        return;
    }

    /*gameTable[x][y] = current;
    fieldChanged(x,y,current);
    current = (Player)(current % 2 + 1);
    steps++;*/

    for(int i = tableRows - 1; i > -1; --i) {

        if(getField(x,i) == TicTacToeModel::NoPlayer) {

            gameTable[x][i] = current;
            fieldChanged(x,i, current);
            steps++;
            current = (Player)(current % 2 + 1);
            checkGame();
            return;
        }
    }
}

void TicTacToeModel::checkGame()
{
    TicTacToeModel::Player winner = TicTacToeModel::NoPlayer;

    int n = 0;

    while(n < tableRows) {

        for(int i = 0; i < tableColumns; ++i) {

            if(getField(i,n) != TicTacToeModel::NoPlayer && getField(i,n) == getField(i+1,n) && getField(i,n) == getField(i+2,n) && getField(i,n) == getField(i+3,n)) {

                winner = getField(i,n);
            }
        }

        n++;
    }

    if(winner != TicTacToeModel::NoPlayer) {

        gameWon(winner);
    }

    if(steps >= tableColumns * tableRows) {

        gameOver();
    }

}

TicTacToeModel::Player TicTacToeModel::getField(int x, int y) const
{
    if(x < 0 || x > tableColumns - 1 || y < 0 || y > tableRows - 1) {

        return TicTacToeModel::None;
    }

    return gameTable[x][y];
}

bool TicTacToeModel::loadGame(int gameIndex)
{
    if(_dataAccess == NULL || !_dataAccess->isAvailable()) {

        return false;
    }

    QVector<int> saveGameData;

    if(!_dataAccess->loadGame(gameIndex, saveGameData)) {

        return false;
    }

    steps = saveGameData[0];
    current = (Player)saveGameData[1];

    for(int i = 0; i < tableColumns; ++i) {

        for(int j = 0; j < tableRows; ++j) {

            gameTable[i][j] = (Player)saveGameData[2+i*tableColumns+j];
        }
    }

    return true;
}

bool TicTacToeModel::saveGame(int gameIndex)
{
    if (_dataAccess == NULL || !_dataAccess->isAvailable()) // ellenőrizzük az adatelérést
        return false;

    QVector<int> saveGameData;

    saveGameData.push_back(steps);
    saveGameData.push_back((int)current);

    for(int i = 0; i < tableColumns; ++i) {

        for(int j = 0; j < tableRows; ++j) {

            saveGameData.push_back((int)gameTable[i][j]);
        }
    }

    return _dataAccess->saveGame(gameIndex, saveGameData);
}

QVector<QString> TicTacToeModel::saveGameList() const
{
    return _dataAccess->saveGameList();
}
