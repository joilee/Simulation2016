﻿#include <gl/freeglut.h>
#include "glWidget.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <QtWidgets/QMessageBox>

//构造函数
GLWidget::GLWidget(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	resetRenderColor();
	// Ground
	m_lightPos = Vector3d(-0.55, 0.55,20);

	m_groundCenter = Vector3d(0, 0, 0);
	m_dGroundWidth=5;

	TriangleModel=NULL;

	drawTriangleScene=false;
	drawVectorScene=false;
	vis_factor_scence = 0.5;
	materials.clear();
	defaultMaterial=-1;
	setMouseTracking(true);
}


//绘制多边形的信息
void  CALLBACK vertexCallback(GLvoid *vertex)  //点坐标信息
{  
	const GLdouble *pointer = (GLdouble *) vertex;  
	//glColor3dv(pointer + 3);//在此设置颜色  
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

void GLWidget::initializeGL()
{
	//定义材料属性
	float mat_specular   [] = {0.3f, 0.3f, 0.3f, 0.3f };
	float mat_shininess  [] = { 100.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);  
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);  
	
	 //创建光源
	float light0_position[] = { m_lightPos.x, m_lightPos.y, m_lightPos.z, 0 };
	float light0_diffuse [] = { m_lightColor.r, m_lightColor.g, m_lightColor.b, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);  //光源位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);  //散射光
	
	 //定义光照模型
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	glClearColor(m_backGroundColor.r , m_backGroundColor.g, m_backGroundColor.b, 0.0);   //设置当前清除颜色
	glShadeModel(GL_SMOOTH);  //平滑着色

	//glColor4f(1.0f,1.0f,1.0f,0.5f);			// 全亮度， 50% Alpha 混合
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// 基于源象素alpha通道值的半透明混合函数
}


void GLWidget::paintGL()
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //用设定的当前清除值清除指定的缓冲区
		m_camera.setupModelMatrix();
		if (drawTriangleScene)
		{
			drawLocalScene();
		}
		if (drawVectorScene)
		{
			drawAllScene();
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

GLWidget::~GLWidget()
{

}
void GLWidget::resetRenderColor()
{
	m_lightColor = Color::LIGHT_GRAY;
	m_backGroundColor = Color(130/256.f, 130/256.f, 172/256.f);
	m_groundColor = Color::GRAY;
}

void GLWidget::drawAllScene()
{
	if (drawVectorScene)
	{
		glEnable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_TEST);
		glPushMatrix();

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

		glColor4d(1, 1, 1,vis_factor_scence);

		for(int buildings_id = 0; buildings_id < m_Buildings.size(); buildings_id++)
		{
			double building_height = m_Buildings[buildings_id].height; //建筑物的高度
			gluTessBeginPolygon(tobj, NULL); 
			//建筑物上顶面
			GLdouble (*a)[3] = new GLdouble[m_Buildings[buildings_id].upper_facePoint.size() -1][3];
			gluTessBeginContour(tobj); 
			for (int id = 0; id < m_Buildings[buildings_id].upper_facePoint.size()-1; id++) //记录building顶面点坐标时，首末点重合，记录两次，所以   .size（）-1
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
			//建筑物下底面
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

			//建筑物侧面
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
		glPopMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
	}

	return;
}


/************************************************************************/
/*  绘制场景
此处场景为局部
*/
/************************************************************************/
void GLWidget::drawLocalScene(){

	if (drawTriangleScene) //读取场景obj格式文件并展示
	{
		glEnable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_TEST);
		glPushMatrix();
		glBegin(GL_TRIANGLES);
		size_t faceNum = TriangleModel->NumF();
		for(size_t i = 0; i < faceNum; ++i)
		{
			bool materialFindFlag=false;
			for(int j = 0;j < materials.size();j++)
			{
				if (materials[j].Id == TriangleModel->getMtlId(i))
				{
					glColor4d((materials[j].color.r)/256.f, (materials[j].color.g)/256.f, (materials[j].color.b)/256.f, vis_factor_scence);
					materialFindFlag=true;
					break;//有一个等于即可，颜色信息是相同的
				}
			}
			if (!materialFindFlag)
			{
				glColor4d((materials[defaultMaterial].color.r)/256.f, (materials[defaultMaterial].color.g)/256.f, (materials[defaultMaterial].color.b)/256.f, vis_factor_scence);
			}
			Vector3i vertexID = TriangleModel->GetFace(i);
			Vector3d v0 = TriangleModel->GetVertex(vertexID.x);
			Vector3d v1 = TriangleModel->GetVertex(vertexID.y);
			Vector3d v2 = TriangleModel->GetVertex(vertexID.z);

			Vector3d faceNormal = TriangleModel->GetNormal(i);
			glNormal3d(faceNormal.x, faceNormal.y, faceNormal.z);
			glVertex3d(v0.x, v0.y, v0.z);
			glVertex3d(v1.x, v1.y, v1.z);
			glVertex3d(v2.x, v2.y, v2.z);
		}
		glEnd();	
	}else
	{
		QMessageBox::warning(this, QStringLiteral("场景展示"),QStringLiteral("无法展示局部场景或者OBJ模型！"));
		return;
	}
}

void GLWidget::updateMesh()
{
	m_camera.setSceneBBox(minPos, maxPos);
	// update ground attribute
	Vector3d dist = maxPos - minPos;
	m_groundCenter   = (minPos + maxPos) * .5;
	m_groundCenter.z = minPos.z;
	m_dGroundWidth = Max(dist.x, dist.y) * 5;  //使场景和背景的比例显示恰当，背景宽度是Max(dist.x, dist.y) 的5倍
}

//鼠标跟踪事件
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
	//else if(is_change_antennapos&&(event->buttons() & Qt::RightButton))
	//{
	//	flag_rightbutton=true;
	//	currentPos=QPoint(event->pos().x(),height()-event->pos().y());  //鼠标获取的窗口y坐标与实际窗口y坐标互补，故用height()减去获取的y值，窗口坐标原点在窗口左上角处
	//	updateGL();
	//}
 	else if(event->buttons() & Qt::MidButton)  //支持图形移动功能
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

//通过鼠标滚轮实现图形缩放
void GLWidget::wheelEvent(QWheelEvent *event)
{
	double zoomValue = 1.3;
	//event->delta()当鼠标滑轮在滚动时用于返回滑动的距离，该值等于鼠标旋转角度的8倍。
	if((event->delta())>0)   //正数值表示滑轮相对于用户在向前滑动
		m_camera.zoomIn(zoomValue);
	else if((event->delta())<0)  //负数值表示滑轮相对于用户是向后滑动的。
		m_camera.zoomOut(zoomValue);
 	updateGL();	
}