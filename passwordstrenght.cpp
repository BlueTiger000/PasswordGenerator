#include "passwordstrenght.h"
#include <cmath>

QString PasswordStrenght:: Strenght(QString password){
    int L = password.length();
    int N = 0;

    bool hasLower = password.contains(QRegularExpression("[a-z]"));
    bool hasUpper = password.contains(QRegularExpression("[A-Z]"));
    bool hasDigit = password.contains(QRegularExpression("[0-9]"));
    bool hasSpecial = password.contains(QRegularExpression("[^a-zA-Z0-9]"));

    //Определяю N искодя из количества символов в пуле
    if (hasLower) N += 26;
    if (hasUpper) N += 26;
    if (hasDigit) N += 10;
    if (hasSpecial) N += 27;

    double entropy = L*std::log2(N);
    qDebug() << "Энтропия:" << entropy;

    //Оценка надежности
    if (entropy > 100) return "Очень надежный";
    if (entropy >= 60) return "Надежный";
    if (entropy >= 40) return "Средний";
    if (entropy >= 20) return "Слабый";
    return "Очень слабый";
}
