#include"stdafx.h"
#include"Cube.h"

MCube::MCube(int width, int height) :Shape(width,height)
{
	degreex = degreey = 0;
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	vertex[0][0] = { 0.5, 0.5, 0.5 };
	vertex[0][1] = { -0.5, 0.5, 0.5 };
	vertex[0][2] = { -0.5, -0.5, 0.5 };
	vertex[0][3] = { 0.5, -0.5, 0.5 };

	vertex[1][0] = { 0.5, 0.5, -0.5 };
	vertex[1][1] = { -0.5, 0.5, -0.5 };
	vertex[1][2] = { -0.5, -0.5, -0.5 };
	vertex[1][3] = { 0.5, -0.5, -0.5 };

	vertex[2][0] = { 0.5, 0.5, 0.5 };
	vertex[2][1] = { 0.5, -0.5, 0.5 };
	vertex[2][2] = { 0.5, -0.5, -0.5 };
	vertex[2][3] = { 0.5, 0.5, -0.5 };

	vertex[3][0] = { -0.5, 0.5, 0.5 };
	vertex[3][1] = { -0.5, -0.5, 0.5 };
	vertex[3][2] = { -0.5, -0.5, -0.5 };
	vertex[3][3] = { -0.5, 0.5, -0.5 };

	vertex[4][0] = { 0.5, 0.5, 0.5 };
	vertex[4][1] = { -0.5, 0.5, 0.5 };
	vertex[4][2] = { -0.5, 0.5, -0.5 };
	vertex[4][3] = { 0.5, 0.5, -0.5 };

	vertex[5][0] = { 0.5, -0.5, 0.5 };
	vertex[5][1] = { -0.5, -0.5, 0.5 };
	vertex[5][2] = { -0.5, -0.5, -0.5 };
	vertex[5][3] = { 0.5, -0.5, -0.5 };
}

void MCube::Draw(){

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(degreex, 0, 1, 0);
	glRotatef(degreey, 1, 0, 0);

	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				glVertex3f(vertex[i][j].x,vertex[i][j].y,vertex[i][j].z);
			}
		}
		
	}
	glEnd();

	glPopMatrix();

}

MCube::~MCube()
{
	glDisable(GL_DEPTH_TEST);
}
void MCube::moveTo(int x, int y){}
void MCube::rotate(int x, int y, int degree){}
void MCube::scale(double x, double y){
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			vertex[i][j].x *= x;
			vertex[i][j].y *= x;
			vertex[i][j].z *= x;
		}
	}
}
void MCube::FillShape(double r, double g, double b){}
void MCube::cut(int left, int top, int right, int bottom){}