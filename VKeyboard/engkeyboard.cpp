#include "engkeyboard.h"
#include "ui_engkeyboard.h"

#include "keyboardsymbols.h"

static constexpr short optimalParentWidgetWidth = 430;
static constexpr int lastNonAlphabetSymbolsCount = 3;

EngKeyboard::EngKeyboard ( QWidget * parent ) :
    BaseKeyboard ( parent ),
    ui ( new Ui::EngKeyboard )
{
    ui->setupUi ( this );
    setButtonList ( findChildren<QPushButton *>() );
    setUpperState ( false );
}

EngKeyboard::~EngKeyboard()
{
    delete ui;
}

short EngKeyboard::getOptimalParentWidgetWidth() const
{
    return optimalParentWidgetWidth;
}


