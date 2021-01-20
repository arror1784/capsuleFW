#ifndef L10IMAGEPROVIDER_H
#define L10IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class L10ImageProvider : public QQuickImageProvider
{
public:
    L10ImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // L10IMAGEPROVIDER_H
