#ifndef _XPC_YX_OBJ_H
#define _XPC_YX_OBJ_H
#include "point.h"
#include "mtl.h"
#include <vector>
#include "particle.h"
using std::vector;

//objģ��
class Obj
{
	friend class Face;
	
public:
	Obj() { }
	int LoadFromFile(const char* FileName);
	int LoadMaterials(const char* FileName);
	void Render();


	Generator generator;
	vector<Vertex> vs;//�������꼯��

	void transfer_to_sphere(int step,int steps);//����,��Ϊ��
	void sphere_to_transfer(int step, int steps);//���Σ����Ϊ����
	//��Ӧ��Ķ���
	vector<Vertex> Sphere_vs;

private:
	
	vector<TVertex> vts;  //�����������꼯��
	vector<VNormal> vns;    //���㷨�߼���
	vector<Face> fs;      //�漯��
	vector<MTL> ms;   //���ʿ�
};



class Face
{
	friend class Obj;
public:
	Face() { nNewMtlI = -1; }

private:

	//���ı�Ϊ-1
	int nNewMtlI;
	vector<VertexData> vds;

};
 
#endif
