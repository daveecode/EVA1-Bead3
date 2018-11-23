#include "savewidget.h"

SaveWidget::SaveWidget(QWidget *parent) : QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle(trUtf8("Potyogós amőba - Játék mentése"));

    listWidget = new QListWidget;
    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton(trUtf8("Mégse"));

    buttons = new QHBoxLayout;
    buttons->addWidget(okButton);
    buttons->addWidget(cancelButton);

    main = new QVBoxLayout;
    main->addWidget(listWidget);
    main->addLayout(buttons);

    setLayout(main);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void SaveWidget::setGameList(QVector<QString> saveGameList)
{
    listWidget->clear();

    for (int i = 0; i < 5; i++)
    {
        if (i < saveGameList.size() && !saveGameList[i].isEmpty())
            listWidget->addItem(saveGameList[i]);
        else
            listWidget->addItem("üres");
    }
}

int SaveWidget::selectedGame() const
{
    listWidget->currentRow();
}
