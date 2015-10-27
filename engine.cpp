#include "engine.h"

Engine::Engine()
{
    init(4);
}

void Engine::init(int _len)
{
    len=_len;
    finalInt=0;
    for (int i=9; i>9-len; i--)
        finalInt=finalInt*10+i;
    if (len==10)
        finalInt*=10;
    currString="begin";

    q.clear();
    QString str;
    str+="10";
    for (int i=0; i<len-2; i++)
        str+=('2'+i);
    q.push_back(str);
    do
        q.push_back(getNextString(q.back()));
    while (q.back()!="-");
}

int Engine::getLength()
{
    return len;
}

void Engine::setBullsCows(int _bulls, int _cows)
{
    if (_bulls+_cows>len || (_bulls==len-1 && _cows==1))
        throw COMPG_WRONG_BC_VALUES;
    bulls=_bulls;
    cows=_cows;
}

int Engine::solutionSize()
{
    return q.size()-1;
}

QString Engine::getNextValue()
{
    if (currString!="begin")
    {
        while (q.front()!="-")
        {
            if ( check(q.front(),currString,bulls,cows) )
                q.push_back(q.front());
            q.pop_front();
        }
        q.pop_front();
        q.push_back("-");
    }
    if (q.front()=="-")
        throw COMPG_NO_SOLUTIONS;
    qsrand(QTime::currentTime().msec());
    currString=q[qrand()%(q.size()-1)];
    return currString;
}

bool Engine::check(QString a, QString b, int _bulls, int _cows)
{
    _cows+=_bulls;
    for (int i=0; i<len; i++)
        if (a[i]==b[i])
            _bulls--;
    if (_bulls!=0)
        return false;
    int temp[10]={};
    for (int i=0; i<len; i++)
    {
        temp[a[i].toLatin1()-'0']++;
        temp[b[i].toLatin1()-'0']++;
    }
    for (int i=0; i<10; i++)
        if (temp[i]==2)
            _cows--;
    if (_cows!=0)
        return false;
    return true;
}

QString Engine::getNextString(QString str)
{
    // Returns "-" if it's impossible to get the next value
    int temp=str.toInt()+1;
    while (true)
    {
        bool fine=true;
        if (temp==finalInt)
            return "-";
        int x=temp, arr[10]={};
        while (x!=0)
        {
            arr[x%10]++;
            x/=10;
        }
        for (int i=0; i<10; i++)
            if (arr[i]>1)
            {
                temp++;
                i=10;
                fine=false;
            }
        if (fine)
            return QString::number(temp);
    }
}

void Engine::guessNumber(int _len)
{
    init(_len);
    guessedByComputer=getNextValue();
}

QPair<int,int> Engine::processUserGuess(QString users)
{
    for (int i=0; i<users.length(); i++)                    // not a number
        if (users[i]<QChar('0') || users[i]>QChar('9'))
            throw USERG_NOT_NUMBER;

    if (users.length()!=len || users[0]==QChar('0'))            // if number has wrong size
        throw USERG_WRONG_LENGTH;

    int digits[10]={};                    // if number has more than one same digits
    for (int i=0; i<len; i++)
        digits[users[i].toLatin1()-'0']++;
    for (int i=0; i<10; i++)
        if (digits[i]>1)
            throw USERG_REPEATED_DIGITS;

    QPair<int,int> temp(0,0);
    for (int i=0; i<len; i++)
        if (users[i]==guessedByComputer[i])
            temp.first++;
    for (int i=0; i<len; i++)
        if (digits[guessedByComputer[i].toLatin1()-'0']==1)
            temp.second++;
    temp.second-=temp.first;
    return temp;
}
