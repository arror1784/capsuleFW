#ifndef SPECIALCHKEYBOARD_H
#define SPECIALCHKEYBOARD_H

#include "basekeyboard.h"

namespace Ui {
    class SpecialChKeyboard;
}

class SpecialChKeyboard : public BaseKeyboard
{
    Q_OBJECT

public:
    explicit SpecialChKeyboard(BaseKeyboard *parent = nullptr);
    ~SpecialChKeyboard();

    short getOptimalParentWidgetWidth() const override;
private:
    Ui::SpecialChKeyboard *ui;
};

#endif // SPECIALCHKEYBOARD_H
