#include "loadwidget.h"
#include <QMessageBox>

LoadWidget::LoadWidget(QWidget *parent) : SaveWidget(parent)
{
    setWindowTitle(trUtf8("Potyogós amőba - Játék betöltése"));

    // ellenőrzést is végzünnk az OK gomb lenyomására
    disconnect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(Clicked()));
}

void LoadWidget::Clicked()
{
    if (listWidget->currentItem()->text() == "üres")
    {
        // ha üres mezőt választott, akkor nem engedjük tovább
        QMessageBox::warning(this, trUtf8("Potyogós amőba"), trUtf8("Nincs játék kiválasztva!"));
        return;
    }

    accept(); // különben elfogadjuk a dialógust
}
