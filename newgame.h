#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class NewGame;
}

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = 0, QString title = "Creating new game");
    ~NewGame();
    static bool opened;
    static NewGame* newGameDlg;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::NewGame *ui;
public:
    int value;
};

#endif // NEWGAME_H
