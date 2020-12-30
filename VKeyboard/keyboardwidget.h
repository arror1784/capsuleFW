#ifndef KEYBOARD_WIDGET_H
#define KEYBOARD_WIDGET_H

#include <QWidget>
#include <QString>

#include <QtQml/qtqml-config.h>
#include "keyboardsymbols.h"

class EngKeyboard;
class QVBoxLayout;
class QHBoxLayout;
class ExtraKeyboard;
class SpecialChKeyboard;


enum class KeyboardMode
{ LOWER, UPPER, SPECIAL };

namespace Ui
{
    class KeyboardWidget;
}

class KeyboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit KeyboardWidget ( QWidget * parent = Q_NULLPTR );
    ~KeyboardWidget();

signals:
    void keyPressed ( const QString & keyText );
    void setText(const QString& text);

private slots:
    void switchKeyboard();
    void keyboardCharKeyPressed ( const QString & keyText );
    void deleteKey();

public slots:
    void showKeyboard(QObject* ob);
    void closeKeyboard();

private:
    void setInitialSettings();
    void setDefaultKeyboard();
    void setConnections();
    bool isTextReceiverReady() const;

    void setKeyboardLower();
    void setKeyboardUpper();
    void setKeyboardSpecial();

    Ui::KeyboardWidget* ui = Q_NULLPTR;

    QHBoxLayout* m_pHLayout = Q_NULLPTR;

    EngKeyboard* m_pEngKeyboard = Q_NULLPTR;
    SpecialChKeyboard* _spChKeyboard = Q_NULLPTR;
    ExtraKeyboard* _exKeyboard = Q_NULLPTR;

    KeyboardMode _mode;

    QObject* _attachedObject;
};

#endif // KEYBOARD_WIDGET_H
