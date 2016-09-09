#include "glWidget.h"
#include <gl/freeglut.h>
#include "geometry/emxModel.h"
#include <QMouseEvent>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <QtWidgets/QToolTip>
//���캯��
GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
m_pMesh(NULL),drawscene_flag(0),plane_flag(0),drawantenna_flag(0),
drawpath_flag(0),is_change_antennapos(0),flag_rightbutton(0),antenna_editNum(-1),drawOBJScene(false),drawVectorScene(false)
{
	m_lightPos = Vector3d(-0.55, 0.55,20);
	resetRenderColor();
	// Ground
	m_groundCenter = Vector3d(0, 0, 0);
	m_dGroundWidth = 5;
	m_iGroundGridNum = 20;
	vis_factor_scence = 0.5;
	vis_factor_face = 0.5;

	setMouseTracking(true);

}

GLWidget::~GLWidget()
{
	delete m_pMesh;
	m_pMesh = NULL;

	vector<vector<EField>>().swap(AP_EPoints);

	vector<building>().swap(m_Buildings);  

	vector<bool>().swap(sceneIsDislpay); 
}

void GLWidget::initializeGL()
{
	//�����������
	float mat_specular   [] = {0.3f, 0.3f, 0.3f, 0.3f };
	float mat_shininess  [] = { 100.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);  
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);  
	
	 //������Դ
	// setup light0
	float light0_position[] = { m_lightPos.x, m_lightPos.y, m_lightPos.z, 0 };
	float light0_diffuse [] = { m_lightColor.r, m_lightColor.g, m_lightColor.b, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);  //��Դλ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);  //ɢ���
	
	//setup light1
	/*
	float light1_position[]={2.0,2.0,2.0,1.0};  //λ���Թ�Դ
	float light1_diffuse[]={1.0,1.0,1.0,1.0};   //ɢ���
	float light1_specular[]={1.0,1.0,1.0,1.0};  //�����
	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	*/

	 //�������ģ��
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	glClearColor(m_backGroundColor.r , m_backGroundColor.g, m_backGroundColor.b, 0.0);   //���õ�ǰ�����ɫ
	glShadeModel(GL_SMOOTH);  //ƽ����ɫ

	//glColor4f(1.0f,1.0f,1.0f,0.5f);			// ȫ���ȣ� 50% Alpha ���
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// ����Դ����alphaͨ��ֵ�İ�͸����Ϻ���

	
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //���趨�ĵ�ǰ���ֵ���ָ���Ļ�����

	m_camera.setupModelMatrix();
	
	//���Ƴ���
	if(drawscene_flag)	
		drawScene();

	//��������
	if (drawantenna_flag)
		drawAntenna();

	//���Ʒ�����
	if(plane_flag)
		drawPlane();

	//����������
	drawCoordinates();

	
	//���ƴ���·��
	if (drawpath_flag)
	{
		drawPath();
	}
}

