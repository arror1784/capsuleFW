#ifndef RUS_KEYBOARD_H
#define RUS_KEYBOARD_H

#include "basekeyboard.h"

namespace Ui
{
    class RusKeyboard;
}

class RusKeyboard : public BaseKeyboard {
    Q_OBJECT

public:
    explicit RusKeyboard ( QWidget * parent = Q_NULLPTR );
    ~RusKeyboard();

    short getOptimalParentWidgetWidth() const override;

private:
    Ui::RusKeyboard * ui = Q_NULLPTR;
};

#endif // RUS_KEYBOARD_H
