#include "loadwidget.h"
#include <QMessageBox>

LoadWidget::LoadWidget(QWidget *parent) : SaveWidget(parent)
{
    setWindowTitle(trUtf8("Potyogós amőba - Játék betöltése"));

    disconnect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(Clicked()));
}

void LoadWidget::Clicked()
{
    if (listWidget->currentItem()->text() == "üres")
    {
        QMessageBox::warning(this, trUtf8("Potyogós amőba"), trUtf8("Nincs játék kiválasztva!"));
        return;
    }

    accept();
}
