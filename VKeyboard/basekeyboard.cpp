#include "basekeyboard.h"

#include "keyboardsymbols.h"

static constexpr int lastNonAlphabetSymbolsCount = 3;

BaseKeyboard::BaseKeyboard ( QWidget * parent ) : QFrame ( parent )
{
}

BaseKeyboard::~BaseKeyboard()
{
}

void BaseKeyboard::keyPressed ( const QString & text )
{
    if ( text.length() == CHAR ) {
        emit charKeyPressed ( text );
    } else if ( text.length() == CAPS ) {
        emit capsKeyPressed();
    } else if ( text.length() == LANG ) {
        emit switchLangPressed();
    } else {
        emit charKeyPressed ( text );
    }
}

void BaseKeyboard::invertCaps()
{
    invertLetters();
    invertAlphabetEnding();
    m_isUpper = !m_isUpper;
}

void BaseKeyboard::setButtonList ( const QList<QPushButton *> & pButtonList )
{
    m_buttonList = pButtonList;
    setConnections();
}

void BaseKeyboard::setUpperState ( bool isUpper )
{
    m_isUpper = isUpper;
}

void BaseKeyboard::setConnections()
{
    for ( auto i = 0; i < m_buttonList.size(); ++i ) {
        connect ( m_buttonList.at ( i ), &QPushButton::clicked, [ = ] {
                keyPressed ( m_buttonList.at ( i )->text() );
        } );
    }

    connect ( this, SIGNAL ( capsKeyPressed() ), SLOT ( invertCaps() ) );
}

void BaseKeyboard::invertLetters()
{
    QString text;

    for ( auto i = 0; i < m_buttonList.size(); ++i ) {
        if ( m_buttonList.at ( i )->text().length() == CHAR ) {
            if ( m_isUpper ) {
                text = m_buttonList[i]->text().toLower();
                m_buttonList[i]->setText ( text );
            } else {
                text = m_buttonList[i]->text().toUpper();
                m_buttonList[i]->setText ( text );
            }
        }
    }
}

void BaseKeyboard::invertAlphabetEnding()
{
    auto j = 0;
    auto i = m_buttonList.size() - lastNonAlphabetSymbolsCount;
    QList<QString> lastCapsSymbols = KeyboardSymbols::getCapsLastSymbols();
    QList<QString> lastNonCapsSymbols = KeyboardSymbols::getNonCapsLastSymbols();

    for ( ; i < m_buttonList.size(); ++i ) {
        if ( m_isUpper ) {
            m_buttonList[i]->setText ( lastNonCapsSymbols.at ( j ) );
            ++j;
        } else {
            m_buttonList[i]->setText ( lastCapsSymbols.at ( j ) );
            ++j;
        }
    }
}
