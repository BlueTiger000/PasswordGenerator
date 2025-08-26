#include "passwordlogic.h"


QString PasswordGenerator::PasswordGenerating(int lenght, bool capital_letters, bool lowercase_letters, bool numbers, bool spec){
    if (lowercase_letters) {
        characterPool += "abcdefghijklmnopqrstuvwxyz";
    }
    if (capital_letters) {
        characterPool += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    if (numbers) {
        characterPool += "0123456789";
    }
    if (spec) {
        characterPool += "!@#$%^&*()_+-=[]{}|;:,.<>?";
    }

    for (int i = 0; i < lenght; ++i) {
        int index = randomGenerator->bounded(characterPool.length());
        password.append(characterPool.at(index));
    }
    return password;
}
