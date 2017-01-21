#ifndef _XPC_YX_MTL_H
#define _XPC_YX_MTL_H

#include "Textrue_Tga.h"
#include <windows.h>



struct RGB
{
	float fR;
	float fG;
	float fB;
	float fA;
};

class MTL
{
	friend class Obj;
public:
	MTL()
    {
        emission.fR = emission.fG = emission.fB = 0.0;
        fTrans = 1.0;
    }
    void InitTex();
	void Set();
	void InitBMPTex();
	void SetBMP();

private:
	//���ʵĻ�����ɫ
	RGB ambient;
	RGB diffuse;
	RGB specular;
	RGB emission;

	float fShiness;//����ָ��
	float fTrans;//͸����
	char szName[MAX_PATH];
	char szTextureName[MAX_PATH];
	Tga tgaTex;
};
#endif