#include "about.h"
#include "ui_about.h"

bool About::opened=false;
About* About::aboutDlg=NULL;

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    aboutDlg=this;
    opened=true;
}

About::~About()
{
    opened=false;
    delete ui;
}

void About::on_pushButton_clicked()
{
    this->accept();
}
