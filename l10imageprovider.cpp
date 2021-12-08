#include "l10imageprovider.h"
#include "transimagergb.h"
#include "imagescaler.h"

#include <QDebug>
#include <QImageReader>
#include <iostream>

L10ImageProvider::L10ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage L10ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 540;
    int height = 2560;
    if (size)
       *size = QSize(width, height);
    return _img;
}

void L10ImageProvider::transImage(QString path, int id,int delta, float yMult)
{
    qDebug() << "transimage start L10" << path;
    _id = id;

    QImageReader ir(path);
    if(!ir.canRead()){
        qDebug() << path << " is not available";
        return;
    }
    auto start = std::chrono::high_resolution_clock::now();

    auto oriImg = ir.read();
    auto tmp = ImageScaler::transImage(oriImg,delta,yMult,_imageBuf);
    _img = TransImageRGB::L10transImage(tmp);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> float_ms = end - start;
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "generateNumbers() elapsed time is " << float_ms.count() << " ms "
              << "( " << int_ms.count() << " milliseconds )" << std::endl;

    qDebug() << "transimage finish L10";
}

