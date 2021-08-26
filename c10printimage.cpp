#include "c10printimage.h"

#include <QDebug>
C10PrintImage::C10PrintImage(int width, int height, int rotate, QString filePath, C10ImageProvider* c10imageProvider) :
    PrintImageControl (width,height,rotate), _filePath(filePath), _c10imageProvider(c10imageProvider)
{

}

C10PrintImage::~C10PrintImage()
{

}

void C10PrintImage::imageChange(int number)
{
    qDebug() << "C10";
    _imageWrote = false;
    if(number == 0){
        requestTransImage(0);
        emit sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(1);
    }else{
        emit sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(number + 1);
    }
}

void C10PrintImage::requestTransImage(int number)
{
    _imageTransfuture = std::async([this](int number) {
        QString imagePath = _rootPath + QString::number(number);
        QString filePath = _filePath + QString::number(number) + ".png";

        _c10imageProvider->transImage(filePath,number,1000000,1);
        return imagePath;
    },number);
}
