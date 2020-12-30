#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

#include "engkeyboard.h"
#include "specialchkeyboard.h"
#include "extrakeyboard.h"
#include "keyboardtextcorrector.h"

#include <QDebug>

static constexpr short keyboard_width = 480;
static constexpr short keyboard_height = 160;

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
    if(_mode == KeyboardMode::SPECIAL) {
        _mode = KeyboardMode::LOWER;
        m_pEngKeyboard->invertCaps();
        _spChKeyboard->hide();
        m_pEngKeyboard->show();
    } else if(_mode == KeyboardMode::UPPER) {
        _mode = KeyboardMode::SPECIAL;

        m_pEngKeyboard->hide();
        _spChKeyboard->show();
    }else{
        _mode = KeyboardMode::UPPER;
        m_pEngKeyboard->invertCaps();
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
    _mode = KeyboardMode::LOWER;
}

void KeyboardWidget::setDefaultKeyboard()
{
    m_pHLayout = new QHBoxLayout;
    _spChKeyboard = new SpecialChKeyboard;
    m_pEngKeyboard = new EngKeyboard;
    _exKeyboard = new ExtraKeyboard;

//    m_pHLayout->addWidget ( m_pDigitsFrame );
    m_pHLayout->addWidget ( m_pEngKeyboard );
    m_pHLayout->addWidget ( _spChKeyboard);
    m_pHLayout->addWidget ( _exKeyboard );
    _spChKeyboard->hide();

    m_pHLayout->setContentsMargins ( 0, 0, 0, 0 );
    setLayout ( m_pHLayout );
}

void KeyboardWidget::setConnections()
{
    connect ( m_pEngKeyboard, &EngKeyboard::charKeyPressed, this, &KeyboardWidget::keyboardCharKeyPressed);
    connect ( _exKeyboard, &ExtraKeyboard::deleteKeyPressed,this, &KeyboardWidget::deleteKey);
    connect ( _exKeyboard, &ExtraKeyboard::charKeyPressed,this, &KeyboardWidget::keyboardCharKeyPressed);
    connect ( _exKeyboard, &ExtraKeyboard::switchLangPressed,this, &KeyboardWidget::switchKeyboard);
    connect ( _exKeyboard, &ExtraKeyboard::closeKeyPressed,this, &KeyboardWidget::closeKeyboard);
    connect ( _exKeyboard, &ExtraKeyboard::modeKeyPressed,this, &KeyboardWidget::switchKeyboard);

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
    _attachedObject = ob;

    show();
#ifdef __arm__
    QRect screenres = QApplication::desktop()->screenGeometry(1);

    windowHandle()->setScreen(qApp->screens()[1]);
    move(0,screenres.height() - height());
    show();
#else
    move(0, windowHandle()->geometry().height()- height());
    show();
#endif
}

void KeyboardWidget::closeKeyboard()
{
    //        QFocusEvent focusEvent = QFocusEvent(QEvent::Type::FocusOut,Qt::FocusReason::MouseFocusReason);
    //        QCoreApplication::sendEvent(_attachedObject, &focusEvent);
    _attachedObject = Q_NULLPTR;
    close();
}
