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
static constexpr short keyboard_height = 180;

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

void KeyboardWidget::attachTo ( QLineEdit * pTextReceiver )
{
    m_pTextReceiver = pTextReceiver;
}

void KeyboardWidget::detachReceiver()
{
    m_pTextReceiver = Q_NULLPTR;
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
    m_pVLayout->setContentsMargins ( 2, 2, 2, 2 );
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

bool KeyboardWidget::isTextReceiverReady() const
{
    return m_pTextReceiver != Q_NULLPTR;
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
    _receiveText.append(KeyboardTextCorrector::performKeyboardTextCorrection(keyText));
    emit setText(_receiveText);

    if ( isTextReceiverReady() ) {
        QString temp = m_pTextReceiver->text();
        temp.append ( KeyboardTextCorrector::performKeyboardTextCorrection(keyText) );
        m_pTextReceiver->setText ( temp );
    }
}

void KeyboardWidget::deleteKey()
{
    _receiveText.chop(last_char);
    emit setText(_receiveText);

    if ( isTextReceiverReady() ) {
        QString receiverString = m_pTextReceiver->text();
        receiverString.chop ( last_char );
        m_pTextReceiver->setText ( receiverString );
    }
}
#include <QWindow>
void KeyboardWidget::attachScreen(QObject *object)
{
    qDebug() << "sgdfsDf:";
    auto window = dynamic_cast<QWindow*>(object);
    windowHandle()->setScreen(window->screen());
    showFullScreen();
}
#include <QApplication>
#include <QDesktopWidget>
void KeyboardWidget::showKeyboard(QString text)
{
    QRect screenres = QApplication::desktop()->screenGeometry(1/*screenNumber*/);

    _receiveText = text;
    show();
    windowHandle()->setScreen(qApp->screens()[1]);
//    move(screenres.bottomLeft());
    move(0,screenres.height() - height());
    show();
}

void KeyboardWidget::closeKeyboard()
{
    _receiveText.clear();
    close();
}
