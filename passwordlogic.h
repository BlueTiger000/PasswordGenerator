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
    QString password;
    QRandomGenerator *randomGenerator = QRandomGenerator::global();
public:
    QString PasswordGenerating(QString pool, int lenght);
};
