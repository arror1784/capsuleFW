#ifndef C10PRINTIMAGE_H
#define C10PRINTIMAGE_H

#include <future>
#include <QImage>

#include "printimagecontrol.h"
#include "c10imageprovider.h"

class C10PrintImage : public PrintImageControl
{
public:
    C10PrintImage(int width, int height, int rotate, QString filePath, C10ImageProvider* c10imageProvider);
    ~C10PrintImage() override;

    void imageChange(int number,int delta,int ymult) override;
    
    void requestTransImage(int number,int delta,int ymult);
    
    C10ImageProvider* _c10imageProvider = nullptr;
private:
    std::future<QString> _imageTransfuture;
    QString _filePath;

};

#endif // C10PRINTIMAGE_H
