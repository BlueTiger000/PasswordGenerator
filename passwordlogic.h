#include <QObject>
#include <string>
#include <QDebug>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <iostream>
#include <windows.h>
#ifndef PASSWORDLOGIC_H
#define PASSWORDLOGIC_H

#endif // PASSWORDLOGIC_H

class PasswordGenerator{
private:
    QString characterPool;
    int lenght;
    QString password;
    bool capital_letters{false};
    bool lowercase_letters{false};
    QRandomGenerator *randomGenerator = QRandomGenerator::global();
public:
    QString PasswordGenerating(int lenght, bool capital_letters, bool lowercase_letters, bool numbers, bool spec);
};
