#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <windows.h>
#include <Gdiplus.h>
#pragma comment( lib,"Gdiplus.lib" )

using namespace std;

void InitGDI(){
    using namespace Gdiplus;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );
};


int GetEncoderClsid( const WCHAR * format, CLSID * pClsid ){
    using namespace Gdiplus;

    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    ImageCodecInfo * pImageCodecInfo = NULL;

    GetImageEncodersSize( &num, &size );
    if ( size == 0 )
        return -1;  // Failure

    pImageCodecInfo = ( ImageCodecInfo *)( malloc( size ) );
    if ( pImageCodecInfo == NULL )
        return -1;  // Failure

    GetImageEncoders( num, size, pImageCodecInfo );

    for ( UINT j = 0; j < num; ++j ){
        if ( wcscmp( pImageCodecInfo [j].MimeType, format ) == 0 ){
            *pClsid = pImageCodecInfo [j].Clsid;
            free( pImageCodecInfo );
            return j;  // Success
        }
    }

    free( pImageCodecInfo );
    return -1;  // Failure
}

int main(){
    namespace gdi = Gdiplus;

    ::InitGDI();

    gdi::Bitmap bmp( 100, 100); // буфер, куда рисовать
    gdi::Graphics graphics( &bmp ); // графическое устройство, чем рисовать
    gdi::SolidBrush whiteBrush( gdi::Color::White );
    gdi::SolidBrush blackBrush( gdi::Color::Black );

    gdi::Font font( L"Arial", 12 );
    gdi::RectF rect( 100, 100, 100, 150 );

    graphics.FillRectangle( &whiteBrush, gdi::Rect { 0, 0, 1000, 1000 } ); // заливка фона белым цветом

    gdi::StringFormat format;
    std::unique_ptr<wchar_t []> buf( new wchar_t [string.length()]() );

    ::MultiByteToWideChar( CP_UTF8, NULL, string.c_str(), (INT)string.size(), buf.get(), (INT)string.length() );

    // рисуем текст
    graphics.DrawString( buf.get(), (INT)string.length(), &font, rect, &format, &blackBrush );
}