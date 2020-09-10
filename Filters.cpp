#include "Filters.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
// функция для крайних пикселей

template <class T>
T clamp(T v, int max, int min) {
    if (v > max)
        return max;
    else if (v < min)
        return min;
    return v;
}

// инвертация

QImage InvertFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor photoColor = photo.pixelColor(x, y);
            photoColor.setRgb(255 - photoColor.red(), 255 - photoColor.green(), 255 - photoColor.blue());
            result_Image.setPixelColor(x, y, photoColor);
        }
    return result_Image;
}

QColor MatrixFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius)*size + j + radius;
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0),
                clamp<int>(y + i, photo.height() - 1, 0));
            returnR += color.red() * vector[idx];
            returnG += color.green() * vector[idx];
            returnB += color.blue() * vector[idx];
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage MatrixFilter::calculateNewImagePixMap(const QImage& photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++) {
        for (int y = 0; y < photo.height(); y++) {
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    }
    return result_Image;
}

void GaussianBlurFilter::createGaussianVector(int radius, int sigma) {
    const unsigned int size = 2 * radius + 1;
    float norm = 0;
    vector = new float[size*size];
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + (j + radius);
            vector[idx] = exp(-(i*i + j * j) / (sigma*sigma));
            norm += vector[idx];
        }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            vector[i*size + j] /= norm;
        }
}

QImage GrayScaleFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor photoColor = photo.pixelColor(x, y);
            int intensity = 0.36 * photoColor.red() + 0.53 *photoColor.green() + 0.11 * photoColor.blue();
            photoColor.setRgb(intensity, intensity, intensity);
            result_Image.setPixelColor(x, y, photoColor);
        }
    return result_Image;
}

QImage SepiaFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            int k = 13;
            QColor photoColor = photo.pixelColor(x, y);
            int intensity = 0.36 * photoColor.red() + 0.53 *photoColor.green() + 0.11 * photoColor.blue();
            photoColor.setRgb(clamp<int>(intensity + 2 * k, 255, 0), clamp<int>(intensity + 0.5 * k, 255, 0), clamp<int>(intensity - 1 * k, 255, 0));
            result_Image.setPixelColor(x, y, photoColor);
        }
    return result_Image;
}

QImage BrightnessFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            int k = 25;
            QColor photoColor = photo.pixelColor(x, y);
            photoColor.setRgb(clamp<int>(photoColor.red() + k, 255, 0), clamp<int>(photoColor.green(), 255, 0), clamp<int>(photoColor.blue(), 255, 0));
            result_Image.setPixelColor(x, y, photoColor);
        }
    return result_Image;
}

QColor SobelFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius)*size + j + radius;
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0),
                clamp<int>(y + i, photo.height() - 1, 0));
            returnR += color.red() * vectorX[idx] + color.red() * vectorY[idx];
            returnG += color.green() * vectorX[idx] + color.green() * vectorY[idx];
            returnB += color.blue() * vectorX[idx] + color.blue() * vectorY[idx];
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage SobelFilter::calculateNewImagePixMap(const QImage& photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++) {
        for (int y = 0; y < photo.height(); y++) {
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    }
    return result_Image;
}

QColor SharpnessFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius)*size + j + radius;
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));

            returnR += color.red() * vector[idx];
            returnG += color.green() * vector[idx];
            returnB += color.blue() * vector[idx];
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage SharpnessFilter::calculateNewImagePixMap(const QImage& photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++) {
        for (int y = 0; y < photo.height(); y++) {
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    }
    return result_Image;
}

QColor EmbossingFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius)*size + j + radius;
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
            returnR += vector[idx] * (0.36 * color.red() + 0.53 *color.green() + 0.11 * color.blue()) + 10;
            returnG += vector[idx] * (0.36 * color.red() + 0.53 *color.green() + 0.11 * color.blue()) + 10;
            returnB += vector[idx] * (0.36 * color.red() + 0.53 *color.green() + 0.11 * color.blue()) + 10;
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage EmbossingFilter::calculateNewImagePixMap(const QImage& photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++) {
        for (int y = 0; y < photo.height(); y++) {
            QColor photoColor = photo.pixelColor(x, y);
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    }
    return result_Image;
}

QColor MaxSharpnessFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius)*size + j + radius;
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0),
                clamp<int>(y + i, photo.height() - 1, 0));
            returnR += color.red() * vector[idx];
            returnG += color.green() * vector[idx];
            returnB += color.blue() * vector[idx];
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage MaxSharpnessFilter::calculateNewImagePixMap(const QImage& photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++) {
        for (int y = 0; y < photo.height(); y++) {
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    }
    return result_Image;
}

QImage WaveFilter::calculateNewImagePixMap(const QImage& photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            int k = x + 15 * sin(2 * 3.14 * y / 60), l = y;
            if ((k >= photo.width()) || (k < 0)) k = x;
            QColor newColor = photo.pixelColor(k, l);
            result_Image.setPixelColor(x, y, newColor);
        }
    return result_Image;
}

QImage GlassFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    srand(time(0));
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            int k = x + ((double)(rand()) / RAND_MAX - 0.5) * 10, l = y + ((double)(rand()) / RAND_MAX - 0.5) * 10;
            if (k >= photo.width() || k < 0) { k = x; }
            if (l >= photo.height() || l < 0) { l = y; }
            QColor newColor = photo.pixelColor(k, l);
            result_Image.setPixelColor(x, y, newColor);
        }
    return result_Image;
}