void GLWidget::resizeGL(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;

	// set OpenGL viewport
	glViewport(0, 0, width, height);
	m_camera.setWindowSize(width, height);
	m_camera.setPerspectiveProjection();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void  CALLBACK vertexCallback(GLvoid *vertex)  //��������Ϣ
{  
	const GLdouble *pointer = (GLdouble *) vertex;  
	//glColor3dv(pointer + 3);//�ڴ�������ɫ  
	glVertex3dv(pointer);  
}  
void CALLBACK beginCallback(GLenum which)  
{  
	glBegin(which);  
}  
void CALLBACK endCallback  ()  
{  
	glEnd();  
}  
void CALLBACK errorCallback(GLenum errorCode)  
{  
	const GLubyte *estring;  
	estring = gluErrorString(errorCode);  
	fprintf(stderr, "Tessellation Error: %s\n", estring);  
	exit(0);  
}  
void CALLBACK combineCallback(GLdouble coords[3],  
							  GLdouble *vertex_data[4],  
							  GLfloat weight[4], GLdouble **dataOut )  
{  
	GLdouble *vertex;  
	int i;  
	vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));  
	vertex[0] = coords[0];  
	vertex[1] = coords[1];  
	vertex[2] = coords[2];  
	for (i = 3; i < 7; i++)  
	{  
		vertex[i] = weight[0] * vertex_data[0][i]  
		+ weight[1] * vertex_data[1][i]  
		+ weight[2] * vertex_data[2][i]  
		+ weight[3] * vertex_data[3][i];  
	}  
	*dataOut = vertex;  
} 
//���Ƴ���
void GLWidget::drawScene()
{
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();

	if (drawOBJScene) //��ȡ����obj��ʽ�ļ���չʾ
	{
		glBegin(GL_TRIANGLES);
		size_t faceNum = m_pMesh->NumF();
		for(size_t i = 0; i < faceNum; ++i)
		{
			for(int j = 0;j < materials.size();j++)
			{
				if (materials[j].Id == m_pMesh->getMtlId(i))
				{
					glColor4d((materials[j].color.r)/256.f, (materials[j].color.g)/256.f, (materials[j].color.b)/256.f, vis_factor_scence);
				}
			}
			Vector3i vertexID = m_pMesh->GetFace(i);
			Vector3d v0 = m_pMesh->GetVertex(vertexID.x);
			Vector3d v1 = m_pMesh->GetVertex(vertexID.y);
			Vector3d v2 = m_pMesh->GetVertex(vertexID.z);

			Vector3d faceNormal = m_pMesh->GetNormal(i);
			glNormal3d(faceNormal.x, faceNormal.y, faceNormal.z);
			glVertex3d(v0.x, v0.y, v0.z);
			glVertex3d(v1.x, v1.y, v1.z);
			glVertex3d(v2.x, v2.y, v2.z);
		}
		glEnd();	
	}
	if (drawVectorScene) //��ȡ����vector�ļ���չʾ
	{
		GLUtesselator *tobj = gluNewTess();  
		if (!tobj) 
		{   
			return;   
		}  
		gluTessCallback(tobj, GLU_TESS_VERTEX, (void (CALLBACK *)())vertexCallback);  
		gluTessCallback(tobj, GLU_TESS_BEGIN, (void (CALLBACK *)())beginCallback);  
		gluTessCallback(tobj, GLU_TESS_END, (void (CALLBACK *)())endCallback);  
		//gluTessCallback(tobj, GLU_TESS_ERROR, (void (CALLBACK *)())errorCallback);  
		//gluTessCallback(tobj, GLU_TESS_COMBINE, (void (CALLBACK *)())combineCallback);  
	
		//glColor4d(128/256.f, 128/256.f, 128/256.f,vis_factor_scence);
		glColor4d(1, 1, 1,vis_factor_scence);
		for(int buildings_id = 0; buildings_id < m_Buildings.size(); buildings_id++)
		{
			double building_height = m_Buildings[buildings_id].height; //������ĸ߶�
			gluTessBeginPolygon(tobj, NULL); 
			//�������϶���
			GLdouble (*a)[3] = new GLdouble[m_Buildings[buildings_id].upper_facePoint.size() -1][3];
			gluTessBeginContour(tobj); 
			for (int id = 0; id < m_Buildings[buildings_id].upper_facePoint.size()-1; id++) //��¼building���������ʱ����ĩ���غϣ���¼���Σ�����   .size����-1
			{
				a[id][0] = m_Buildings[buildings_id].upper_facePoint[id].x;
				a[id][1] = m_Buildings[buildings_id].upper_facePoint[id].y;
				a[id][2] =	m_Buildings[buildings_id].upper_facePoint[id].z;	
				gluTessVertex(tobj, a[id], a[id]); 
			}
			gluTessEndContour(tobj); 
			gluTessEndPolygon(tobj);
			delete []a;

			gluTessBeginPolygon(tobj, NULL); 
			//�������µ���
			GLdouble (*b)[3] = new GLdouble[m_Buildings[buildings_id].upper_facePoint.size() -1][3];
			gluTessBeginContour(tobj); 
			for (int id = 0; id < m_Buildings[buildings_id].upper_facePoint.size()-1; id++)
			{
				b[id][0] = m_Buildings[buildings_id].upper_facePoint[id].x;
				b[id][1] = m_Buildings[buildings_id].upper_facePoint[id].y;
				b[id][2] = m_Buildings[buildings_id].upper_facePoint[id].z - building_height;	
				gluTessVertex(tobj, b[id], b[id]); 
			}
			gluTessEndContour(tobj); 
			gluTessEndPolygon(tobj);
			delete []b;

			//���������
			glBegin(GL_QUADS);
			for (int id = 0; id < m_Buildings[buildings_id].upper_facePoint.size()-1; id++)
			{
				glVertex3d(m_Buildings[buildings_id].upper_facePoint[id].x,m_Buildings[buildings_id].upper_facePoint[id].y,m_Buildings[buildings_id].upper_facePoint[id].z);
				glVertex3d(m_Buildings[buildings_id].upper_facePoint[id+1].x,m_Buildings[buildings_id].upper_facePoint[id+1].y,m_Buildings[buildings_id].upper_facePoint[id+1].z);
				glVertex3d(m_Buildings[buildings_id].upper_facePoint[id+1].x,m_Buildings[buildings_id].upper_facePoint[id+1].y,m_Buildings[buildings_id].upper_facePoint[id+1].z - building_height);
				glVertex3d(m_Buildings[buildings_id].upper_facePoint[id].x,m_Buildings[buildings_id].upper_facePoint[id].y,m_Buildings[buildings_id].upper_facePoint[id].z - building_height);
			}
			glEnd();
		}	 
		gluDeleteTess(tobj);   		
	}
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}
//��������
void GLWidget::drawAntenna()
{
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	for (int i=0;i<draw_antenna.size();i++)
	{
		double length1=maxPos.x-minPos.x;
		double width1=maxPos.y-minPos.y;
		glPushMatrix();
		if (flag_rightbutton && i==antenna_editNum) //������Ҽ�press�������ͨ������϶����ı�����λ�ã���������Ϊ�����趨����λ��
		{
			double scalex=width()/length1;
			double scaley=height()/width1;
			double scale=Min(scalex,scaley);
			antenna_posx=length1/2+(width()/2-currentPos.x())/scale;
			antenna_posy=width1/2+(height()/2-currentPos.y())/scale;
			antenna_posz = draw_antenna[i].position.z;
			glTranslated(antenna_posx,antenna_posy,antenna_posz);
		}
		else
		{
			glTranslated(draw_antenna[i].position.x,draw_antenna[i].position.y,draw_antenna[i].position.z);
		}
		double a_cube=width1/100;  //��ʾ���ߵ�cube�߳�
		
		glColor3d(1.0,1.0,0.0);
		glBegin(GL_QUADS);	//  �������������

		//�϶���
		glNormal3d(0.0,0.0,1.0);
		glVertex3d(a_cube,a_cube,a_cube);					
		glVertex3d(-a_cube,a_cube,a_cube);					
		glVertex3d(-a_cube,-a_cube,a_cube);					
		glVertex3d(a_cube,-a_cube,a_cube);	

		//�µ���
		glNormal3d(0.0,0.0,-1.0);
		glVertex3d(a_cube,a_cube,-a_cube);					
		glVertex3d(a_cube,-a_cube,-a_cube );					
		glVertex3d(-a_cube,-a_cube,-a_cube );					
		glVertex3d(-a_cube,a_cube,-a_cube);	

		//ǰ��
		glNormal3d(0.0,1.0,0.0);
		glVertex3d(a_cube,a_cube,a_cube);					
		glVertex3d(a_cube,a_cube,-a_cube );					
		glVertex3d(- a_cube,a_cube,-a_cube );					
		glVertex3d(-a_cube,a_cube,a_cube);

		//����
		glNormal3d(0.0,-1.0,0.0);
		glVertex3d(a_cube,-a_cube,a_cube);					
		glVertex3d(-a_cube,-a_cube,a_cube );					
		glVertex3d(-a_cube,-a_cube,-a_cube );					
		glVertex3d(a_cube,-a_cube,-a_cube);


		//�����
		glNormal3d(1.0,0.0,0.0);
		glVertex3d(a_cube,a_cube,a_cube);					
		glVertex3d(a_cube,-a_cube,a_cube );					
		glVertex3d(a_cube,-a_cube,-a_cube );					
		glVertex3d(a_cube,a_cube,-a_cube);

		//�Ҳ���
		glNormal3d(-1.0,0.0,0.0);
		glVertex3d(-a_cube,a_cube,a_cube);					
		glVertex3d(-a_cube,a_cube,-a_cube );					
		glVertex3d(-a_cube,-a_cube,-a_cube );					
		glVertex3d(-a_cube,-a_cube,a_cube);

		glEnd();	
		glPopMatrix();
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_BLEND);
}
//���Ʒ�����
void GLWidget::drawPlane()  //���ݽ��ܵ㴦��ǿֵ��С��������ɫ���л���
{
	//int min_id = 0;
	for (int id=0;id<AP_EPoints.size();id++)
	{
		if (sceneIsDislpay[id])  //ѡ�е�С��������ʾ������
		{
			vector<EField> &EPoint = AP_EPoints[id];
			double emax = EPoint[0].MolStrength;
			double emin = EPoint[0].MolStrength;
			for(size_t m = 1; m < EPoint.size(); m++)
			{
				if (EPoint[m].Path.size() > 0) //��EPoint[i].Path.size() == 0 ˵�����˽��յ�û��·������ź�ǿ��ֵδ֪
				{
					if(EPoint[m].MolStrength > emax)
					{
						emax = EPoint[m].MolStrength;
					}
					if(EPoint[m].MolStrength < emin)
					{
						emin = EPoint[m].MolStrength;
					//	min_id = m;
					}
				}
			}
		//	cout<<"the minimal point id is:"<<min_id<<endl;
			for (size_t n = 0; n< EPoint.size();n++)
			{
				if (EPoint[n].Path.size() == 0) //����û��·������Ľ��յ㣬�ź�ǿ����Ϊ��Сֵ
				{
					EPoint[n].MolStrength = emin;
				}
			}
			Tmax = emax;
			Tmin = emin;

			drawColorbar();

			double length = emax - emin;

			glEnable(GL_BLEND); //���û��
			glPushMatrix();
			glBegin(GL_QUADS);
			for(int i = 0; i < veticalNum-1; i++)
			{
				for(int j = 0; j < horizonNum-1; j++)
				{
					Vector3d v1 = EPoint[j*veticalNum + i].Position;
					Vector3d v2 = EPoint[j*veticalNum + i + 1].Position;
					Vector3d v4 = EPoint[(j+1)*veticalNum + i].Position;
					Vector3d v3 = EPoint[(j+1)*veticalNum + i + 1].Position;
					double c1 = (EPoint[j*veticalNum + i].MolStrength - emin)/length;
					double c2 = (EPoint[j*veticalNum + i +1].MolStrength - emin)/length;
					double c4 = (EPoint[(j+1)*veticalNum + i].MolStrength - emin)/length;
					double c3 = (EPoint[(j+1)*veticalNum + i + 1].MolStrength - emin)/length;

					Color result(0.5, 0.0, 0.0); 

					LoadUniformColor(c1,result);
					glColor4d(result.r, result.g, result.b, vis_factor_face);
					glVertex3d(v1.x, v1.y, v1.z);
					LoadUniformColor(c2,result);
					glColor4d(result.r, result.g, result.b, vis_factor_face);
					glVertex3d(v2.x, v2.y, v2.z);
					LoadUniformColor(c3,result);
					glColor4d(result.r, result.g, result.b, vis_factor_face);
					glVertex3d(v3.x, v3.y, v3.z);
					LoadUniformColor(c4,result);
					glColor4d(result.r, result.g, result.b, vis_factor_face);
					glVertex3d(v4.x, v4.y, v4.z);
				}
			}
			glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		}		
	}
}

