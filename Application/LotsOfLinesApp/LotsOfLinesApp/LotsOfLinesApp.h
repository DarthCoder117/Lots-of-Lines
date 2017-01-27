#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LotsOfLinesApp.h"

class LotsOfLinesApp : public QMainWindow
{
    Q_OBJECT

public:
    LotsOfLinesApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::LotsOfLinesAppClass ui;
};
