#include "l10printimage.h"

#include <QDebug>
L10PrintImage::L10PrintImage(int width, int height, int rotate, QString filePath, L10ImageProvider* l10imageProvider) :
    PrintImageControl (width,height,rotate), _l10imageProvider(l10imageProvider), _filePath(filePath)
{

}

L10PrintImage::~L10PrintImage()
{

}

void L10PrintImage::imageChange(int number,int delta,int ymult)
{
    qDebug() << "L10";
    _imageWrote = false;
    if(number == 0){
        requestTransImage(0,delta,ymult);
        emit sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(1,delta,ymult);
    }else{
        emit sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(number + 1,delta,ymult);
    }
}
void L10PrintImage::requestTransImage(int number,int delta,int ymult){

    _imageTransfuture = std::async([this](int number,int delta,int ymult) {
        QString imagePath = _rootPath + QString::number(number);
        QString filePath = _filePath + QString::number(number) + ".png";

        _l10imageProvider->transImage(filePath,number,delta,1);
        return imagePath;
    },number, delta,ymult);
}