//����������
void GLWidget::drawCoordinates()
{
	GLUquadricObj* quadratic=gluNewQuadric(); 
	gluQuadricNormals(quadratic, GLU_SMOOTH); 
	gluQuadricTexture(quadratic, GL_FALSE);

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST); 

	glMatrixMode(GL_PROJECTION); 
	glPushMatrix();
	glLoadIdentity(); 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int ww = width() / 4;
	if (ww > 128) ww = 128;
	glViewport(0, 0, ww + 20, (GLint)ww + 20);
	glOrtho(-24, 24, -24, 24, -24, 24); 

	//��������
	glMultMatrixd(m_camera.getRotateMatrix());
	glColor3f(1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, 12.0f ,32, 32);
	glTranslatef(0.0, 0.0, 12.0f); 
	gluCylinder(quadratic, 2.0f, 0.0f, 4.0f, 32, 32);
	glRasterPos3f (0.0, 0.0, 8);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,'z');
	glTranslatef(0.0, 0.0, -12.0f);
	glRotated(-90, 1.0, 0.0, 0.0); 
	glColor3f( 0.0, 1.0, 0.0 );
	gluCylinder(quadratic, 1.0f, 1.0f, 12.0f ,32, 32); 
	glTranslatef(0.0, 0.0, 12.0f);
	gluCylinder(quadratic, 2.0f, 0.0f, 4.0f, 32, 32);
	glRasterPos3f (0.0, 0.0, 8); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,'y'); 
	glTranslatef(0.0, 0.0, -12.0f); 
	glRotated(90, 0.0, 1.0, 0.0); 
	glColor3f(0.0, 0.0, 1.0); 
	gluCylinder(quadratic, 1.0f, 1.0f, 12.0f ,32, 32); 
	glTranslatef(0.0, 0.0, 12.0f); 
	gluCylinder(quadratic, 2.0f, 0.0f, 4.0f, 32, 32);
	glRasterPos3f (0.0, 0.0, 8); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,'x');

	glMatrixMode(GL_PROJECTION); 
	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix(); 

	glViewport(0, 0, (GLint)width(), (GLint)height());  //�ӿڻ�ԭΪԭʼ��������Ļ
	glDisable(GL_BLEND);
	gluDeleteQuadric(quadratic); 
}
//����Colorbar
void GLWidget::drawColorbar()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
	int viewWidth = width() / 10;
	if (viewWidth>80) viewWidth = 80;
	int viewheight = height() / 2;

	glViewport(width() - viewWidth - 20, height() - viewheight - 20, viewWidth, viewheight);  //�ӿڣ����ڣ��任
	gluOrtho2D(0, viewWidth, 0, viewheight);  //��ͶӰ

	int cx = 0,cy = 0,cw = viewWidth / 4,ch = viewheight;
	
	// Draw Color Bar 6����ɫ 
	cy = ch;
	ch = - ch;

	glBegin (GL_QUAD_STRIP);      //

	glColor3f( 1.0 ,0.0 ,0.0 ) ;	   //�� 
	glVertex2i(cx,cy);
	glVertex2i(cx+cw,cy);

	glColor3f(  1.0 ,0.5 ,0.0 );	   //�ۻ�
	glVertex2i(cx,cy+ch/5);
	glVertex2i(cx+cw,cy+ch/5);

	glColor3f( 1.0 ,1.0 ,0.0);	   //��
	glVertex2i(cx,cy+2*ch/5);
	glVertex2i(cx+cw,cy+2*ch/5);

	glColor3f( 0.0 ,1.0 ,0.0);	   //��
	glVertex2i(cx,cy+3*ch/5);
	glVertex2i(cx+cw,cy+3*ch/5);

	glColor3f( 0.0 ,1.0 ,1.0);	   //�� 
	glVertex2i(cx,cy+4*ch/5);
	glVertex2i(cx+cw,cy+4*ch/5);

	glColor3f( 0.0 ,0.0 ,1.0);	   //��
	glVertex2i(cx,cy+5*ch/5);
	glVertex2i(cx+cw,cy+5*ch/5);

	glEnd(); 

	// Draw the outline of color bar
	glColor3ub(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(cx,cy);
	glVertex2i(cx+cw,cy);
	glVertex2i(cx+cw,cy+ch);
	glVertex2i(cx,cy+ch);
	glEnd();

	// Draw the coordinate values
	double y;
	double strength[6];
	for(int i=0;i<=5;i++)
	{
		y=cy+i*ch/5.0;
		glBegin(GL_LINES);
		glVertex2i(cx+cw,y);
		glVertex2i(cx+cw+1,y);
		glEnd();
		
		strength[i] = Tmax - (Tmax - Tmin)*i/5.0;

		char* format;
		format = new char[30]; 
		
		/*
		����gcvt(double number,size_t ndigits,char *buf)���Ѹ�����numberת�����ַ���(����С�������������)��
		����ndigits��ʾ����ʾ��λ��(����������),������ָ����ַ�����ָ��buf
		*/
		if(strength[i]>=-1000 && strength[i]<-100)
		{
			gcvt(strength[i], 5, format);  
		}
		else if(strength[i]>=-100 && strength[i]<-10)
		{
			gcvt(strength[i], 4, format);
		}
		else if (strength[i]>=-10 && strength[i]<10)
		{
			gcvt(strength[i], 3, format);
		}
		else if (strength[i]>=10 && strength[i]<100)
		{
			gcvt(strength[i], 4, format);
		}
		else if (strength[i]>=100 && strength[i]<1000)
		{
			gcvt(strength[i], 5, format);
		}
		else if (strength[i]>=1000 && strength[i]<10000)
		{
			gcvt(strength[i], 6, format);
		}
		else if (strength[i]>=10000 && strength[i]<100000)
		{
			gcvt(strength[i], 7, format);
		}

		/*va_list args;
		char buffer[255], *s;
		va_start(args, format);
		vsprintf(buffer, format, args);
		va_end(args);
		glRasterPos2f(cx+cw+2,y);
		for(s = buffer; *s; ++s)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *s);*/

		char *s;
		glRasterPos2f(cx+cw+2,y);
		for(s = format; *s; ++s)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *s);
		delete[] format;
	}
	glMatrixMode(GL_PROJECTION); 
	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix();
	glViewport(0, 0, (GLint)width(), (GLint)height()); //�ӿڻ�ԭΪԭʼ��������Ļ
}

