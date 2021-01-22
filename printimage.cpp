#include "printimage.h"

PrintImage::PrintImage()
{

}

void PrintImage::imageWrote()
{
    _imageWrote = true;
    _cv_image.notify_all();
}

void PrintImage::imageChange(QString path)
{
    _imageWrote = false;
    emit sendToQmlChangeImage(path);
}

void PrintImage::imageScale(double scale)
{
    emit sendToQmlImageScale(scale);
}

void PrintImage::imageRotate(int rotate)
{
    emit sendToQmlImageRotate(rotate);
}
void PrintImage::waitImageWrote()
{
    std::unique_lock<std::mutex> lk(_cv_image_m);
    _cv_image.wait(lk,[this]{return this->_imageWrote;});
}
