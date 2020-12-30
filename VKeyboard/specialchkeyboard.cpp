#include "specialchkeyboard.h"
#include "ui_specialchkeyboard.h"

static constexpr short optimalParentWidgetWidth = 430;

SpecialChKeyboard::SpecialChKeyboard(BaseKeyboard *parent) :
    BaseKeyboard(parent),
    ui(new Ui::SpecialChKeyboard)
{
    ui->setupUi(this);
}

SpecialChKeyboard::~SpecialChKeyboard()
{
    delete ui;
}
short SpecialChKeyboard::getOptimalParentWidgetWidth() const
{
    return optimalParentWidgetWidth;
}
