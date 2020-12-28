#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QLineEdit>

#include "engkeyboard.h"
#include "ruskeyboard.h"
#include "keyboardtextcorrector.h"

#include <QDebug>

static constexpr short keyboard_width = 500;
static constexpr short keyboard_height = 150;

static constexpr short last_char = 1;

KeyboardWidget::KeyboardWidget ( QWidget * parent ) :
    QWidget ( parent ),
    ui ( new Ui::KeyboardWidget )
{
    setInitialSettings();
    setDefaultKeyboard();
    setConnections();

}

KeyboardWidget::~KeyboardWidget()
{
    delete ui;
}

void KeyboardWidget::switchKeyboard()
{
    m_pDigitsFrame->setFrameType ( Digits );
    m_pDigitsFrame->switchFrame();

    if ( m_pEngKeyboard->isHidden() ) {
        m_pRusKeyboard->hide();
        setFixedWidth ( m_pEngKeyboard->getOptimalParentWidgetWidth() );
        m_pEngKeyboard->show();
    } else {
        m_pEngKeyboard->hide();
        setFixedWidth ( m_pRusKeyboard->getOptimalParentWidgetWidth() );
        m_pRusKeyboard->show();
    }
}

void KeyboardWidget::setInitialSettings()
{
    ui->setupUi ( this );
    setWindowFlags ( Qt::WindowDoesNotAcceptFocus |
                     Qt::Tool |
                     Qt::FramelessWindowHint |
                     Qt::WindowStaysOnTopHint );
    setFixedSize ( keyboard_width, keyboard_height );
}

void KeyboardWidget::setDefaultKeyboard()
{
    m_pVLayout = new QVBoxLayout;
    m_pDigitsFrame = new DigitsFrame;
    m_pEngKeyboard = new EngKeyboard;
    m_pRusKeyboard = new RusKeyboard;
    m_pRusKeyboard->hide();
    m_pVLayout->addWidget ( m_pDigitsFrame );
    m_pVLayout->addWidget ( m_pEngKeyboard );
    m_pVLayout->addWidget ( m_pRusKeyboard );
    m_pVLayout->setContentsMargins ( 0, 0, 0, 0 );
    setLayout ( m_pVLayout );
}

void KeyboardWidget::setConnections()
{
    connect ( m_pEngKeyboard, &EngKeyboard::capsKeyPressed, this,
    [&]() {
        switchDigitsFrame ( EngSpecialSymbols );
    } );
    connect ( m_pRusKeyboard, &EngKeyboard::capsKeyPressed, this,
    [&]() {
        switchDigitsFrame ( RusSpecialSymbols );
    } );
    connect ( m_pEngKeyboard, &EngKeyboard::closeKeyPressed, this,
    [&]() {
//        QFocusEvent focusEvent = QFocusEvent(QEvent::Type::FocusOut,Qt::FocusReason::MouseFocusReason);
//        QCoreApplication::sendEvent(_attachedObject, &focusEvent);
        closeKeyboard();
    } );
    connect ( m_pEngKeyboard, SIGNAL ( switchLangPressed() ),
              SLOT ( switchKeyboard() ) );
    connect ( m_pRusKeyboard, SIGNAL ( switchLangPressed() ),
              SLOT ( switchKeyboard() ) );
    connect ( m_pEngKeyboard, SIGNAL ( charKeyPressed ( QString ) ),
              SLOT ( keyboardCharKeyPressed ( QString ) ) );
    connect ( m_pRusKeyboard, SIGNAL ( charKeyPressed ( QString ) ),
              SLOT ( keyboardCharKeyPressed ( QString ) ) );
    connect ( m_pDigitsFrame, SIGNAL ( digitKeyPressed ( QString ) ),
              SLOT ( keyboardCharKeyPressed ( QString ) ) );
    connect ( m_pDigitsFrame, SIGNAL ( deleteSymbol() ),
              SLOT ( deleteKey() ) );
}

void KeyboardWidget::switchDigitsFrame ( DigitsFrameType digitsFrameType )
{
    DigitsFrameType frameType = m_pDigitsFrame->getFrameType();

    if ( frameType != Digits ) {
        m_pDigitsFrame->setFrameType ( Digits );
    } else {
        m_pDigitsFrame->setFrameType ( digitsFrameType );
    }

    m_pDigitsFrame->switchFrame();
}

void KeyboardWidget::keyboardCharKeyPressed ( const QString & keyText )
{
    QKeySequence keySequence = keyText;
    QString key = KeyboardTextCorrector::performKeyboardTextCorrection(keyText);

    QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, keySequence[0], Qt::NoModifier,key);
    QCoreApplication::sendEvent(_attachedObject, &keyPressEvent);
}

void KeyboardWidget::deleteKey()
{
    QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    QCoreApplication::sendEvent(_attachedObject, &keyPressEvent);
}

#include <QApplication>
#include <QDesktopWidget>
#include <QWindow>

void KeyboardWidget::showKeyboard(QObject* ob)
{
    QRect screenres = QApplication::desktop()->screenGeometry(1);
    _attachedObject = ob;

    show();
    windowHandle()->setScreen(qApp->screens()[1]);
//    move(screenres.bottomLeft());
    move(0,screenres.height() - height());
    show();
}

void KeyboardWidget::closeKeyboard()
{
    _attachedObject = Q_NULLPTR;
    close();
}
