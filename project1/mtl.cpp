#include "mtl.h"
#include <windows.h>
//#include <glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <tchar.h>  
#include<string>
using namespace std;

void  MTL::InitTex()
{
	size_t pos;
	string str = szTextureName;
	pos = str.find(".tga");
	if (pos != string::npos){

		tgaTex.LoadTga(szTextureName);
		tgaTex.InitTex();
	}
	else {
		pos = str.find(".bmp");
		if (pos != string::npos){

			InitBMPTex();
		}
	}
}

bool LoadBMPTexture(LPTSTR szFileName, GLuint &texid) // Creates Texture From A Bitmap File
{
	HBITMAP hBMP; // Handle Of The Bitmap
	BITMAP BMP; // Bitmap Structure

	glGenTextures(1, &texid); // Create The Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (!hBMP) // Does The Bitmap Exist?
		return FALSE; // If Not Return False

	GetObject(hBMP, sizeof(BMP), &BMP); // Get The Object


	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid); // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP); // Delete The Object

	return TRUE; // Loading Was Successfu
}
void  MTL::InitBMPTex()
{
	szTextureName;
	size_t len = strlen(szTextureName) + 1;
	size_t converted = 0;
	wchar_t *WStr;
	WStr = (wchar_t*)malloc(len*sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, szTextureName , _TRUNCATE);

	LoadBMPTexture(WStr, tgaTex.uTexName);
	//tgaTex.InitTex();
}

void  MTL::Set()
{
	ambient.fA = diffuse.fA = specular.fA = emission.fA = fTrans;
	//设置透明度
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendEquation(GL_ADD);
	//设置材质
	glMaterialfv(GL_FRONT, GL_AMBIENT, (float*)&ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, (float*)&diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (float*)&specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, (float*)&emission);
	glMaterialf(GL_FRONT, GL_SHININESS, fShiness);
	//设置纹理
	glBindTexture(GL_TEXTURE_2D, tgaTex.uTexName); // Bind To The Texture ID
}

 