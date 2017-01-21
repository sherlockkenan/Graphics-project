#ifndef _XPC_YX_OBJ_H
#define _XPC_YX_OBJ_H
#include "point.h"
#include "mtl.h"
#include <vector>
#include "particle.h"
using std::vector;

//obj模型
class Obj
{
	friend class Face;
	
public:
	Obj() { }
	int LoadFromFile(const char* FileName);
	int LoadMaterials(const char* FileName);
	void Render();


	Generator generator;
	vector<Vertex> vs;//顶点坐标集合

	void transfer_to_sphere(int step,int steps);//变形,变为球
	void sphere_to_transfer(int step, int steps);//变形，球变为物体
	//对应球的顶点
	vector<Vertex> Sphere_vs;

private:
	
	vector<TVertex> vts;  //顶点纹理坐标集合
	vector<VNormal> vns;    //顶点法线集合
	vector<Face> fs;      //面集合
	vector<MTL> ms;   //材质库
};



class Face
{
	friend class Obj;
public:
	Face() { nNewMtlI = -1; }

private:

	//不改变为-1
	int nNewMtlI;
	vector<VertexData> vds;

};
 
#endif
