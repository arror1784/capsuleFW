#include "keyboardsymbols.h"

QList<QString> KeyboardSymbols::getDigits()
{
    return {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",};
}

QList<QString> KeyboardSymbols::getEnglishSpecialSymbols()
{
    return {"!", "@", "#", "$", "%", "^", "&&", "*", "(", ")",};
}

QList<QString> KeyboardSymbols::getNonCapsLastSymbols()
{
    return {",", ".", "/"};
}

QList<QString> KeyboardSymbols::getCapsLastSymbols()
{
    return {"-", "_", "\\"};
}

QList<QString> KeyboardSymbols::getRussianSpecialSymbols()
{
    return {"!", "\"", "№", ";", "%", ":", "?", "*", "(", ")",};
}
