#ifndef L10PRINTIMAGE_H
#define L10PRINTIMAGE_H

#include <future>

#include "printimagecontrol.h"
#include "l10imageprovider.h"

class L10PrintImage : public PrintImageControl
{
public:
    L10PrintImage(int width, int height, int rotate, QString filePath, L10ImageProvider* l10imageProvider);
    ~L10PrintImage() override;

    void imageChange(int number,int delta,int ymult) override;

    void requestTransImage(int number,int delta,int ymult);

    L10ImageProvider* _l10imageProvider = nullptr;
private:
    std::future<QString> _imageTransfuture;
    QString _filePath;

};

#endif // L10PRINTIMAGE_H
