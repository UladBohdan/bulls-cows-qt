#include "rules.h"
#include "ui_rules.h"

bool Rules::opened=false;
Rules* Rules::rulesDlg=NULL;

Rules::Rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rules)
{
    opened=true;
    rulesDlg=this;
    ui->setupUi(this);
}

Rules::~Rules()
{
    opened=false;
    delete ui;
}

void Rules::on_gotItButton_clicked()
{
    this->accept();
}
