#pragma once
#include <fstream>
#include "mathutils/matrix.hpp"

using namespace std;

using nu::math::Vec2d;
using nu::math::Mat22d;

namespace nu::images {
    #pragma pack(1)
        struct Pixel {
            unsigned char b;
            unsigned char g;
            unsigned char r;
        };
    #pragma pack()

    class BMP{
    public:
        BMP();
        BMP(int width, int height);
        ~BMP();
        void readFile(const std::string& filename);
        void writeFile(const std::string& filename);
        void superFilter();
        void readPixels(std::ifstream &in);
        void writeSecret();

    private:
        #pragma pack(1) // Отключить выравнивание
            struct BMPHEADER{
                unsigned short    Type;
                unsigned int      Size;
                unsigned short    Reserved1;
                unsigned short    Reserved2;
                unsigned int      OffBits;
            };
        #pragma pack()

        #pragma pack(1)
            struct BMPINFO{
                unsigned int    Size;
                int             Width;
                int             Height;
                unsigned short  Planes;
                unsigned short  BitCount;
                unsigned int    Compression;
                unsigned int    SizeImage;
                int             XPelsPerMeter;
                int             YPelsPerMeter;
                unsigned int    ClrUsed;
                unsigned int    ClrImportant;
            };
        #pragma pack()

    private:
        BMPHEADER bmpHeader;
        BMPINFO bmpInfo;
        Pixel** pixels = new Pixel * [bmpInfo.Height];
        BMPHEADER bmpHeader_new;
        BMPINFO bmpInfo_new;
        int m_width, m_height;
        Pixel** m_pixels = nullptr;
    };
}