#ifndef L10PRINTIMAGE_H
#define L10PRINTIMAGE_H

#include <future>
#include <logger.h>

#include "printimagecontrol.h"
#include "l10imageprovider.h"

class L10PrintImage : public PrintImageControl
{
public:
    L10PrintImage(L10ImageProvider* l10imageProvider);

    void imageChange(int number) override;

    void requestTransImage(int number);

    L10ImageProvider* _l10imageProvider = nullptr;
private:
    std::future<QString> _imageTransfuture;

};

#endif // L10PRINTIMAGE_H
