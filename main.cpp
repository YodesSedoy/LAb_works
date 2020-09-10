#include <QtCore/QCoreApplication>
#include "Filters.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <shellapi.h>

using namespace std;

void printMenu() {
    system("cls");
    cout << "Filters" << endl;
    cout << "1.  Original Image" << endl;
    cout << "2.  Apply Invert Filter" << endl;
    cout << "3.  Apply Blur Filter" << endl;
    cout << "4.  Apply Gaussian Filter" << endl;
    cout << "5.  Apply Gray Scale Filter" << endl;
    cout << "6.  Apply Sepia Filter" << endl;
    cout << "7.  Apply Brightness Filter" << endl;
    cout << "8.  Apply Sobel Filter" << endl;
    cout << "9.  Apply Sharpness Filter" << endl;
    cout << "10. Apply Embossing Filter" << endl;
    cout << "11. Apply Max Sharpness Filter" << endl;
    cout << "12. Apply Waves" << endl;
    cout << "13. Apply Glass" << endl;
    cout << "14. Apply Dilation" << endl;
    cout << "15. Apply Erosion" << endl;
    cout << "16. Apply Opening" << endl;
    cout << "17. Apply Closening" << endl;
    cout << "18. Apply Top Hat" << endl;
    cout << "19. Apply Grey World" << endl;
    cout << "20. Apply Ideal Reflector" << endl;

    cout << "> ";
}

