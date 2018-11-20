#ifndef SAVEWIDGET_H
#define SAVEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QLayout>
#include <QPushButton>

class SaveWidget : public QDialog
{
    Q_OBJECT

public:

    explicit SaveWidget(QWidget *parent = nullptr);
    void setGameList(QVector<QString> saveGameList); // a játékok betöltése
    int selectedGame() const; // a kiválasztott játék lekérdezése

protected:
    QPushButton *okButton;
    QPushButton *cancelButton;
    QListWidget *listWidget;

private:

    QHBoxLayout *buttons;
    QVBoxLayout *main;
};

#endif // SAVEWIDGET_H
