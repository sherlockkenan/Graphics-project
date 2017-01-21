#ifndef _XPC_YX_PARTICL_H
#define _XPC_YX_PARTICL_H
#include <GL/glut.h>
#include <GL/gl.h>
#include"point.h"
#include <vector>
using std::vector;



typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	init_x;						// init X Position
	float	init_y;						// init Y Position
	float	init_z;						//init  Z Position

	float	init_xi;						// X speed
	float	init_yi;						// Y speed
	float	init_zi;						// Z speed

	float	x;						// X 
	float	y;						// Y
	float	z;						// Z 

	float	xi;						// X speed
	float	yi;						// Y speed
	float	zi;						// Z speed

	float	xg;						// X 
	float	yg;						// Y 
	float	zg;						// Z 
}
particle;



static GLfloat colors[12][3] =		// Rainbow Of Colors
{
	{0.0f, 10.5f, 255.0f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};


class Generator{
public:
	
	 
   void particleInit();
   void particleInit(vector<Vertex>);
 
   void particleDisplay(int i);

   void particleMainLoop();

protected:

	//粒子数量与对象数组  
	GLuint particleCount=10000;
	particle particles[10000];

	
};
#endif