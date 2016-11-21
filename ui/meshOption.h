#ifndef  MESHOPTION_H
#define MESHOPTION_H
#include "util/vector.h"
#include <QDialog>

class meshOpitionDialog:public QDialog
{
	meshOpitionDialog(QWidget *parent=0);
	~meshOpitionDialog();
public:
	Vector3d center;
	int range;

	void getValue();

protected:
private:
};



#endif