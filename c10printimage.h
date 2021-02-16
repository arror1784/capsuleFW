#ifndef C10PRINTIMAGE_H
#define C10PRINTIMAGE_H

#include "printimagecontrol.h"

class C10PrintImage : public PrintImageControl
{
public:
    C10PrintImage(int width, int height, int rotate);
    ~C10PrintImage() override;

    void imageChange(int number) override;
};

#endif // C10PRINTIMAGE_H
