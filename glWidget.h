//QT�б�дopengl�����õ���QGLWidget���࣬�̳�QGLWidget�࣬��protected��Ա�����������Ա������initializeGL()��paintGL()��resizeGL()

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "util/Color.h"
#include "util/HsvToRgb.h"
#include "util/PredictionIndex.h"
#include "util/vector.h"
#include "util/emxCamera.h"
#include <QPoint>
#include "geometry/emxPoint.h"
#include "geometry/dataStruct.h"
#include "util/EField.h"
#include "antenna.h"
#include <vector>
#include "geometry/emxModel.h"

class emxModel;
class QMouseEvent;
class QWheelEvent;
class TransAntenna;
struct material;
struct field_BestServer;
struct field_SINR;
struct field_Throughput;
struct building;

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();
	void setMaterial(vector<material> &materialdatabase){materials = materialdatabase;}
	void setModel(emxModel* pMesh)
	{
		m_pMesh = pMesh; 
		drawOBJScene = true;
		pMesh->GetBBox(minPos,maxPos);
	}
	void setVectorBuilding(vector<building> &Buildings, Vector3d MaxPoint, Vector3d MinPoint)
	{
		m_Buildings = Buildings;
		drawVectorScene = true;
		minPos = MinPoint;
		maxPos = MaxPoint;
	}
	//void setPath(emxPoint point, int maxBounces) {m_point.InitSize(maxBounces); m_point = point;}
	void setSence(vector<vector<EField>> &PlacePoint){AP_EPoints = PlacePoint;}
	void clearEpoint(){AP_EPoints.clear();horizonNum = 0; veticalNum = 0;}
	void setGrid(int level, int vertical){horizonNum = level; veticalNum = vertical;}
	
	void setSceneIsDisplay(vector<bool>& IsDislpay){sceneIsDislpay = IsDislpay;}
	//����
	bool drawantenna_flag; //�Ƿ񻭳�����
	bool drawscene_flag; //�Ƿ񻭳���
	bool plane_flag; //�Ƿ񻭳�������

	bool drawpath_flag; //�Ƿ񻭳�·��

	bool drawOBJScene; //obj�ļ���������
	bool drawVectorScene;  //vector�ļ���������

	double vis_factor_scence;
	double vis_factor_face;
	int horizonNum;
	int veticalNum;
	int antenna_editNum;
	vector<TransAntenna>draw_antenna;
	
	vector<material> materials;
	double  antenna_posx,antenna_posy,antenna_posz;  //�����ڳ����е�����
	bool flag_rightbutton;//�������Ҽ��Ƿ��£����ж�����λ����������Ϊ�趨�����ǿ���ͨ������϶�
	bool is_change_antennapos; //����λ���Ƿ�ı�
	double getTmax(){return Tmax;}
	double getTmin(){return Tmin;}
	void setTmax(double tmax){Tmax = tmax;}
	void setTmin(double tmin){Tmin = tmin;}
	void updateMesh();

	void drawAntenna();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

private:
	void resetRenderColor();

	void drawPixelBuffer();
	
	void drawGround();

	void drawScene();

	//����λ��ӳ��ƽ��
	//void drawposplane(double viewlength,double viewwidth);

	void drawPath();

	void drawPlane();

	void drawColorbar();

	void drawCoordinates();

	void mousePressEvent(QMouseEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);

	void mouseMoveEvent(QMouseEvent *event);

	void wheelEvent(QWheelEvent *event);

   // void LoadUniformColor(double currentVaule);

	void LoadUniformColor(double currentVaule,Color &result);

private:
	double Tmax;
	double Tmin;
	Color m_backGroundColor;/**< scene background color(OpenGL clear color) */


	// Ground
	Vector3d m_groundCenter;/**< the center position of the ground */
	double m_dGroundWidth;
	int m_iGroundGridNum;
	Color m_groundColor;


	//Light
	Vector3d m_lightPos;	/**< light position */
	Color m_lightColor;		/**< light color */

	emxCamera m_camera;


	int m_iWidth;	/**< the width of the canvas */
	int m_iHeight;	/**< the height of the canvas */

	emxModel *m_pMesh;  //����������Ϣ�����Ƴ���
	Vector3d minPos,maxPos;
	QPoint lastPos,currentPos;

	//emxPoint m_point;
	vector<vector<EField>> AP_EPoints;  //��¼���յ㴦�����Ϣ���Ա������Ļ���

	 vector<building> m_Buildings;  

	 vector<bool> sceneIsDislpay;   //�Ƿ���ʾ������������
};

#endif