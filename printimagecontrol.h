#ifndef PRINTIMAGECONTROL_H
#define PRINTIMAGECONTROL_H

#include <QObject>
#include <mutex>
#include <condition_variable>

class PrintImageControl : public QObject
{
    Q_OBJECT

public:
    PrintImageControl(int width, int height, int rotate);

signals:
    void sendToQmlChangeImage(QString path);
    void sendToQmlImageScale(double scale);
    void sendToQmlImageRotate(int rotate);
    void sendToQmlImageWidhtHeight(int width,int height);

public slots:
    void imageWrote();

public:
    virtual void imageChange(int number) = 0;
    void imageScale(double scale);
    void waitImageWrote();

    void setRootPath(QString path);
    void imageSetBlack();

    void reset();

private:
    std::condition_variable _cv_image;
    std::mutex _cv_image_m;

protected:
    double _scale = 0.0;
    int _width = 0;
    int _height = 0;
    int _rotate = 0;

    bool _imageWrote = true;

    QString _rootPath;
};

#endif // PRINTIMAGECONTROL_H
