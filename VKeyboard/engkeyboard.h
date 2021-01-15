#ifndef ENG_KEYBOARD_H
#define ENG_KEYBOARD_H

#include "basekeyboard.h"

namespace Ui
{
    class EngKeyboard;
}

class EngKeyboard : public BaseKeyboard {
    Q_OBJECT

public:
    explicit EngKeyboard ( QWidget * parent = Q_NULLPTR );
    ~EngKeyboard();

    short getOptimalParentWidgetWidth() const override;

private:
    Ui::EngKeyboard * ui = Q_NULLPTR;
};

#endif // ENG_KEYBOARD_H
