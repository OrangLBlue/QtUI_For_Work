#ifndef TEST_WIDGET
#define TEST_WIDGET 

#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QMutex>

namespace Ui {
	class CMvTestWidget;
}

class CMvTestWidget : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvTestWidget* Instance();
	//释放内存
	static void destroy();

private slots:

	//选择功能
	void slotSelectFunction(int Index);

	//打开界面
	void slotOpenWindow();
	
private:
	Ui::CMvTestWidget *ui;
	QWidget *m_pTestWidget;

	static CMvTestWidget* s_pTestWidget;

	int m_iFunctionIndex;

	CMvTestWidget(QWidget *parent = Q_NULLPTR);
	~CMvTestWidget();

};

#endif // _DEBUG