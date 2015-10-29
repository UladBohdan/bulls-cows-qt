#include "newgame.h"
#include "ui_newgame.h"

bool NewGame::opened=false;
NewGame* NewGame::newGameDlg=NULL;

NewGame::NewGame(QWidget *parent, QString title) :
    QDialog(parent),
    ui(new Ui::NewGame),
    value(5)
{
    opened=true;
    newGameDlg=this;
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->setLenEdit->setText(QString::number(value));
}

NewGame::~NewGame()
{
    opened=false;
    delete ui;
}

void NewGame::on_okButton_clicked()
{
    bool ok=true;
    value=ui->setLenEdit->text().toInt(&ok);
    if (!ok || value<2 || value>7)
    {
        QMessageBox::warning(this,tr("Mistake!"),tr("Something went wrong! Check the value."));
        ui->setLenEdit->clear();
        ui->setLenEdit->setFocus();
    }
    else
        this->accept();
}

void NewGame::on_cancelButton_clicked()
{
    this->reject();
}
