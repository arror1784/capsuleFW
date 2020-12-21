#include "keyboardtextcorrector.h"

QString KeyboardTextCorrector::m_textBuffer;

QString KeyboardTextCorrector::performKeyboardTextCorrection (
                const QString & text )
{
    m_textBuffer = text;
    checkForDoubleAmpersand();
    checkForSpaceKey();
    return m_textBuffer;
}

void KeyboardTextCorrector::checkForDoubleAmpersand()
{
    if ( m_textBuffer == "&&" ) {
        m_textBuffer = "&";
    }
}

void KeyboardTextCorrector::checkForSpaceKey()
{
    if ( m_textBuffer.size() > 2 ) {
        m_textBuffer = " ";
    }
}
