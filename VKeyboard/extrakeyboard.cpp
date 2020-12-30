#include "extrakeyboard.h"
#include "ui_extrakeyboard.h"

static constexpr short optimalParentWidgetWidth = 50;

ExtraKeyboard::ExtraKeyboard(QWidget *parent) :
    BaseKeyboard(parent),
    ui(new Ui::ExtraKeyboard)
{
    ui->setupUi(this);
    setButtonList ( findChildren<QPushButton *>() );

}

ExtraKeyboard::~ExtraKeyboard()
{
    delete ui;
}
short ExtraKeyboard::getOptimalParentWidgetWidth() const
{
    return optimalParentWidgetWidth;
}
