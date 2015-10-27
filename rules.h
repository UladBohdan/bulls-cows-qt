#ifndef RULES_H
#define RULES_H

#include <QDialog>

namespace Ui {
class Rules;
}

class Rules : public QDialog
{
    Q_OBJECT

public:
    explicit Rules(QWidget *parent = 0);
    ~Rules();
    static bool opened;
    static Rules* rulesDlg;

private slots:
    void on_gotItButton_clicked();

private:
    Ui::Rules *ui;
};

#endif // RULES_H
