#include "../inc/BMP.hpp"

namespace nu::images{

    BMP::BMP(){
        m_width = 0;
        m_height = 0;
    }
    BMP::BMP(int width, int height) {
        m_width = width;
        m_height = height;
        m_pixels = new Pixel * [m_height];
        for (int i = 0; i < m_height; i++)
            m_pixels[i] = new Pixel[m_width];

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_pixels[i][j] = { 0,0,0 };
    }
    BMP::~BMP(){
            for (int i = 0; i < bmpInfo.Height; i++)
                delete[] pixels[i];
            delete[] pixels;
        }
    void BMP::readFile(const std::string& filename){
            // Чтение файла
            std::ifstream in(filename, std::ios::binary); // открыть файл для бинарного чтения

            if (!m_width || !m_height) {
                m_width = bmpInfo.Width;
                m_height = bmpInfo.Height;
            }
            if (m_pixels != nullptr){
                for (int i = 0; i < m_height; i++)
                    delete[] m_pixels[i];
                delete[] m_pixels;
            }

            // Считать 14 байтов побайтово и заполнить структуру BMPHEADER
            in.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHEADER));
            in.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPINFO));
            readPixels(in);
    }
    void BMP::writeFile(const std::string& filename){
            // Записать файл
            if (m_width == 0 || m_height == 0)
                throw std::runtime_error("Det equally zero!!!");
            std::ofstream out(filename, std::ios::binary);

            int width = bmpInfo.Width;
            int height = bmpInfo.Height;

            // Формирование заголовка
            bmpHeader_new.Type = 0x4D42; // Тип данных BMP
            bmpHeader_new.Size = 14 + 40 + (3 * width * height);
            if (width % 4 != 0)
                bmpHeader_new.Size += (4 - (3 * width) % 4) * height;
            bmpHeader_new.OffBits = 54;
            bmpHeader_new.Reserved1 = 0;
            bmpHeader_new.Reserved2 = 0;

            out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

            // Формирование информации об изображении
            bmpInfo_new.BitCount = 24;
            bmpInfo_new.ClrImportant = 0;
            bmpInfo_new.ClrUsed = 0;
            bmpInfo_new.Compression = 0;
            bmpInfo_new.Height = height;
            bmpInfo_new.Planes = 1;
            bmpInfo_new.Size = 40;
            bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
            bmpInfo_new.Width = width;
            bmpInfo_new.XPelsPerMeter = 0;
            bmpInfo_new.YPelsPerMeter = 0;

            out.write(reinterpret_cast<char*>(&bmpInfo_new), sizeof(BMPINFO));

            // Записать пиксели
            for (int i = 0; i < bmpInfo_new.Height; i++) {
                for (int j = 0; j < bmpInfo_new.Width; j++)
                    out.write(reinterpret_cast<char*>(&pixels[i][j]), sizeof(Pixel));

                if ((3 * bmpInfo_new.Width) % 4 != 0)
                    for (int j = 0; j < 4 - (3*bmpInfo_new.Width) % 4; j++)
                    {
                        char c = 0;
                        out.write(&c, 1);
                    }
            }
        }
    void BMP::superFilter(){
            // pixels
            for (int i = 0; i < bmpInfo.Height; i++)
                for (int j = 0; j < bmpInfo.Width; j++) {
                    if(pixels[i][j].b != 250)
                        pixels[i][j].b = 250;
                    if (pixels[i][j].g > 50 > 0)
                        pixels[i][j].g += 20;
                    if (pixels[i][j].r > 50 > 0)
                        pixels[i][j].r -= 10;
                }
        }
    void BMP::readPixels(std::ifstream &in) {
            for (int i = 0; i < bmpInfo.Height; i++)
                pixels[i] = new Pixel[bmpInfo.Width];

            for (int i = 0; i < bmpInfo.Height; i++) {
                for (int j = 0; j < bmpInfo.Width; j++)
                    in.read(reinterpret_cast<char*>(&pixels[i][j]), sizeof(Pixel));

                if((3 * bmpInfo.Width) % 4 != 0)
                    for (int j = 0; j < 4 - (3*bmpInfo.Width) % 4; j++) {
                        char c;
                        in.read(&c, 1);
                    }
            }

    }

    void BMP::writeSecret(){
        std::string string;
        std::cout << "Enter secret password pls:";
        std::cin >> string;

        int i = 280;
        int j = 20;
        for (int k = 0; k < string.size(); ++k){
            if(string[k] == 'a'){
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1) && i >= h && i < h+5)
                            || (j == w+4 && i >= h && i < h+6)
                            || (j == w+3 && i == h+5)
                            || (j == w+3 && i == h+1)
                            || (j == w+2 && (i == h || i == h+5))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                }
                //cout << "I: " << i << "; J: " << j << endl;
                i-=6;
            } else if (string[k] == 'b') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+1 && i >= h && i < h+6)
                            || (j == w+4 && i >= h && i < h+4)
                            || ((j == w+2 || j == w+3) && (i == h || i == h+3))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'c') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+5; j++) {
                        if((j == w+1 && i >= h && i < h+5)
                           || ((j == w+2 || j == w+3 || j == w+4) && (i == h || i == h+4))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'd') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+1 && i >= h && i < h+4)
                           || (j == w+4 && i >= h && i < h+6)
                           || ((j == w+2 || j == w+3) && (i == h || i == h+3))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'e') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+1 && i >= h && i < h+5)
                           || (j == w+4 && (i == h || i == h+3))
                           || ((j == w+2 || j == w+3 || j == w+4) && (i == h || i == h+2 || i == h+4))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'f') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+2 && i >= h && i < h+6)
                           || ((j == w+3) && (i == h+2 || i == h+5))
                           || ((j == w+4) && (i == h+4 || i == h+5))
                           || ((j == w+1) && (i == h+2))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'g') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+1 && (i > h && i < h+5))
                           || ((j == w+2 || j == w+3) && (i == h || i == h+5))
                           || ((j == w+4) && (i == h+1 || i == h+2))
                           || ((j == w+3) && (i == h+2))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'h') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+1 && (i >= h && i < h+6))
                           || ((j == w+2 || j == w+3) && i == h+3)
                           || ((j == w+4) && (i == h || i == h+1 || i == h+2 || i == h+3))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'i') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+3; j++) {
                        if((j == w+1 && (i >= h && i < h+4))
                            || (j == w+1 && i == h+5)){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'j') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+4 && (i >= h && i < h+4))
                           || ((j == w+1) && i == h+1)
                           || ((j == w+2 || j == w+3) && i == h)
                           || ((j == w+4) && (i == h || i == h+5))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'k') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+1 && (i >= h && i < h+5))
                           || ((j == w+2) && i == h+2)
                           || ((j == w+3) && (i == h+1 || i == h+3))
                           || ((j == w+4) && (i == h || i == h+4))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'l') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+3; j++) {
                        if((j == w+1 && (i >= h && i < h+6))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'm') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+8; j++) {
                        if(((j == w+1 || j == w+7) && (i >= h && i < h+6))
                           || ((j == w+2 || j == w+6) && i == h+4)
                           || ((j == w+3 || j == w+5) && (i == h+3))
                           || ((j == w+4) && (i == h+2))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'n') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+7; j++) {
                        if(((j == w+1 || j == w+5) && (i >= h && i < h+6))
                           || ((j == w+2) && i == h+3)
                           || ((j == w+3) && (i == h+2))
                           || ((j == w+4) && (i == h+1))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'o') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1 || j == w+5) && (i > h && i < h+5))
                           || ((j == w+2 || j == w+3 || j ==w+4) && (i == h || i == h+5))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'p') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1) && (i >= h && i < h+6))
                           || ((j == w+4) && (i > h+1 && i < h+6))
                           || ((j == w+2 || j == w+3) && (i == h+2 || i == h+5))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'q') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+7; j++) {
                        if(((j == w+1 || j == w+5) && (i > h && i < h+5))
                           || ((j == w+2 || j == w+3 || j ==w+4) && (i == h || i == h+5))
                           || ((j == w+4) && (i == h+1))
                           || ((j == w+6) && (i == h))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'r') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+7; j++) {
                        if(((j == w+1) && (i >= h && i < h+6))
                           || ((j == w+2 || j == w+3) && i == h+5)
                           || ((j == w+4) && (i == h+4 || i == h+3))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 's') {
                int h = i;
                int w = j;
                for (i; i < h+7; i++)
                    for (j=w; j < w+7; j++) {
                        if(((j == w+1) && (i == h+1 || i == h+4 || i == h+5))
                           || ((j == w+2 || j == w+3) && (i == h || i == h+3 || i == h+6))
                           || ((j == w+4) && (i == h+1 || i == h+2 || i == h+5))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=7;
            } else if (string[k] == 't') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if((j == w+3 && (i >= h && i < h+6))
                           || ((j == w+1 || j == w+2 || j == w+4 || j == w+5) && (i == h+4))
                           || ((j == w+4 || j == w+5) && (i == h))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'u') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1 || j == w+5) && (i > h && i <= h+5))
                           || ((j == w+2 || j == w+3 || j ==w+4) && (i == h))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'v') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1 || j == w+5) && (i == h+4 || i == h+3 || i == h+5))
                           || ((j == w+2 || j == w+4) && (i == h+2 || i ==h+1))
                           || ((j == w+3) && (i == h))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'w') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+8; j++) {
                        if(((j == w+1 || j == w+7) && (i == h+4 || i == h+3 || i == h+5))
                           || ((j == w+2 || j == w+6) && (i == h+2 || i ==h+1))
                           || ((j == w+3 || j == w+5) && (i == h))
                           || ((j == w+4) && (i == h+1))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            } else if (string[k] == 'x') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1 || j == w+5) && (i == h || i == h+4 || i == h+5))
                           || ((j == w+2 || j == w+4) && (i == h+1 || i ==h+3))
                           || ((j == w+3) && (i == h+2))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            }else if (string[k] == 'y') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1 || j == w+5) && (i == h+4 || i == h+5))
                           || ((j == w+2 || j == w+4) && (i ==h+3))
                           || ((j == w+3) && (i == h || i == h+1 || i == h+2))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            }else if (string[k] == 'z') {
                int h = i;
                int w = j;
                for (i; i < h+6; i++)
                    for (j=w; j < w+6; j++) {
                        if(((j == w+1 || j == w+2 || j == w+3 || j == w+4 || j == w+5) && (i == h || i == h+5))
                           || ((j == w+2) && (i == h+1))
                           || ((j == w+3) && (i == h+2))
                           || ((j == w+4) && (i == h+3))
                           || ((j == w+5) && (i == h+4))){
                            pixels[i][j].b = 250;
                            pixels[i][j].g = 250;
                            pixels[i][j].r = 250;
                        }
                    }
                i-=6;
            }else {
                throw std::runtime_error("This symbol unacceptable");
            }
        }

    }
}
