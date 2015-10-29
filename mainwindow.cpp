#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->userGuessWidget->hide();
    ui->computerGuessWidget->hide();
    LISTOUT(tr("Welcome!"));
    LISTOUT(tr("Go to \"Game\" to start a new game."));
    LISTOUT(tr("Good luck!"));
    status = new QLabel(tr("Go to \"Game\"."));
    ui->statusBar->addWidget(status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitButton_clicked()
{
    try
    {
        bool ok=true;
        game.setBullsCows(ui->bullsNum->text().toInt(&ok), ui->cowsNum->text().toInt(&ok));
        if (!ok)
            throw COMPG_WRONG_BC_VALUES;
        LISTOUT(ui->mainLabel->text()+"  :  "+ui->bullsNum->text()+tr(" bulls, ")+
                ui->cowsNum->text()+tr(" cows."));
        ui->bullsNum->clear();
        ui->cowsNum->clear();
        ui->bullsNum->setFocus();
        nextStep();
    }
    catch (int e)
    {
        switch (e)
        {
        case COMPG_WRONG_BC_VALUES:
            LISTOUT(tr("Impossible number of bulls and cows. Try again."));
            break;
        }
    }
    ui->historyList->scrollToBottom();
}

void MainWindow::on_actionComputerGuesses_triggered()
{
    if (NewGame::opened)
        NewGame::newGameDlg->activateWindow();
    else
    {
        NewGame dlg(this,tr("Length for Computer-Guessing mode"));
        if (dlg.exec()==QDialog::Accepted)
        {
            ui->computerGuessWidget->show();
            ui->userGuessWidget->hide();
            status->setText(tr("Mode: Computer is guessing your number."));
            ui->historyList->clear();
            ui->bullsNum->clear();
            ui->cowsNum->clear();
            game.init(dlg.value);
            ui->bullsNum->setFocus();
            ui->submitButton->setEnabled(true);
            nextStep();
        }
    }
}

void MainWindow::nextStep()
{
    try
    {
        QString temp=game.getNextValue();
        if (game.solutionSize()==1)
        {
            LISTOUT(tr("Oh, I know the answer! It's ")+temp.right(game.getLength()));
            ui->mainLabel->setText(temp.right(game.getLength()));
            ui->solutCountLabel->setText(tr("The only suitable answer!"));
            ui->submitButton->setEnabled(false);
        }
        else
        {
            ui->mainLabel->setText(temp);
            ui->solutCountLabel->setText(tr("There're ")+QString::number(game.solutionSize())+tr(" suitable solutions!"));
        }
    }
    catch (int e)
    {
        switch (e)
        {
        case COMPG_NO_SOLUTIONS:
            LISTOUT(tr("Something went wrong:( There're no suitable solutions."));
            ui->mainLabel->setText(tr("Mistake"));
            ui->solutCountLabel->setText(tr("No suitable solutions"));
            ui->submitButton->setEnabled(false);
            break;
        }
    }
    ui->historyList->scrollToBottom();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionRules_triggered()
{
    if (Rules::opened)
        Rules::rulesDlg->activateWindow();
    else
    {
        Rules dlg;
        dlg.exec();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    if (About::opened)
        About::aboutDlg->activateWindow();
    else
    {
        About dlg;
        dlg.exec();
    }
}

void MainWindow::on_actionUserGuessing_triggered()
{
    if (NewGame::opened)
        NewGame::newGameDlg->activateWindow();
    else
    {
        NewGame dlg(this,tr("Length for User-Guessing mode"));
        if (dlg.exec()==QDialog::Accepted)
        {
            ui->computerGuessWidget->hide();
            ui->userGuessWidget->show();
            status->setText("Mode: You are guessing a number");
            ui->historyList->clear();
            ui->userGuessString->clear();
            game.guessNumber(dlg.value);
            ui->userGuessString->setFocus();
            LISTOUT(tr("Make a guess what the number is!\nLength is ")+QString::number(game.getLength()));
            ui->historyList->scrollToBottom();
        }
    }
}

void MainWindow::on_processUserGuessButton_clicked()
{
    try
    {
        QPair<int,int> temp=game.processUserGuess(ui->userGuessString->text());
        if (temp.first==game.getLength())
        {
            LISTOUT(tr("Well done! Yes, ")+ui->userGuessString->text()+tr(" was a number I've guessed!"));
            LISTOUT(tr("You may start a new game or continue making queries for already guessed number."));
            LISTOUT(tr("Just for fun:)"));
        }
        else
            LISTOUT(ui->userGuessString->text()+"  :  "+QString::number(temp.first)+tr(" bulls, ")+
                                                       QString::number(temp.second)+tr(" cows."));
    }
    catch (int e)
    {
        switch (e)
        {
        case USERG_WRONG_LENGTH:
            LISTOUT(tr("WRONG: Your number should have length ")+QString::number(game.getLength()));
            break;
        case USERG_REPEATED_DIGITS:
            LISTOUT(tr("WRONG: Remember, that your number cannot consist more than one same digits"));
            break;
        case USERG_NOT_NUMBER:
            LISTOUT(tr("WRONG: It's not a number at all!"));
            break;
        }
    }
    ui->userGuessString->clear();
    ui->userGuessString->setFocus();
    ui->historyList->scrollToBottom();
}
