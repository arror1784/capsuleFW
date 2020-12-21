#ifndef BASE_KEYBOARD_H
#define BASE_KEYBOARD_H

#include <QFrame>

#include <QPushButton>
#include <QList>

class BaseKeyboard : public QFrame {
    Q_OBJECT
public:
    explicit BaseKeyboard ( QWidget * parent = Q_NULLPTR );
    virtual ~BaseKeyboard();

    virtual short getOptimalParentWidgetWidth() const = 0;

signals:
    void charKeyPressed ( const QString & text );

    void capsKeyPressed();
    void switchLangPressed();


public slots:
    void keyPressed ( const QString & text );
    void invertCaps();

protected:
    void setButtonList ( const QList<QPushButton *> & pButtonList );
    void setUpperState ( bool isUpper );

private:
    void setConnections();
    void invertLetters();
    void invertAlphabetEnding();
    QList<QPushButton *> m_buttonList;
    bool m_isUpper = false;
};

#endif // BASE_KEYBOARD_H
