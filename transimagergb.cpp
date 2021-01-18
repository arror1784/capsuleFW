#include "transimagergb.h"

#include <QImageReader>
#include <QImageWriter>
#include <QImage>
#include <QColor>
#include <QMatrix>

TransImageRGB::TransImageRGB()
{

}

#include <QDebug>
bool TransImageRGB::transImage(std::string target, std::string path, int width, int height,int rotate)
{
    QImageReader ir(target.data());
    auto oriImg = ir.read();
    QImage srcImage;
    QImage saveImage(width, height, QImage::Format_RGB32);

    qDebug() << "trans start";

    if(rotate){
        QPoint center = oriImg.rect().center();
        QMatrix matrix;
        matrix.translate(center.x(), center.y());
        matrix.rotate(rotate);

        srcImage = oriImg.transformed(matrix);
    }else{
        srcImage = oriImg;
    }


    for(int y = 0; y < srcImage.height(); y++){
        int x = 0;
        for(int i = 0; i < srcImage.width();i+=3){

            int transRed = 0;
            int transGreen = 0;
            int transBlue = 0;

            for(int j = 0; j < 3; j++){
                if(i + j > srcImage.width()){
                    break;
                }
                auto col = srcImage.pixelColor(i + j,y);
                int total = col.red();
                if(j == 0){
                    transRed = total;
                }else if(j == 1){
                    transGreen = total;
                }else{
                    transBlue = total;
                }
            }
            saveImage.setPixel(x++,y,QColor(transRed,transGreen,transBlue).rgb());
        }
    }
    QImageWriter iw(path.data());
    iw.write(saveImage);

    qDebug() << "trans finish";

    return true;
}

bool TransImageRGB::L10transImage(std::string target, std::string path)
{
    QImageReader ir(target.data());
    auto oriImg = ir.read();
    QImage saveImage(540, 2560, QImage::Format_RGB32);

    if(oriImg.width() != 2560 || oriImg.height() != 1620){
        return false;
    }
    int sourceWidth = oriImg.width();
    int sourceHeight = oriImg.height();

    for(int x = 0; x < sourceWidth; x++){
        int y = 0;
        for(int i = 0; i < sourceHeight;i+=3){

            int transRed = 0;
            int transGreen = 0;
            int transBlue = 0;

            for(int j = 0; j < 3; j++){
                if(i + j > sourceWidth){
                    break;
                }
                auto col = oriImg.pixelColor(x,i + j);
                int total = col.red();
                if(j == 0){
                    transRed = total;
                }else if(j == 1){
                    transGreen = total;
                }else{
                    transBlue = total;
                }
            }
            saveImage.setPixel(y++,(sourceWidth - 1) - x, QColor(transRed,transGreen,transBlue).rgb());
        }
    }
    QImageWriter iw(path.data());
    iw.write(saveImage);

    return true;
}