QColor DilationFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    int max = 0;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
            int intensity = color.red();
            if (color.red() != color.green() || color.red() != color.blue() || color.green() != color.blue()) {
                intensity = (int)(0.36*color.red() + 0.53*color.green() + 0.11*color.blue());
            }
            if ((vector[j + radius, i + radius] > 0) && (intensity > max))
            {
                max = intensity;
                returnR = color.red();
                returnG = color.green();
                returnB = color.blue();
            }
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));

}

QImage DilationFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    return result_Image;
}


QColor ErosionFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float returnR = 0;
    float returnG = 0;
    float returnB = 0;
    float size = 2 * radius + 1;
    int min = 255;
    int radX = sizeof(vector) / 2;
    int radY = sizeof(vector[0]) / 2;
    for (int i = -radY; i <= radY; i++)
        for (int j = -radX; j <= radX; j++) {
            QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
            int intensity = color.red();
            if (color.red() != color.green() || color.red() != color.blue() || color.green() != color.blue()) {
                intensity = (int)(0.36*color.red() + 0.53*color.green() + 0.11*color.blue());
            }
            if ((vector[j + radius, i + radius] > 0) && (intensity < min))
            {
                min = intensity;
                returnR = color.red();
                returnG = color.green();
                returnB = color.blue();
            }
        }
    return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));

}

QImage ErosionFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
        }
    return result_Image;

}
QImage OpeningFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    ErosionFilter* er;
    er = new ErosionFilter();
    result_Image = er->calculateNewImagePixMap(result_Image, 1);
    DilationFilter* dil;
    dil = new DilationFilter();
    result_Image = dil->calculateNewImagePixMap(result_Image, 1);
    return result_Image;
}

QImage ClosingFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    ErosionFilter* er;
    DilationFilter* dil;
    dil = new DilationFilter();
    result_Image = dil->calculateNewImagePixMap(result_Image, 1);
    er = new ErosionFilter();
    result_Image = er->calculateNewImagePixMap(result_Image, 1);
    return result_Image;
}

QImage GreyWorldFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    int r = 0, g = 0, b = 0, avg = 0, n = 0;
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor color = photo.pixelColor(x, y);
            n++;
            r += color.red();
            g += color.green();
            b += color.blue();
        }
    r = r / n;
    g = g / n;
    b = b / n;
    avg = (r + g + b) / 3;
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor ncolor = photo.pixelColor(x, y);
            ncolor.setRgb(clamp<int>((ncolor.red() * avg / r), 255, 0), clamp<int>((ncolor.green() * avg / g), 255, 0), clamp<int>((ncolor.blue() * avg / b), 255, 0));
            result_Image.setPixelColor(x, y, ncolor);
        }
    return result_Image;
}

QImage IdealReflectorFilter::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    int r = 0, g = 0, b = 0;
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor color = photo.pixelColor(x, y);
            if (r < color.red()) {
                r = color.red();
            }
            if (g < color.green()) {
                g = color.green();
            }
            if (b < color.blue()) {
                b = color.blue();
            }

        }
    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor color = photo.pixelColor(x, y);
            int r0 = color.red(), g0 = color.green(), b0 = color.blue();
            int newr = r0 * 255 / (r - 50), newg = g0 * 255 / (g - 50), newb = b0 * 255 / (b - 50);
            color.setRgb(clamp<int>(newr, 255, 0), clamp<int>(newg, 255, 0), clamp<int>(newb, 255, 0));
            result_Image.setPixelColor(x, y, color);
        }
    return result_Image;
}

QImage TopHat::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    QImage src_Image(photo);
    Sub* sub;
    sub = new Sub();
    result_Image = sub->calculateNewImagePixMap(result_Image, 1);
    return result_Image;
}

QImage Sub::calculateNewImagePixMap(const QImage &photo, int radius) {
    QImage result_Image(photo);
    QImage src_Image(photo);
    OpeningFilter* cl;
    cl = new OpeningFilter();
    result_Image = cl->calculateNewImagePixMap(result_Image, 1);

    for (int x = 0; x < photo.width(); x++)
        for (int y = 0; y < photo.height(); y++) {
            QColor sub(clamp(src_Image.pixelColor(x,y).red() - result_Image.pixelColor(x,y).red(), 255, 0), clamp(src_Image.pixelColor(x,y).green() - result_Image.pixelColor(x,y).green(), 255, 0),clamp(src_Image.pixelColor(x,y).blue() - result_Image.pixelColor(x,y).blue(), 255, 0));
            result_Image.setPixelColor(x, y, sub);
        }
    return result_Image;
}

/*QColor MedianFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
    float size = 2 * radius + 1;
    float* intensityVector = new float[size * size];
    int middleIntensity;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + (j + radius);
            intensityVector[idx] = calculateIntensity(photo.pixelColor(clamp(x + j, photo.width() - 1, 0), clamp(y + i, photo.height() - 1, 0)));
        }
    vector<int> sortIntVector(intensityVector, intensityVector + ARRLENGTH);
    sort(sortIntVector.begin(), sortIntVector.end());
    middleIntensity = sortIntVector[ARRLENGTH / 2];
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + (j + radius);
            if (calculateIntensity(photo.pixelColor(clamp(x + j, photo.width() - 1, 0),
                clamp(y + i, photo.height() - 1, 0))) == middleIntensity)
                return photo.pixelColor(clamp(x + j, photo.width() - 1, 0),
                    clamp(y + i, photo.height() - 1, 0));
        }
}*/
