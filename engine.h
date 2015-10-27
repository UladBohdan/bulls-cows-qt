#ifndef ENGINE_H
#define ENGINE_H

#include <QMessageBox>
#include <QPair>
#include <QQueue>
#include <QString>
#include <QTime>

#define USERG_WRONG_LENGTH 30
#define USERG_REPEATED_DIGITS 31
#define USERG_NOT_NUMBER 32

#define COMPG_NO_SOLUTIONS 40
#define COMPG_WRONG_BC_VALUES 41

class Engine : public QObject
{
public:
    Engine();

    void guessNumber(int);
    void init(int);
    void setBullsCows(int,int);

    int getLength();
    int solutionSize();

    QPair<int,int> processUserGuess(QString);
    QString getNextValue();

private:
    bool check(QString, QString, int, int);
    QString getNextString(QString);

    int len, bulls, cows;
    long long finalInt;
    QQueue <QString> q;
    QString guessedByComputer, currString;
};

#endif // ENGINE_H
