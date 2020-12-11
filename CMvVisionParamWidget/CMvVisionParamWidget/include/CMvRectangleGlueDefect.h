#ifndef CMV_RECTANGLE_GLUE_DEFECT
#define CMV_RECTANGLE_GLUE_DEFECT

#include "CMvSecondLevelMenu.h"
#include <QMenu>

namespace Ui {
	class CMvRectangleGlueDefect;
}

class CMvRectangleGlueDefect : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvRectangleGlueDefect* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();


	//初始化数据
	void initCMvRectangleGlueDefect();
	//void testInit();

private slots:
	/*===============================================================================================*\
	**======================================输入设置槽函数===========================================**
	\*===============================================================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

	/*===============================================================================================*\
	**=================================二级菜单相关槽函数声明========================================**
	\*===============================================================================================*/
	//菜单动作点击
	void soltMenuTriggered(QAction*);

	//根据点击位置选择弹框
	void slotClickPushButton(int, int);

	/*===============================================================================================*\
	**=======================================结果判断槽函数==========================================**
	\*===============================================================================================*/
	//获取颜色空间
	void slotGetColorSpaceValue(int index);

	//点击显示颜色直方图
	void slotGetUnqualifiedPiontIsClick();

	//获取滤波尺寸
	void slotGetFilteringSizeValue(int index);

	//获取图像显示
	void slotGetImageDisplayIsChecked(bool State);

	//获取涂胶显示
	void slotGetGlueDisplayIsChecked(bool State);

	//获取杂点剔除面积上限 数值
	void slotGetMaxAreaValue(int Value);

	//获取杂点剔除面积下限 数值
	void slotGetMinAreaValue(int Value);

	//获取涂胶宽度上限 数值
	void slotGetWidthMaxValue(int Value);

	//获取涂胶宽度下限 数值
	void slotGetWidthMinValue(int Value);

	//获取异胶最小长度 数值
	void slotGetMinimumLengthValue(double Value);

	//获取开槽数量 数值
	void slotGetlSotsNumberValue(int Value);

	//获取开槽长度上限 数值
	void slotGetMaxLengthValue(int Value);

	//获取开槽长度下限 数值
	void slotGetMinLengthValue(int Value);

	//获取断胶最小长度 数值
	void slotGetBreakdownValue(double Value);

	//获取涂胶圆角半径 数值
	void slotGetGlueingValue(double Value);

	//获取孔洞最小面积 数值
	void slotGetHoleValue(double Value);

	/*===============================================================================================*\
	**=======================================结果绘制页面槽函数======================================**
	\*===============================================================================================*/
	//获取启动绘制选中信息
	void slotGetStartUpDrawingValue(bool State);


	/*===============================================================================================*\
	**======================================功能栏槽函数=============================================**
	\*===============================================================================================*/
	//点击 放大
	void slotAmplifyThePictureIsClick();

	//点击 缩小
	void slotShrinkThePictureIsClick();

	//点击 最好尺寸
	void slotBestSizeOfPictureIsClick();

	//点击 锁定ROI
	void slotLockROIIsClick();

	//点击 单次
	void slotOnceIsClick();

	//点击 确定
	void slotMakeSureIsClick();

	//点击 取消
	void slotCancelIsClick();
	
private:
	Ui::CMvRectangleGlueDefect *ui;

	static CMvRectangleGlueDefect* s_pCMvRectangleGlueDefect;

	CMvRectangleGlueDefect(QWidget *parent = Q_NULLPTR);
	~CMvRectangleGlueDefect();

	bool m_signalEnable;
	
	/*===============================================================================================*\
	**===============================二级菜单相关成员变量定义========================================**
	\*===============================================================================================*/
	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;
	
	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pImageSourceMenu;//图片来源菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_allImageSourceMenuData;//图片来源菜单数据

};

#endif // _DEBUG