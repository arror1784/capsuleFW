#include "ruskeyboard.h"
#include "ui_ruskeyboard.h"

#include "keyboardsymbols.h"

static constexpr short optimalParentWidgetWidth = 620;

RusKeyboard::RusKeyboard ( QWidget * parent ) :
    BaseKeyboard ( parent ),
    ui ( new Ui::RusKeyboard )
{
    ui->setupUi ( this );
    setButtonList ( findChildren<QPushButton *>() );
    setUpperState ( false );
}

RusKeyboard::~RusKeyboard()
{
    delete ui;
}

short RusKeyboard::getOptimalParentWidgetWidth() const
{
    return optimalParentWidgetWidth;
}
