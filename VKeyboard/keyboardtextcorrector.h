#ifndef KEYBOARD_TEXT_CORRECTOR_H
#define KEYBOARD_TEXT_CORRECTOR_H

#include <QString>

class KeyboardTextCorrector {
public:
    static QString performKeyboardTextCorrection ( const QString & text );

private:
    static void checkForDoubleAmpersand();
    static void checkForSpaceKey();

    static QString m_textBuffer;
};

#endif // KEYBOARD_TEXT_CORRECTOR_H