/*
//����λ��ӳ��ƽ��
void GLWidget::drawposplane(double viewlength,double viewwidth)
{
	double  a=viewwidth/30;

	//	double x=width()-viewlength-20;
	double x=20;
	double y=height()-viewwidth-20;

	double posx=currentPos.x();
	double posy=currentPos.y();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glViewport(x,y,(GLsizei)viewlength,(GLsizei)viewwidth);  //�ӿڣ����ڣ��任
	gluOrtho2D(0.0, viewlength, 0.0,viewwidth);  //ͶӰ�任

	glBegin(GL_QUADS);

	//����λ��ӳ��ƽ��
	glColor3d(0.5,0.5,0.8);
	glVertex2d(0.0,0.0);
	glVertex2d(viewlength,0.0);
	glVertex2d(viewlength,viewwidth);
	glVertex2d(0.0,viewwidth);

	//��һ��С��������������ӳ��
	glColor3d(1.0,1.0,1.0);
	glVertex2d(posx-x-a,posy-y-a);
	glVertex2d(posx-x+a,posy-y-a);
	glVertex2d(posx-x+a,posy-y+a);
	glVertex2d(posx-x-a,posy-y+a);

	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}
*/
void GLWidget::resetRenderColor()
{
	m_lightColor = Color::LIGHT_GRAY;
	//m_backGroundColor = Color(0.8, 0.8, 0.8);
	m_backGroundColor = Color(130/256.f, 130/256.f, 172/256.f);
	m_groundColor = Color::GRAY;
}

