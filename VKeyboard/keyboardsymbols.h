#ifndef KEYBOARD_SYMBOLS_H
#define KEYBOARD_SYMBOLS_H

#include <QList>
#include <QString>

enum KeyType {
    CHAR = 1,
    LANG = 3,
    CAPS = 4
};

enum DigitsFrameType {
    Digits,
    EngSpecialSymbols,
    RusSpecialSymbols
};

class KeyboardSymbols {
public:

    static QList<QString> getDigits();
    static QList<QString> getNonCapsLastSymbols();
    static QList<QString> getCapsLastSymbols();

    static QList<QString> getEnglishSpecialSymbols();
    static QList<QString> getRussianSpecialSymbols();

};

#endif // KEYBOARD_SYMBOLS_H
