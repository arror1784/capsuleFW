#ifndef L10IMAGEPROVIDER_H
#define L10IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class L10ImageProvider : public QQuickImageProvider
{
public:
    L10ImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    void transImage(QString path, int id,int delta, float yMult);

private:
    QImage _img;
    std::vector<uint8_t> _imageBuf;

    int _id;
};

#endif // L10IMAGEPROVIDER_H
