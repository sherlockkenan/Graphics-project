#include "object.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>

enum { VERTEX = 0, TEXTURE = 1, NORMAL = 2 };

//变形第一步，转为球
void Obj::transfer_to_sphere(int step, int stepTotal){
	Vertex middle;
	int nNum = fs.size();
	glEnable(GL_TEXTURE_2D);
	//变为球
	glColor3f(255, 255, 255);
	int steps = stepTotal / 10 * 9;
	if (step <= steps){
		for (int i = 0; i < nNum; ++i)
		{
			if (fs[i].nNewMtlI != -1)
			{
				ms[fs[i].nNewMtlI].Set();               //设置新的材质
			}
			int sum = fs[i].vds.size();
			glBegin(GL_POLYGON);
			for (int j = 0; j < sum; ++j)
			{

				if (fs[i].vds[j].bVt)
				{
					glTexCoord3dv((double*)&(vts[fs[i].vds[j].nVtI]));
				}
				if (fs[i].vds[j].bVn)
				{
					glNormal3dv((double*)&(vns[fs[i].vds[j].nVnI]));

				}
				Vertex src = vs[fs[i].vds[j].nVI];
				Vertex dest = Sphere_vs[fs[i].vds[j].nVI];

				middle.fX = src.fX - (src.fX - dest.fX) / steps*step;
				middle.fY = src.fY - (src.fY - dest.fY) / steps*step;
				middle.fZ = src.fZ - (src.fZ - dest.fZ) / steps*step;
				glVertex3dv((double*)&(middle));
			}
			glEnd();
		}

	}
	//球褪色为白球
	else{
		for (int i = 0; i < nNum; ++i)
		{
			if (fs[i].nNewMtlI != -1)
			{
				ms[fs[i].nNewMtlI].Set();               //设置新的材质
			}
			int sum = fs[i].vds.size();
			glBegin(GL_POLYGON);
			for (int j = 0; j < sum; ++j)
			{
				int tmp = pow(2, step - steps);
				if ((i%tmp) == 0 && fs[i].vds[j].bVt)
				{
					glTexCoord3dv((double*)&(vts[fs[i].vds[j].nVtI]));
				}
				if (fs[i].vds[j].bVn)
				{
					glNormal3dv((double*)&(vns[fs[i].vds[j].nVnI]));

				}

				glVertex3dv((double*)&(Sphere_vs[fs[i].vds[j].nVI]));
			}
			glEnd();
		}

	}
	glDisable(GL_TEXTURE_2D);

}

//将球转为模型
void Obj::sphere_to_transfer(int step, int stepTotal){
	Vertex middle;
	int nNum = fs.size();
	glEnable(GL_TEXTURE_2D);
		glColor3f(255, 255, 255);
	int steps = stepTotal / 10 * 9;
	int begin = stepTotal - steps;
	if (step > begin){
		for (int i = 0; i < nNum; ++i)
		{
			if (fs[i].nNewMtlI != -1)
			{
				ms[fs[i].nNewMtlI].Set();//设置新的材质
			}

			int sum = fs[i].vds.size();
			glBegin(GL_POLYGON);
			for (int j = 0; j < sum; ++j)
			{
				if (fs[i].vds[j].bVt)
				{
					glTexCoord3dv((double*)&(vts[fs[i].vds[j].nVtI]));
				}
				if (fs[i].vds[j].bVn)
				{
					glNormal3dv((double*)&(vns[fs[i].vds[j].nVnI]));

				}
				Vertex dest = vs[fs[i].vds[j].nVI];
				Vertex src = Sphere_vs[fs[i].vds[j].nVI];

				middle.fX = src.fX - (src.fX - dest.fX) / steps*(step - begin);
				middle.fY = src.fY - (src.fY - dest.fY) / steps*(step - begin);
				middle.fZ = src.fZ - (src.fZ - dest.fZ) / steps*(step - begin);
				glVertex3dv((double*)&(middle));
			}
			glEnd();
		}
	}
	
	else{
		for (int i = 0; i < nNum; ++i)
		{
			if (fs[i].nNewMtlI != -1)
			{
				ms[fs[i].nNewMtlI].Set();              
			}
			int sum = fs[i].vds.size();
			glBegin(GL_POLYGON);
			for (int j = 0; j < sum; ++j)
			{
				int tmp = pow(2, begin - step);
				if ((i%tmp) == 0 && fs[i].vds[j].bVt)
				{
					glTexCoord3dv((double*)&(vts[fs[i].vds[j].nVtI]));
				}
				if (fs[i].vds[j].bVn)
				{
					glNormal3dv((double*)&(vns[fs[i].vds[j].nVnI]));

				}

				glVertex3dv((double*)&(Sphere_vs[fs[i].vds[j].nVI]));
			}
			glEnd();
		}


	}
	glDisable(GL_TEXTURE_2D);

}


