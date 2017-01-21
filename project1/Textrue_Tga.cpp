#include "Textrue_Tga.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

int Tga::LoadTga(const char* pcszFileName)
{
    FILE* fpFile;
    BYTE* byPos;
    BYTE byTemp;
    int nSizeOfHeader;
    int nSize;
    int nRowSize;
    int i, j;
    
    //不重复加载相同的文件
    if (strcmp(pcszFileName, szTexName) == 0)
    {
        return 1;
    }
    strcpy(szTexName, pcszFileName);
    if (byData)
    {
        free(byData);
    }

    fpFile = fopen(pcszFileName, "rb");
    if (fpFile == NULL)
    {
        return 0;
    }
    
    nSizeOfHeader = 18;
    if (fread(&header, 18, 1, fpFile) != 1)
    {
        fclose(fpFile);
        return 0;
    }
    
    if (header.byImageInfoByteCnt != 0)
    {
        fseek(fpFile, header.byImageInfoByteCnt, SEEK_CUR);
    }
    nRowSize = header.uWidth * (header.chBitsPerPixel / 8);
    nSize = nRowSize * header.uHeight;
    byData = (BYTE*)malloc(nSize);
    if (fread(byData, nSize, 1, fpFile) != 1)
    {
        fclose(fpFile);
        return 0;
    }
    
    for (i = 0; i < header.uHeight; ++i)
    {
        for (j = 0; j < header.uWidth; ++j)
        {
            byPos = byData + i * nRowSize + j * header.chBitsPerPixel / 8;
            byTemp = byPos[0];
            byPos[0] = byPos[2];
            byPos[2] = byTemp;
        }
    }
    
    fclose(fpFile);
    return 1;
}
//获取比nA大的2的N次
int Pow2Big(int nA)
{
	int nRval = 1;
	while (nRval < nA) nRval <<= 1;
	return nRval;
}


void Tga::InitTex()
{
    double fTexScaleX = 1.0;
    double fTexScaleY = 1.0;
    GLenum eFormat;
    int nWidthPowerOfTwo = Pow2Big(header.uWidth);
    int nHeightPowerOfTwo = Pow2Big(header.uHeight);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &uTexName);
    glBindTexture(GL_TEXTURE_2D, uTexName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter


    if (header.chBitsPerPixel == 24)
    {
        eFormat = GL_RGB;
    }
    else if (header.chBitsPerPixel == 32)
    {
        eFormat = GL_RGBA;
    }
    
    if (nWidthPowerOfTwo == header.uWidth && nHeightPowerOfTwo == header.uHeight)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, eFormat, nWidthPowerOfTwo, nHeightPowerOfTwo, 
            0, eFormat, GL_UNSIGNED_BYTE, byData);
        fTexScaleX = fTexScaleY = 1.0f;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, eFormat, nWidthPowerOfTwo, nHeightPowerOfTwo,
        0, eFormat, GL_UNSIGNED_BYTE, NULL);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, header.uWidth, header.uHeight,
        GL_RGBA, GL_UNSIGNED_BYTE, byData);
        fTexScaleX = 1.0 * header.uWidth / nWidthPowerOfTwo;
        fTexScaleY = 1.0 * header.uHeight / nHeightPowerOfTwo;
        //设置纹理堆栈
        glMatrixMode(GL_TEXTURE);
        glScaled(fTexScaleX, fTexScaleY, 1.0);
    }
}

void Tga::SetTexture()
{
    glBindTexture(GL_TEXTURE_2D, uTexName);
}