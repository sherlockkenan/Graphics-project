#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>	
#include <windows.h>
#include"particle.h"
	


#define	MAX_PARTICLES	1000			

float slowdown=1000000.0;
GLuint	col;						
GLuint	delay;						
GLuint	texture[1];					


bool LoadTexture(LPTSTR szFileName, GLuint &texid) // Creates Texture From A Bitmap File
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
	 //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	 glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, BMP.bmBits);

	
		  DeleteObject(hBMP); // Delete The Object
	
		  return TRUE; // Loading Was Successfu
}


void Generator::particleInit(vector<Vertex>m_vs){
	if (!LoadTexture(L"data/star.bmp", texture[0]))								// Jump To Texture Loading Routine
	{
		return;									// If Texture Didn't Load Return FALSE
	}
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Texture

	//glBlendEquation(GL_ADD);
	//设置材质
	
	//glMaterialf(GL_FRONT, GL_SHININESS, fShiness);

	particleCount = m_vs.size() ;
	double x_sum = 0, y_sum = 0, z_sum = 0;
	for (int i = 0; i < particleCount; i++){
		x_sum += m_vs[i].fX;
		y_sum += m_vs[i].fY;
		z_sum += m_vs[i].fZ;
	}
	double x_avg = z_sum / particleCount;
	double y_avg = y_sum / particleCount;
	double z_avg = z_sum / particleCount;

	for (int loop = 0; loop<particleCount; loop++)				
	{
		particles[loop].active = true;								
		particles[loop].life = 1.0f;								
		particles[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	
		int temp = rand() % 12;
		particles[loop].r = colors[temp][0];	
		particles[loop].g = colors[temp][1];	
		particles[loop].b = colors[temp][2];	
		
		particles[loop].x = m_vs[loop].fX*1.5;                  
		particles[loop].y = m_vs[loop].fY*1.5;
		particles[loop].z = m_vs[loop].fZ*1.5;
		particles[loop].init_x = m_vs[loop].fX*1.5;
		particles[loop].init_y = m_vs[loop].fY*1.5;
		particles[loop].init_z = m_vs[loop].fZ*1.5;
		particles[loop].xi = rand()*(particles[loop].init_x -0) /( abs(particles[loop].init_x)*slowdown);
		particles[loop].yi = rand()* (particles[loop].init_y - 0) /( abs(particles[loop].init_y) *slowdown);
		particles[loop].zi = rand()*(particles[loop].init_z - 0) / (abs(particles[loop].init_z) * slowdown);

		particles[loop].init_xi = particles[loop].xi;	
		particles[loop].init_yi = particles[loop].yi;		
		particles[loop].init_zi = particles[loop].zi;		


		particles[loop].xg = (particles[loop].init_x -x_avg)*float(rand() % 100) / 10000.0f;
		particles[loop].yg = (particles[loop].init_y -y_avg)*float(rand() % 100) / 10000.0f;
		particles[loop].zg = (particles[loop].init_z - z_avg)*float(rand() % 100) / 10000.0f;
	}
}

//粒子渲染函数  
void Generator::particleDisplay(int loop){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer;
	if (particles[loop].active)							// If The Particle Is Active
	{
		float x = particles[loop].x;						
		float y = particles[loop].y;						
		float z = particles[loop].z;					

		// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
		glColor4f(particles[loop].r, particles[loop].g, particles[loop].b,particles[loop].life);

	
		glBegin(GL_TRIANGLE_STRIP);		
	
		glTexCoord2d(1, 1); glVertex3f(x + 0.03f, y + 0.03f, z); // Top Right

		glTexCoord2d(0, 1); glVertex3f(x - 0.03f, y + 0.03f, z); // Top Left

		glTexCoord2d(1, 0); glVertex3f(x + 0.03f, y - 0.03f, z); // Bottom Right

		glTexCoord2d(0, 0); glVertex3f(x - 0.03f, y - 0.03f, z); // Bottom Left
		glEnd();

		particles[loop].x += particles[loop].xi;
		particles[loop].y += particles[loop].yi ;
		particles[loop].z += particles[loop].zi;

		particles[loop].xi += particles[loop].xg/10;			
		particles[loop].yi += particles[loop].yg/10;			
		particles[loop].zi += particles[loop].zg/10;			
		particles[loop].life -= particles[loop].fade/10;		

		if (particles[loop].life < 0.0f)					
		{
			particles[loop].life = 1.0f;					
			particles[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	
			particles[loop].x = particles[loop].init_x;						
			particles[loop].y = particles[loop].init_y;						
			particles[loop].z = particles[loop].init_z;						
			particles[loop].xi = particles[loop].init_xi;		
			particles[loop].yi = particles[loop].init_yi;		
			particles[loop].zi = particles[loop].init_zi;		
			int temp = rand() % 12;
			particles[loop].r = colors[temp][0];	
			particles[loop].g = colors[temp][1];	
			particles[loop].b = colors[temp][2];	

		}
	}

}




//发生器循环函数  
void Generator::particleMainLoop(){
	//glLoadIdentity();
	

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Texture


	for (int i = 0; i < particleCount; i++){
		particleDisplay(i);
	}
}

