#include "printimage.h"

PrintImage::PrintImage()
{

}

void PrintImage::imageWrited()
{
    _imageWrited = true;
    _cv_image.notify_all();
}

void PrintImage::imageChange(QString path)
{
    bool _imageWrited = false;
    emit sendToQmlChangeImage(path);
}

void PrintImage::imageScale(double value)
{
    emit sendToQmlImageScale(value);
}
void PrintImage::waitImageWrited()
{
    std::unique_lock<std::mutex> lk(_cv_image_m);
    _cv_image.wait(lk,[this]{return this->_imageWrited;});
}
