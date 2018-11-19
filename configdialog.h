#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
#include "tictactoemodel.h"
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QComboBox>

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:

    ConfigDialog(QWidget *parent = 0);

    QString firstPlayerName(); // első játékos neve
    QString secondPlayerName(); // második játékos neve
    int size();

public slots:

    void setFirstPlayerName();
    void setSecondPlayerName();
    void setSize();

private:

    QLabel *firstPlayerLabel;
    QLabel *secondPlayerLabel;
    QLineEdit *firstLineEdit;
    QLineEdit *secondLineEdit;
    QComboBox *box;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QString firstplayer;
    QString secondplayer;

    QHBoxLayout *player1;
    QHBoxLayout *player2;
    QHBoxLayout *buttons;

    QVBoxLayout *main;
    //TicTacToeModel _model;

    bool isValid();
};

#endif // CONFIGDIALOG_H
