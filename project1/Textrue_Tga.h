#ifndef _XPC_YX_TGA_H
#define _XPC_YX_TGA_H
#include <windows.h>

#define RGB16(r,g,b)   ( ((r>>3) << 10) + ((g>>3) << 5) + (b >> 3) )
#define RGB24(r,g,b)   ( ((r) << 16) + ((g) << 8) + (b) )

typedef unsigned char BYTE;

struct TgaHeader
{
    BYTE  byImageInfoByteCnt;    //The image information length, in byte
    BYTE  byColorTableExist;       //0-have not color table,1-have
    BYTE  byImageType;              //Image type,2-uncompare RGB image,10-compare RGB image
    BYTE  byColorTableInfo[5];    //Color table information
    unsigned short uXOrigin;
    unsigned short uYOrigin;
    unsigned short uWidth;
    unsigned short uHeight;
    unsigned char  chBitsPerPixel;  //每像素的字节数
    unsigned char  chImageDescriptor;    
};

class Tga
{
public:
    Tga() { byData = 0; szTexName[0] = 0; }
    Tga(const char* pcszFileName) { byData = 0; LoadTga(pcszFileName); }
    ~Tga() { if (byData) free(byData); }

	//loader
    int LoadTga(const char* pcszFileName);
    void InitTex();
    void SetTexture();
	unsigned uTexName;
private:
    TgaHeader header;
    BYTE* byData;
    char szTexName[MAX_PATH];

};

#endif 