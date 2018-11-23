#ifndef LOADWIDGET_H
#define LOADWIDGET_H
#include "savewidget.h"
#include <QWidget>

class LoadWidget : public SaveWidget
{
    Q_OBJECT

public:

    explicit LoadWidget(QWidget *parent = nullptr);

public slots:

    void Clicked();
};

#endif // LOADWIDGET_H
