#include "l10imageprovider.h"
#include "transimagergb.h"

const QString printFilePath = "/opt/capsuleFW/print/printFilePath";
L10ImageProvider::L10ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage L10ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 540;
    int height = 2560;
    QString path = printFilePath + "/" + id + ".png";
    if (size)
       *size = QSize(width, height);
    return TransImageRGB::L10transImage(path.toStdString());
//    return img;
}
