#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

using EloScore = int;
using IDPlayer = int;
using PositionClassification = int;

#include <QtWidgets/QMainWindow>
#include "ui_TFG_ELO_UI.h"
#include "TFG_ELO.h"
#include <QPushButton>
#include <QFileDialog>
#include <QIntValidator>
#include <QMessageBox>

class TFG_ELO_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit TFG_ELO_UI(QWidget *parent = 0);
   
private slots:
    void on_startButton_clicked();
    void on_directoryButton_clicked();

private:
    Ui::TFG_ELO_UIClass ui;

    bool checkEditsLineEmpty();
    bool checkEditsLineNumber();
};
