#ifndef EXTRAKEYBOARD_H
#define EXTRAKEYBOARD_H

#include "basekeyboard.h"

namespace Ui {
    class ExtraKeyboard;
}

class ExtraKeyboard : public BaseKeyboard
{
    Q_OBJECT

public:
    explicit ExtraKeyboard(QWidget *parent = Q_NULLPTR);
    ~ExtraKeyboard();

    short getOptimalParentWidgetWidth() const override;
private:
    Ui::ExtraKeyboard *ui = Q_NULLPTR;
};

#endif // EXTRAKEYBOARD_H