int getVariant(int count) {
    int variant;
    string s;
    getline(cin, s);
    while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 1 || variant > count) {
        cout << "Incorrect input. Try again: ";
        getline(cin, s);
    }
    return variant;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string s;
    QImage photo;
    photo.load("origin.png");
    photo.save("1.starting.png");
    int var;
    do {
        printMenu();
        var = getVariant(20);
        switch (var) {
        case 1: {
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\1.starting.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 2: {
            InvertFilter* invert = new InvertFilter();
            QImage InvertImage = invert->calculateNewImagePixMap(photo, 0);
            InvertImage.save("2.invert_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\2.invert_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 3: {
            BlurFilter* blur = new BlurFilter();
            QImage BlurImage = blur->calculateNewImagePixMap(photo, 1);
            BlurImage.save("3.blur_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\3.blur_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 4: {
            GaussianBlurFilter* gblur = new GaussianBlurFilter();
            QImage GBlurImage = gblur->calculateNewImagePixMap(photo, 3);
            GBlurImage.save("4.gaussian_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\4.gaussian_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 5: {
            GrayScaleFilter* gscale = new GrayScaleFilter();
            QImage GScaleImage = gscale->calculateNewImagePixMap(photo, 3);
            GScaleImage.save("5.grayscale_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\5.grayscale_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 6: {
            SepiaFilter* sepia = new SepiaFilter();
            QImage SepiaImage = sepia->calculateNewImagePixMap(photo, 3);
            SepiaImage.save("6.sepia_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\6.sepia_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 7: {
            BrightnessFilter* br = new BrightnessFilter();
            QImage BrightnessImage = br->calculateNewImagePixMap(photo, 3);
            BrightnessImage.save("7.brightness_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\7.brightness_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 8: {
            SobelFilter* sob = new SobelFilter();
            QImage SobelImage = sob->calculateNewImagePixMap(photo, 1);
            SobelImage.save("8.sobel_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\8.sobel_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 9: {
            SharpnessFilter* sharp = new SharpnessFilter();
            QImage SharpnessImage = sharp->calculateNewImagePixMap(photo, 1);
            SharpnessImage.save("9.sharp_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\9.sharp_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 10: {
            EmbossingFilter* emb = new EmbossingFilter();
            QImage EmbossingImage = emb->calculateNewImagePixMap(photo, 1);
            EmbossingImage.save("10.embossing_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\10.embossing_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 11: {
            MaxSharpnessFilter* maxsharp = new MaxSharpnessFilter();
            QImage MaxSharpnessImage = maxsharp->calculateNewImagePixMap(photo, 1);
            MaxSharpnessImage.save("11.maxsharpness_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\11.maxsharpness_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 12: {
            WaveFilter* wave = new WaveFilter();
            QImage WaveImage = wave->calculateNewImagePixMap(photo, 1);
            WaveImage.save("12.wave_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\12.wave_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 13: {
            GlassFilter* glass = new GlassFilter();
            QImage GlassImage = glass->calculateNewImagePixMap(photo, 1);
            GlassImage.save("13.glass_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\13.glass_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 14: {
            DilationFilter* dil = new DilationFilter();
            QImage DilImage = dil->calculateNewImagePixMap(photo, 1);
            DilImage.save("14.dilation_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\14.dilation_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 15: {
            ErosionFilter* er = new ErosionFilter();
            QImage ErImage = er->calculateNewImagePixMap(photo, 1);
            ErImage.save("15.erosion_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\15.erosion_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 16: {
            OpeningFilter* op = new OpeningFilter();
            QImage OpImage = op->calculateNewImagePixMap(photo, 1);
            OpImage.save("16.opening_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\16.opening_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 17: {
            ClosingFilter* cl = new ClosingFilter();
            QImage ClImage = cl->calculateNewImagePixMap(photo, 1);
            ClImage.save("17.closing_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\17.closing_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 18: {
            TopHat* th = new TopHat();
            QImage ThImage = th->calculateNewImagePixMap(photo, 1);
            ThImage.save("18.tophat_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\18.tophat_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 19: {
            GreyWorldFilter* gw = new GreyWorldFilter();
            QImage GreyWorldImage = gw->calculateNewImagePixMap(photo, 1);
            GreyWorldImage.save("19.greyworld_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\19.greyworld_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 20: {
            IdealReflectorFilter* ir = new IdealReflectorFilter();
            QImage IdealReflectorImage = ir->calculateNewImagePixMap(photo, 1);
            IdealReflectorImage.save("20.idealreflector_filter.png");
            ShellExecute(NULL, L"open", L"G:\\build-filters-Desktop_Qt_5_15_0_MinGW_64_bit-Debug\\20.idealreflector_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        /*
        case 21: {
            system("cls");
            cout << "Input size of the structuring element: ";
            int n = 3;
            cin >> n;
            float *str;
            str = new float[n*n];
            cout << "Input structuring element:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> str[i, j];
                }
            }
            ErosionFilter* er;
            er->SetVector(str, n);
            QImage ErImage = er->calculateNewImagePixMap(photo, 1);
            ErImage.save("21.custom_structuring_element_filter.png");
            ShellExecute(NULL, L"open", L"D:\\University\\ComputerGraphics\\Filters\\Filters\\21.custom_structuring_element_filter.png", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 22: {
            InvertFilter* invert = new InvertFilter();
            QImage InvertImage = invert->calculateNewImagePixMap(photo, 0);
            InvertImage.save("2.invert_filter.png");
            BlurFilter* blur = new BlurFilter();
            QImage BlurImage = blur->calculateNewImagePixMap(photo, 1);
            BlurImage.save("3.blur_filter.png");
            GaussianBlurFilter* gblur = new GaussianBlurFilter();
            QImage GBlurImage = gblur->calculateNewImagePixMap(photo, 3);
            GBlurImage.save("4.gaussian_filter.png");
            GrayScaleFilter* gscale = new GrayScaleFilter();
            QImage GScaleImage = gscale->calculateNewImagePixMap(photo, 3);
            GScaleImage.save("5.grayscale_filter.png");
            SepiaFilter* sepia = new SepiaFilter();
            QImage SepiaImage = sepia->calculateNewImagePixMap(photo, 3);
            SepiaImage.save("6.sepia_filter.png");
            BrightnessFilter* br = new BrightnessFilter();
            QImage BrightnessImage = br->calculateNewImagePixMap(photo, 3);
            BrightnessImage.save("7.brightness_filter.png");
            SobelFilter* sob = new SobelFilter();
            QImage SobelImage = sob->calculateNewImagePixMap(photo, 1);
            SobelImage.save("8.sobel_filter.png");
            SharpnessFilter* sharp = new SharpnessFilter();
            QImage SharpnessImage = sharp->calculateNewImagePixMap(photo, 1);
            SharpnessImage.save("9.sharp_filter.png");
            EmbossingFilter* emb = new EmbossingFilter();
            QImage EmbossingImage = emb->calculateNewImagePixMap(photo, 1);
            EmbossingImage.save("10.embossing_filter.png");
            MaxSharpnessFilter* maxsharp = new MaxSharpnessFilter();
            QImage MaxSharpnessImage = maxsharp->calculateNewImagePixMap(photo, 1);
            MaxSharpnessImage.save("11.maxsharpness_filter.png");
            WaveFilter* wave = new WaveFilter();
            QImage WaveImage = wave->calculateNewImagePixMap(photo, 1);
            WaveImage.save("12.wave_filter.png");
            GlassFilter* glass = new GlassFilter();
            QImage GlassImage = glass->calculateNewImagePixMap(photo, 1);
            GlassImage.save("13.glass_filter.png");
            DilationFilter* dil = new DilationFilter();
            QImage DilImage = dil->calculateNewImagePixMap(photo, 1);
            DilImage.save("14.dilation_filter.png");
            ErosionFilter* er = new ErosionFilter();
            QImage ErImage = er->calculateNewImagePixMap(photo, 1);
            ErImage.save("15.erosion_filter.png");
            OpeningFilter* op = new OpeningFilter();
            QImage OpImage = op->calculateNewImagePixMap(photo, 1);
            OpImage.save("16.opening_filter.png");
            ClosingFilter* cl = new ClosingFilter();
            QImage ClImage = cl->calculateNewImagePixMap(photo, 1);
            ClImage.save("17.closing_filter.png");
            TopHat* th = new TopHat();
            QImage ThImage = th->calculateNewImagePixMap(photo, 1);
            ThImage.save("18.tophat_filter.png");
            GreyWorldFilter* gw = new GreyWorldFilter();
            QImage GreyWorldImage = gw->calculateNewImagePixMap(photo, 1);
            GreyWorldImage.save("19.greyworld_filter.png");
            IdealReflectorFilter* ir = new IdealReflectorFilter();
            QImage IdealReflectorImage = ir->calculateNewImagePixMap(photo, 1);
            IdealReflectorImage.save("20.idealreflector_filter.png");
            ShellExecute(NULL, L"open", L"D:\\University\\ComputerGraphics\\Filters\\Filters", NULL, NULL, SW_SHOWNORMAL);
            break;
        }*/
    }
    }  while (var != 23);
    ShellExecute(NULL, L"open", L"D:\\University\\ComputerGraphics\\Filters\\Filters", NULL, NULL, SW_SHOWNORMAL);
}