// void GLWidget::drawPixelBuffer()
// {
// 	// Clear color
// 	glClearColor(0.0, 0.0, 0.0, 0.0);
// 	// Clear all pixels.
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 	m_camera.setupModelMatrix();
// 
// 	//drawGround();
// 	glClearColor(m_backGroundColor.r , m_backGroundColor.g, m_backGroundColor.b, 0.0); 
// }
// 
// 
// void GLWidget::drawGround()
// {
// 	double startX = m_groundCenter.x - m_dGroundWidth / 2;
// 	double startY = m_groundCenter.y - m_dGroundWidth / 2;
// 	double endX = m_groundCenter.x + m_dGroundWidth / 2;
// 	double endY = m_groundCenter.y + m_dGroundWidth / 2;
// 
// 	double posX = startX;
// 	Vector3d vec1(0, startY, m_groundCenter.z);
// 	Vector3d vec2(0, endY, m_groundCenter.z);
// 
// 	double posY = startY;
// 	Vector3d vec3(startX, 0, m_groundCenter.z);
// 	Vector3d vec4(endX, 0, m_groundCenter.z);
// 	double delta = m_dGroundWidth / m_iGroundGridNum;
// 
// 	LoadColor(m_groundColor);
// 	glBegin(GL_LINES);
// 	for (int i = 0; i <= m_iGroundGridNum; ++i)
// 	{
// 		vec1.x = vec2.x = posX;
// 		LoadVertex(vec1);
// 		LoadVertex(vec2);
// 
// 		vec3.y = vec4.y = posY;
// 		LoadVertex(vec3);
// 		LoadVertex(vec4);
// 
// 		posX += delta;
// 		posY += delta;
// 	}
// 
// 	//Draw x axis and y axis
// 	LoadColor(Color::BLACK);
// 	delta = m_iGroundGridNum / 2 * delta;
// 	vec1.x = startX + delta;
// 	vec2.x = vec1.x;
// 	vec3.y = startY + delta;
// 	vec4.y = vec3.y;
// 	LoadVertex(vec1);
// 	LoadVertex(vec2);
// 	LoadVertex(vec3);
// 	LoadVertex(vec4);
// 	glEnd();
// }
// 
// 
//���ƴ���·��
 void GLWidget::drawPath()
 {
	 for (int id=0;id<AP_EPoints.size();id++)
	 {
		 if (sceneIsDislpay[id])  //ѡ�е�С��������ʾ������
		 {
			 vector<EField> &EPoint = AP_EPoints[id];
			 //for (int i=0;i<1;i++)
			 for (int i=0;i<EPoint.size();i++)
			 {
				 glColor3d(1.0, 0.0, 0.0);
				 glPushMatrix();
				 glTranslatef(EPoint[i].Position.x,EPoint[i].Position.y,EPoint[i].Position.z);
				 //glutSolidSphere(0.1, 16, 16);
				 glPopMatrix();
				 for (int j=0;j<EPoint[i].Path.size();j++)
				 {
					 vector<Vector3d> &m_point = EPoint[i].Path[j].Path_interPoint;
					 glPushMatrix();
					 //glColor3d(0.0, 0.0, 1.0);
					 glColor3d(1.0, 1.0, 0.0);
					 glBegin(GL_LINES);
					 for(int i = 0; i < m_point.size()-1; i++)
					 {
						 Vector3d startPos = m_point[i];
						 Vector3d endPos  = m_point[i+1];
						 glVertex3d(startPos.x, startPos.y, startPos.z);
						 glVertex3d(endPos.x, endPos.y, endPos.z);
					 }
					 glEnd();
					 glPopMatrix();
				 }
			 }
		 }
	 }
	 
 }

