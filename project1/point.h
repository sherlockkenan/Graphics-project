#ifndef _XPC_YX_POINT_H
#define _XPC_YX_POINT_H

//顶点坐标
struct Vertex
{
	double fX;
	double fY;
	double fZ;
};

//顶点法线坐标
struct VNormal
{
	double fX;
	double fY;
	double fZ;
};
//顶点纹理坐标
struct TVertex
{
	double fS;
	double fT;
	double fP;
};



//面
struct VertexData
{
	int nVI;
	//纹理
	bool bVt;
	int nVtI;
	//法线
	bool bVn;
	int nVnI;
};

#endif
