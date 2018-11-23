#include "configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setFixedSize(310, 200);
    setWindowTitle(trUtf8("Potyogós amőba - Beállítások"));

    firstPlayerLabel = new QLabel(trUtf8("Első játékos neve"), this);
    secondPlayerLabel = new QLabel(trUtf8("Második játékos neve"), this);
    firstLineEdit = new QLineEdit;
    secondLineEdit = new QLineEdit;

    player1 = new QHBoxLayout;
    player1->addWidget(firstPlayerLabel);
    player1->addWidget(firstLineEdit);

    player2 = new QHBoxLayout;
    player2->addWidget(secondPlayerLabel);
    player2->addWidget(secondLineEdit);

    box = new QComboBox(this);
    box->addItem(trUtf8("Válaszd ki a játéktábla méretét! (oszlop x sor)"));
    box->addItem("8x5");
    box->addItem("10x6");
    box->addItem("12x7");

    okButton = new QPushButton(trUtf8("&Ok"), this);
    okButton->setEnabled(false);
    cancelButton = new QPushButton(trUtf8("&Mégse"), this);

    buttons = new QHBoxLayout;
    buttons->addWidget(okButton);
    buttons->addWidget(cancelButton);

    main = new QVBoxLayout;
    main->addLayout(player1);
    main->addLayout(player2);
    main->addWidget(box);
    main->addLayout(buttons);

    setLayout(main);

    connect(firstLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setFirstPlayerName()));
    connect(secondLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setSecondPlayerName()));
    connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(setSize()));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

QString ConfigDialog::firstPlayerName()
{
    return firstplayer;
}

QString ConfigDialog::secondPlayerName()
{
    return secondplayer;
}

int ConfigDialog::size()
{
    return box->currentIndex();
}

void ConfigDialog::setSize()
{
    if(size() == 1) {

       row = 5;
       col = 8;
    }

    else if(size() == 2) {

       row = 6;
       col = 10;
    }

    else if(size() == 3) {

       row = 7;
       col = 12;
    }

    else {

       // _model.tableColumns = 8;
       // _model.tableRows = 5;
    }

    isValid();
}

int ConfigDialog::columns()
{
    return col;
}

int ConfigDialog::rows()
{
    return row;
}

void ConfigDialog::setFirstPlayerName()
{
    firstplayer = firstLineEdit->text();
    isValid();
}

void ConfigDialog::setSecondPlayerName()
{
    secondplayer = secondLineEdit->text();
    isValid();
}

bool ConfigDialog::isValid()
{
    if(firstLineEdit->text().length() != 0 && secondLineEdit->text().length() != 0 && box->currentIndex() != 0) {

        okButton->setEnabled(true);
        return true;
    }

    else {

        return false;
    }
}