//�������¼�
void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
	//cout<<lastPos.x()<<"  "<<lastPos.y()<<endl;
	if(event->button() == Qt::LeftButton)
	{
		m_camera.beginDrag(lastPos.x(), lastPos.y());
	}
	else if(event->button() == Qt::RightButton)
	{
	}
	else if(event->button() == Qt::MidButton)
	{
		
	}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	/*double length1=maxPos.x-minPos.x;
	double width1=maxPos.y-minPos.y;
	currentPos=QPoint(event->pos().x(),event->pos().y());
	double posx = (width()/2-currentPos.x())/length1;
	double posy = (currentPos.y() - height()/2)/width1;

	QString s1 = QString::number(posx);
	QString s2 = QString::number(posy);
	QString s = s1 + "," + s2;
	QPoint p = event->pos();
	p.setX( p.x());
	p.setY (p.y());
	QToolTip::showText(p, s);*/

	if(event->buttons() & Qt::LeftButton)
	{
		m_camera.mouseMove(event->pos().x(), event->pos().y());
		updateGL();
	}
	else if(is_change_antennapos&&(event->buttons() & Qt::RightButton))
	{
		flag_rightbutton=true;
		currentPos=QPoint(event->pos().x(),height()-event->pos().y());  //����ȡ�Ĵ���y������ʵ�ʴ���y���껥��������height()��ȥ��ȡ��yֵ����������ԭ���ڴ������ϽǴ�
		updateGL();
	}
 	else if(event->buttons() & Qt::MidButton)  //֧��ͼ���ƶ�����
	{
		m_camera.setModelTranslate(event->pos().x() - lastPos.x(), event->pos().y() - lastPos.y());	
		lastPos = event->pos();
		updateGL();
	}	  
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() == Qt::LeftButton) && (event->type() == QEvent::MouseButtonRelease)) 
		m_camera.endDrag(event->pos().x(), event->pos().y());
	
}

