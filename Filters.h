#pragma once
#include <qimage.h>

//родительский фильтр

class Filters {
public:
    Filters() {};
    ~Filters() {};
    virtual QImage calculateNewImagePixMap(const QImage &photo, int radius) = 0;
};

//инвертирующий фильтр

class InvertFilter : public Filters {
public:
    InvertFilter() {};
    ~InvertFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius) override;
};

//родительский матричный фильтр

class MatrixFilter : public Filters {
public:
    float* vector;
    int mRadius;
    MatrixFilter(int radius = 1) : mRadius(radius) {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius) override;
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};

//фильтр "размытие"

class BlurFilter : public MatrixFilter {
public:
    BlurFilter() {
        int size = 2 * mRadius + 1;
        vector = new float[size*size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                vector[i*size + j] = float(1.0f / ((float)(size*size)));
    }
};

// фильтр "гауссово размытие"


class GaussianBlurFilter : public MatrixFilter {
public:
    GaussianBlurFilter() {
        createGaussianVector(3, 2);
    }
    ~GaussianBlurFilter() {};
    void createGaussianVector(int radius, int sigma);
};

// ч/б фильтр

class GrayScaleFilter : public Filters {
public:
    GrayScaleFilter() {};
    ~GrayScaleFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

// фильтр "сепия"

class SepiaFilter : public Filters {
public:
    SepiaFilter() {};
    ~SepiaFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

// фильтр "яркость"

class BrightnessFilter : public Filters {
public:
    BrightnessFilter() {};
    ~BrightnessFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

// матричный фильтр Собеля

class SobelFilter : public MatrixFilter {
public:
    float* vectorX;
    float* vectorY;
    SobelFilter() {
        vectorX = new float[3 * 3];
        vectorX[0] = -1; vectorX[1] = 0; vectorX[2] = 1;
        vectorX[3] = -2; vectorX[4] = 0; vectorX[5] = 2;
        vectorX[6] = -1; vectorX[7] = 0; vectorX[8] = 1;
        vectorY = new float[3 * 3];
        vectorY[0] = -1; vectorY[1] = -2; vectorY[2] = -1;
        vectorY[3] = 0; vectorY[4] = 0; vectorY[5] = 0;
        vectorY[6] = 1; vectorY[7] = 2; vectorY[8] = 1;
    }
    QImage calculateNewImagePixMap(const QImage &photo, int radius) override;
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};

// матричный фильтр "Яркость"

class SharpnessFilter : public MatrixFilter {
public:
    float* vector;
    SharpnessFilter() {
        vector = new float[3 * 3];
        vector[0] = 0; vector[1] = -1; vector[2] = 0;
        vector[3] = -1; vector[4] = 5; vector[5] = -1;
        vector[6] = 0; vector[7] = -1; vector[8] = 0;
    }
    QImage calculateNewImagePixMap(const QImage &photo, int radius) override;
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};

// матричный фильтр "тиснение"

class EmbossingFilter : public MatrixFilter {
public:
    float* vector;
    EmbossingFilter() {
        vector = new float[3 * 3];
        vector[0] = 0; vector[1] = 1; vector[2] = 0;
        vector[3] = 1; vector[4] = 0; vector[5] = -1;
        vector[6] = 0; vector[7] = -1; vector[8] = 0;
    }
    QImage calculateNewImagePixMap(const QImage &photo, int radius) override;
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};

// матричный фильтр "максимальная резкость"

class MaxSharpnessFilter : public MatrixFilter {
public:
    float* vector;
    MaxSharpnessFilter() {
        vector = new float[3 * 3];
        vector[0] = -1; vector[1] = -1; vector[2] = -1;
        vector[3] = -1; vector[4] = 9; vector[5] = -1;
        vector[6] = -1; vector[7] = -1; vector[8] = -1;
    }
    QImage calculateNewImagePixMap(const QImage &photo, int radius) override;
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};

class WaveFilter : public Filters {
public:
    WaveFilter() {};
    ~WaveFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class GlassFilter : public Filters {
public:
    GlassFilter() {};
    ~GlassFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class DilationFilter : public Filters {
public:
    float *vector;
    DilationFilter() {
        vector = new float[3, 3];
        vector[0, 0] = 0; vector[0, 1] = 1; vector[0, 2] = 0;
        vector[1, 0] = 1; vector[1, 1] = 1; vector[1, 2] = 1;
        vector[2, 0] = 0; vector[2, 1] = 1; vector[2, 2] = 0;
    }
    ~DilationFilter() {};
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class ErosionFilter : public Filters {
public:
    float *vector;
    ErosionFilter() {
        vector = new float[3, 3];
        vector[0, 0] = 0; vector[0, 1] = 1; vector[0, 2] = 0;
        vector[1, 0] = 1; vector[1, 1] = 1; vector[1, 2] = 1;
        vector[2, 0] = 0; vector[2, 1] = 1; vector[2, 2] = 0;
    }
    void SetVector(float* v, int n) {
        delete [] vector;
        vector = new float[n*n];
        for (int i = 0; i < n; i++)
        {
            vector[i] = v[i];
        }
    };
    ~ErosionFilter() {};
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class OpeningFilter : public Filters {
public:
    float *vector;
    OpeningFilter() {}
    ~OpeningFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class ClosingFilter : public Filters {
public:
    float *vector;
    ClosingFilter() {}
    ~ClosingFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class GreyWorldFilter : public Filters {
public:
    GreyWorldFilter() {};
    ~GreyWorldFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class IdealReflectorFilter : public Filters {
public:
    IdealReflectorFilter() {};
    ~IdealReflectorFilter() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class TopHat : public Filters {
public:
    TopHat() {};
    ~TopHat() {};
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class Sub : public Filters {
public:
    Sub() {}
    ~Sub() {}
    QColor Subst(int x, int y, QImage src, QImage res);
    QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class MedianFilter : public MatrixFilter {
public:
    MedianFilter() {}
    ~MedianFilter() {}
    QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};