void Obj::Render()
{

	int i;
	int nNum;
	glEnable(GL_TEXTURE_2D);
	nNum = fs.size();
	glColor4f(255, 255,255,255);
	for (int i = 0; i < nNum; ++i)
	{
		if (fs[i].nNewMtlI != -1)
		{
			ms[fs[i].nNewMtlI].Set();              
		}
		int sum = fs[i].vds.size();
		glBegin(GL_POLYGON);
		for (int j = 0; j < sum; ++j)
		{
			if (fs[i].vds[j].bVt)
			{
				glTexCoord3dv((double*)&(vts[fs[i].vds[j].nVtI]));
			}
			if (fs[i].vds[j].bVn)
			{
				glNormal3dv((double*)&(vns[fs[i].vds[j].nVnI]));

			}
			glVertex3dv((double*)&(vs[fs[i].vds[j].nVI]));
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

int Obj::LoadFromFile(const char* pcszFileName)
{
	FILE* fpFile = NULL;
	char szLine[MAX_PATH];
	char szMaterialPath[MAX_PATH];
	char szMaterialName[MAX_PATH];
	Vertex v;
	TVertex vt;
	VNormal vn;
	VertexData vd;

	Face face;
	int nIndex;
	int nKind;
	int nPos;
	int nMtlIndex = -1;//当前的面的材质索引
	int i;
    
    fpFile = fopen(pcszFileName, "rb");
    if (fpFile == NULL)
    {
        return 0;
	}

	vs.clear();
	vts.clear();
	vns.clear();
	fs.clear();
	
	while (fgets(szLine, MAX_PATH, fpFile) != NULL)
	{
		if (szLine[0] == 'v')
		{
			if (szLine[1] == 't')//纹理坐标
			{
				sscanf(szLine + 2, "%lf%lf%lf", &vt.fS, &vt.fT, &vt.fP);
				vts.push_back(vt);
			}
			else if (szLine[1] == 'n')//法线坐标
			{
				sscanf(szLine + 2, "%lf%lf%lf", &vn.fX, &vn.fY, &vn.fZ);
				vns.push_back(vn);
			}
			else//顶点坐标
			{
				sscanf(szLine + 1, "%lf%lf%lf", &v.fX, &v.fY, &v.fZ);
				vs.push_back(v);
			}
		}
		else if (szLine[0] == 'f')                       //读取代表面的一行
		{
			face.vds.clear();
			face.nNewMtlI = nMtlIndex;
            nMtlIndex = -1;                               //这样以后的面就不需要重新设置材质了,直到材质发生变化为止
			nPos = 1;
			nIndex = -1;
			nKind = VERTEX;
			vd.bVn = vd.bVt = false;

			while (szLine[nPos] != '\0')
			{
				if (szLine[nPos] >='0' && szLine[nPos] <= '9')
				{
					if (nIndex == -1)
					{
						nIndex = szLine[nPos] - '0';
					}
					else
					{
						nIndex = nIndex * 10 + szLine[nPos] - '0';
					}
				}
				else if (szLine[nPos] == '/')
				{
					if (nKind == VERTEX)
					{
						vd.nVI = nIndex - 1;
						nKind = TEXTURE;
					}
					else if (nKind == TEXTURE)
					{
						if (nIndex != -1)
						{
							vd.bVt = true;
							vd.nVtI = nIndex - 1;
						}
						nKind = NORMAL;
					}

					nIndex = -1;
				}
				else if (szLine[nPos] == ' ' || szLine[nPos] == '\n')
				{
                    if (nKind == TEXTURE)
                    {
                        if (nIndex != -1)
                        {
                            vd.bVt = true;
                            vd.nVtI = nIndex - 1;
						}
                        nKind = VERTEX;
                        face.vds.push_back(vd);
                        
                        nIndex = -1;
						vd.bVn = vd.bVt = false;
                    }
					else if (nKind == NORMAL)//法线坐标
					{
						if (nIndex != -1)
						{
							vd.bVn = true;
							vd.nVnI = nIndex - 1;
						}
						nKind = VERTEX;
						face.vds.push_back(vd);

						nIndex = -1;
						vd.bVn = vd.bVt = false;
					}
				}

				++nPos;
			}
			fs.push_back(face);
		}
		else if (szLine[0] == 'm' && strncmp(szLine, "mtllib", 6) == 0)
		{
			sscanf(szLine + 6, "%s", szMaterialPath);
			LoadMaterials(szMaterialPath);
		}
		else if (szLine[0] == 'u' && strncmp(szLine, "usemtl", 6) == 0)
		{
			sscanf(szLine + 6, "%s", szMaterialName);
			for (i = 0; i < ms.size(); ++i)
			{
				if (strcmp(ms[i].szName, szMaterialName) == 0)
				{
					nMtlIndex = i;
					break;
				}
			}
		} 
	}
	
    //初始化每个材质的纹理设置
    for (i = 0; i < ms.size(); ++i)
    {
        ms[i].InitTex();
    }
	Vertex sv;
	for (int i = 0; i < vs.size(); i++){
		double x = vs[i].fX;
		double y = vs[i].fY;
		double z = vs[i].fZ;
		double l = sqrt(x*x + y*y + z*z);
		sv.fX = x /l;
		sv.fY = y /l;
		sv.fZ = z /l;

		Sphere_vs.push_back(sv);
	}
	fclose(fpFile);
	return 1;
}

int Obj::LoadMaterials(const char* pcszFileName)
{
	FILE* fpFile;
	char szLine[MAX_PATH];
	char* pszLine;
	MTL mtl;
	bool bFirst = true;
    
	ms.clear();
	fpFile = fopen(pcszFileName, "r");
	if (fpFile == NULL)
	{
		return 0;
	}

	while (fgets(szLine, MAX_PATH, fpFile) != NULL)
	{
		pszLine = szLine;
		while (isspace(*pszLine))
		{
			++pszLine;
		}

		if (strncmp(pszLine, "newmtl", 6) == 0)
		{
			if (bFirst == true)
			{
				bFirst = false;
			}
			else
			{
				ms.push_back(mtl);//存储上一次读取的结果
			}
			sscanf(pszLine + 6, "%s", mtl.szName);
		}
		else if (pszLine[0] == 'K' && pszLine[1] == 'a')//材质的环境颜色
		{
			sscanf(pszLine + 2, "%f %f %f", &mtl.ambient.fR,
				&mtl.ambient.fG, &mtl.ambient.fB);
		}
		else if (pszLine[0] == 'K' && pszLine[1] == 'd')
		{
			sscanf(pszLine + 2, "%f %f %f", &mtl.diffuse.fR,
				&mtl.diffuse.fG, &mtl.diffuse.fB);
		}
		else if (pszLine[0] == 'K' && pszLine[1] == 's')
		{
			sscanf(pszLine + 2, "%f %f %f", &mtl.specular.fR,
				&mtl.specular.fG, &mtl.specular.fB);
		}
		else if (pszLine[0] == 'K' && pszLine[1] == 'e')
		{
			sscanf(pszLine + 2, "%f %f %f", &mtl.emission.fR,
				&mtl.emission.fG, &mtl.emission.fB);
		}
		else if (pszLine[0] == 'N' && pszLine[1] == 's')//材质的镜面指数
		{
			sscanf(pszLine + 2, "%f", &mtl.fShiness);
		}
		else if (pszLine[0] == 'd' && isspace(pszLine[1]))//透明度
		{
			sscanf(pszLine + 1, "%f", &mtl.fTrans);
		}
		else if (strncmp(pszLine, "map_Kd", 6) == 0)//纹理路径
		{
			sscanf(pszLine + 6, "%s", mtl.szTextureName);
		}
	}
	ms.push_back(mtl);//存储最后一次读取的结果

	return 1;
}