//ͨ��������ʵ��ͼ������
void GLWidget::wheelEvent(QWheelEvent *event)
{
	double zoomValue = 1.3;
	//event->delta()����껬���ڹ���ʱ���ڷ��ػ����ľ��룬��ֵ���������ת�Ƕȵ�8����
	if((event->delta())>0)   //����ֵ��ʾ����������û�����ǰ����
		m_camera.zoomIn(zoomValue);
	else if((event->delta())<0)  //����ֵ��ʾ����������û�����󻬶��ġ�
		m_camera.zoomOut(zoomValue);
 	updateGL();	
}
void GLWidget::LoadUniformColor(double currentVaule,Color &result)
{ 
	if(currentVaule <= 0.2) 
		result = Color(0.0,currentVaule * 5,1.0);
	else if(currentVaule <= 0.4)
		result = Color(0.0, 1.0, (0.4 - currentVaule) * 5);
	else if(currentVaule <= 0.6)
		result = Color((currentVaule - 0.4) * 5,1.0,0.0);
	else if(currentVaule <= 0.8)
		result = Color(1.0, (0.8 - currentVaule) * 2.5 + 0.5, 0.0);
	else if(currentVaule <= 1.0)
		result = Color(1.0,(1.0 - currentVaule) * 2.5,0.0);

}

void GLWidget::updateMesh()
{
	m_camera.setSceneBBox(minPos, maxPos);
	// update ground attribute
	Vector3d dist = maxPos - minPos;
	m_groundCenter   = (minPos + maxPos) * .5;
	m_groundCenter.z = minPos.z;
	m_dGroundWidth = Max(dist.x, dist.y) * 5;  //ʹ�����ͱ����ı�����ʾǡ�������������Max(dist.x, dist.y) ��5��
}


