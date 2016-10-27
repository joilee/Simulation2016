/************************************************************************/
/*  计算参数的对话框 一个对话框拥有三个页面                                            */
/************************************************************************/

#ifndef COMPUTEOPTION
#define COMPUTEOPTION
#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>




class computerOptionDialog : public QDialog
{
	Q_OBJECT
public:
	computerOptionDialog(QWidget *parent = 0);

	public slots:
			void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private:
	QListWidget *contentsWidget;
	QStackedWidget *pagesWidget;

};

#endif

