#include "object.h"
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "particle.h"

GLfloat sun_light_position[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 0.0f };

const GLfloat pi = 3.14;
GLboolean mouserdown = GL_FALSE;
GLboolean mouseldown = GL_FALSE;
GLboolean mousemdown = GL_FALSE;

static GLint mousex = 0, mousey = 0;

static GLfloat center[3] = { 0.0f, 0.0f, 0.0f };
static GLfloat eye[3];

static GLfloat yrotate = 1.4; 
static GLfloat xrotate =1.4; 
static GLfloat celength = 5.0f;

static GLfloat mSpeed = 0.04f; 
static GLfloat rSpeed = 0.02f; 


int trans=0;
int steps = 200;
int step = 0;


const char* srcObjFileName = "Wolf.obj";
const char* desObjFileName = "cat.obj";


Obj src;
Obj des;

Generator gen = Generator();






int InitGL(GLvoid)
{
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform*/

	//glEnable(GL_DEPTH_TEST);
	src.LoadFromFile(srcObjFileName);
	
	des.LoadFromFile(desObjFileName);
	src.generator.particleInit(src.vs);
	des.generator.particleInit(des.vs);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_NORMALIZE);

    
	//glShadeModel(GL_SMOOTH);


	//maxver = 0;


	//drawSphere(0, 0, 0, 1, 40, 40,&sphere);
	//GetObj("data/teddy.obj",&trans1);
	

	//GetObj("data/teddy.obj", &helper);
	//GetObj("data/monkey.obj", &trans2);

	//sour = &sphere;
	//drawSphere(0, 0, 0, 1, 10, 10, &helper);
	//objallocate(&helper, 10000);
	//objallocate(&helper_sour, 10000);
	//dest = &trans1;
	return true;
}

void DrawGLScene(GLvoid)
{


	if (trans == 0){
		
		src.Render();
		//src.generator.particleMainLoop();
	}
	else if(trans==1){
	
		src.transfer_to_sphere(step,steps);
	}
	else if (trans == 2){
		des.sphere_to_transfer(step,steps);
	}
	else if (trans == 3){
		des.Render();
		des.generator.particleMainLoop();
	}

	
	

	if (trans!=0){
		if (step < steps){
			step++;
		}
		else {
			if (trans == 1){
				trans = 2; step = 0;
			}else if (trans == 2){
				trans = 3; step = 0;
			}
			else if (trans == 3){
				 step = 0;
			}				
			//trans = false; sour = dest; step = 0;
		}
	}
}


void eyepostion()
{
	if (yrotate > pi / 2.2) yrotate = pi / 2.2;   /// 限制看得方向
	if (yrotate < 0.01)  yrotate = 0.01;
	if (xrotate > 2 * pi)   xrotate = 0.01;
	if (xrotate < 0)   xrotate = 2 * pi;
	//if (celength > 50)  celength = 50;
	eye[0] = center[0] + celength * sin(yrotate) * cos(xrotate);
	eye[2] = center[2] + celength * sin(yrotate) * sin(xrotate);
	eye[1] = center[1] + celength * cos(yrotate);
}

/// center moves
void MoveBackward()              /// center 点沿视线方向水平向后移动
{
	center[0] += mSpeed * cos(xrotate);
	center[2] += mSpeed * sin(xrotate);
	eyepostion();
}

void MoveForward()
{
	center[0] -= mSpeed * cos(xrotate);
	center[2] -= mSpeed * sin(xrotate);
	eyepostion();
}

void MoveLeft()
{
	center[0] += mSpeed * sin(xrotate);
	center[2] -= mSpeed * cos(xrotate);
	eyepostion();
}

void MoveRight()
{
	center[0] -= mSpeed * sin(xrotate);
	center[2] += mSpeed * cos(xrotate);
	eyepostion();
}

void Reset(){
	center[0] = 0;
	center[2] = 0;
	center[1] = 0;
}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': MoveLeft(); break;
	case 'd': MoveRight(); break;
	case 's': MoveForward(); break;
	case 'w': MoveBackward(); break;
	case 'r':Reset(); break;
	case '1': {
		
		trans = 1;
		
		break;

	}


	}
	glutPostRedisplay();
}

/// CALLBACK func for mouse kicks
void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_RIGHT_BUTTON) mouserdown = GL_TRUE;
		if (button == GLUT_LEFT_BUTTON) mouseldown = GL_TRUE;
		if (button == GLUT_MIDDLE_BUTTON)mousemdown = GL_TRUE;
	}
	else
	{
		if (button == GLUT_RIGHT_BUTTON) mouserdown = GL_FALSE;
		if (button == GLUT_LEFT_BUTTON) mouseldown = GL_FALSE;
		if (button == GLUT_MIDDLE_BUTTON)mousemdown = GL_FALSE;
	}
	mousex = x, mousey = y;
}

/// CALLBACK func for mouse motions
void Mousemotion(int x, int y)
{
	if (mouseldown == GL_TRUE)
	{
		xrotate += (x - mousex) *rSpeed;
		yrotate -= (y - mousey) *rSpeed;
	}

	if (mousemdown == GL_TRUE)
	{
		celength += (y - mousey) *mSpeed;
	}
	mousex = x, mousey = y;
	eyepostion();
	glutPostRedisplay();
}



void changeSize(int w, int h) {


	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;


	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}
void renderScene() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	//GLfloat gAmbient[] = { 0.6, 0, 6, 0, 6, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmbient);
	// Reset transformations
	glLoadIdentity();

	// Set the camera
	//glMatrixMode(GL_MODELVIEW);

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	eyepostion();



	//glColor3f(1.0f, 0.0f, 0.0f);
	//glutWireTeapot(0.5f);
	DrawGLScene();
	//drawSphere(0, 0, 0, 3, 200, 200);
	//glutSolidSphere(0.5f, 20, 20);

	glFlush();
	glutSwapBuffers();
}
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("ObjLoader");
	InitGL();

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Mousemotion);
	glutMainLoop();


	return 0;
}