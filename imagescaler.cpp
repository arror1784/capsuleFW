#include "imagescaler.h"

#include "dt/dt.h"
#include <cmath>
#include <execution>

QImage ImageScaler::transImage(QImage& img, int delta, float yMult, std::vector<uint8_t>& out)
{

    bool isShrink = delta < 0;

    int w = img.width();
    int h = img.height();
    int imgSize = w * h;

    unsigned char* bits = img.bits();
    image<float>* sdfImage;
    if(img.format() != QImage::Format_Grayscale8){
        bits = img.convertToFormat(QImage::Format_Grayscale8).bits();
    }
    image<uint8_t> origImg(w, h, bits);
    out.assign(imgSize, 0);

    if (isShrink)
    {
        sdfImage = dt(&origImg, 0, yMult);
        int threshold = 1 - delta;

        std::transform(std::execution::par_unseq,sdfImage->data, sdfImage->data + imgSize, out.begin(), [threshold](float flt)->uint8_t {
            if (std::round(flt) >= threshold)
                return 255;
            return 0;
            });
    }
    else
    {
        sdfImage = dt(&origImg, 255, yMult);
        int threshold = delta;
        std::transform(std::execution::par_unseq,sdfImage->data, sdfImage->data + imgSize, out.begin(), [threshold](float flt)->uint8_t {
            if (std::round(flt) <= threshold)
                return 255;
            return 0;
            });
    }
    delete sdfImage;
    return QImage(out.data(),w,h,QImage::Format_Grayscale8);
}
