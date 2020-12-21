#ifndef KEYBOARD_WIDGET_H
#define KEYBOARD_WIDGET_H

#include <QWidget>
#include <QString>

#include <digitsframe.h>
#include <QtQml/qtqml-config.h>
#include "keyboardsymbols.h"

class BaseKeyboard;
class QVBoxLayout;
class QLineEdit;

namespace Ui
{
    class KeyboardWidget;
}

class KeyboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit KeyboardWidget ( QWidget * parent = Q_NULLPTR );
    ~KeyboardWidget();

    void attachTo ( QLineEdit * pTextReceiver );
    void detachReceiver();

signals:
    void keyPressed ( const QString & keyText );
    void setText(const QString& text);

private slots:
    void switchKeyboard();
    void switchDigitsFrame ( DigitsFrameType digitsFrameType );
    void keyboardCharKeyPressed ( const QString & keyText );
    void deleteKey();

public slots:
    void attachScreen(QObject* object);
    void showKeyboard(QString text);
    void closeKeyboard();

private:
    void setInitialSettings();
    void setDefaultKeyboard();
    void setConnections();
    bool isTextReceiverReady() const;

    Ui::KeyboardWidget * ui = Q_NULLPTR;

    QVBoxLayout * m_pVLayout = Q_NULLPTR;
    BaseKeyboard * m_pEngKeyboard = Q_NULLPTR;
    BaseKeyboard * m_pRusKeyboard = Q_NULLPTR;
    DigitsFrame * m_pDigitsFrame = Q_NULLPTR;
    QLineEdit * m_pTextReceiver = Q_NULLPTR;

    QString _receiveText;
};

#endif // KEYBOARD_WIDGET_H
