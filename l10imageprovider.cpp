#include "l10imageprovider.h"
#include "transimagergb.h"
#include "imagescaler.h"

#include <QDebug>
#include <QImageReader>

L10ImageProvider::L10ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage L10ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 540;
    int height = 2560;
    qDebug() << "asdasd";
    if (size)
       *size = QSize(width, height);
    return _img;
}

void L10ImageProvider::transImage(QString path, int id,int delta, float yMult)
{
    qDebug() << "transimage start L10" << path;
    _id = id;
    QImageReader ir(path);

    auto oriImg = ir.read();
    _img = ImageScaler::transImage(oriImg,delta,yMult);
    _img = TransImageRGB::L10transImage(oriImg);
    qDebug() << "transimage finish L10";
}

