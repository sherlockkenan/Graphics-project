#ifndef _XPC_YX_POINT_H
#define _XPC_YX_POINT_H

//��������
struct Vertex
{
	double fX;
	double fY;
	double fZ;
};

//���㷨������
struct VNormal
{
	double fX;
	double fY;
	double fZ;
};
//������������
struct TVertex
{
	double fS;
	double fT;
	double fP;
};



//��
struct VertexData
{
	int nVI;
	//����
	bool bVt;
	int nVtI;
	//����
	bool bVn;
	int nVnI;
};

#endif
