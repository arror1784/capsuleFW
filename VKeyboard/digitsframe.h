#ifndef DIGITS_FRAME_H
#define DIGITS_FRAME_H

#include <QFrame>

#include <QList>
#include <QString>

#include "keyboardsymbols.h"

class QPushButton;

namespace Ui
{
    class DigitsFrame;
}

class DigitsFrame : public QFrame {
    Q_OBJECT

public:
    explicit DigitsFrame ( QWidget * parent = Q_NULLPTR );
    ~DigitsFrame();

    void setFrameType ( DigitsFrameType frameType );
    DigitsFrameType getFrameType() const;

signals:
    void digitKeyPressed ( const QString & text );
    void deleteSymbol();

public slots:
    void switchFrame();

private slots:
    void digitPressed ( const QString & text );
    void deleteKeyPressed();

private:
    void setInitialSetting();
    void redrawKeys ( const QList<QString> & keys );

    Ui::DigitsFrame * ui = Q_NULLPTR;

    QList<QPushButton *> m_englishSpecialSymbols;
    QList<QPushButton *> m_russianSpecialSymbols;
    QList<QPushButton *> m_digits;
    QList<QPushButton *> m_buttons;

    DigitsFrameType m_digitsFrameType;
};

#endif // DIGITS_FRAME_H
