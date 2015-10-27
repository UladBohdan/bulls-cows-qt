#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define LISTOUT(str) ui->historyList->addItem(str)

#include <QMainWindow>
#include <QMessageBox>
#include <QPair>

#include "about.h"
#include "engine.h"
#include "newgame.h"
#include "rules.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_submitButton_clicked();

    void on_actionExit_triggered();

    void on_actionRules_triggered();

    void on_actionAbout_triggered();

    void on_actionComputerGuesses_triggered();

    void on_actionUserGuessing_triggered();

    void on_processUserGuessButton_clicked();

private:
    Ui::MainWindow *ui;
    Engine game;
    QLabel* status;

    void nextStep();
};

#endif // MAINWINDOW_H
