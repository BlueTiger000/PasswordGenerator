#include "passwordlogic.h"


QString PasswordGenerator::PasswordGenerating(QString pool, int lenght){

    for (int i = 0; i < lenght; ++i) {
        int index = randomGenerator->bounded(pool.length());
        password += pool[index];
    }
    return password;
}
