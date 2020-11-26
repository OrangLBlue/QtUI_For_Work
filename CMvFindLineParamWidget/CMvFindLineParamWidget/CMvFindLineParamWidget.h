#ifndef CMVFINDLINEPARAMWIDGET_H
#define CMVFINDLINEPARAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>
#include "CySecondLevelMenu.h"

namespace Ui {
class CMvFindLineParamWidget;
}

class CySecondLevelMenu;
class CMvFindLineParamWidget : public QWidget
{
    Q_OBJECT
private:
	Ui::CMvFindLineParamWidget *ui;

	bool m_SignalEnable;

/*==============================二级菜单相关成员变量定义========================================*/
// 记录当前点击的位置
	int m_Row;
	int m_Col;
	CySecondLevelMenu *SecondLevelMenu;//定义类

	QVector<CySecondLevelMenu::cyMenu*>  m_AllImageSourceMenuData;//图片来源菜单数据
	QVector<CySecondLevelMenu::cyMenu*>  m_AllROISourceMenuData;////ROI来源菜单数据
	QVector<CySecondLevelMenu::cyMenu*>  m_AllROIPositionUpdatingMenuData;//ROI位置修正菜单数据
	QVector<CySecondLevelMenu::cyMenu*>  m_AllMaskSourceMenuData;//掩膜来源菜单数据

	QMenu * m_ImageSourceMenu;//图片来源菜单
	QMenu * m_ROISourceMenu;//ROI来源菜单
	QMenu * m_ROIPositionUpdatingMenu;//ROI位置修正菜单
	QMenu * m_MaskSourceMenu;//掩膜来源菜单
/*==============================================================================================*/
public:
	explicit CMvFindLineParamWidget(QWidget *parent = 0);
	~CMvFindLineParamWidget();

	//初始化菜单
	void initMenu();

	void testInit();

private slots:
/*====================================输入设置槽函数=================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

	//获取ROI来源
	void slotGetROISourcesValue(int index);

	//获取自己创建选中信息
	void slotGetCreateYourselfValue(bool state);

	/*==============二级菜单相关槽函数声明================*/
	//菜单动作点击
	void soltMenuTriggered(QAction*);

	//根据点击位置选择弹框
	void slotClickPushButton(int, int);
	/*===================================================*/
/*============================================================================================*/

/*===================================参数设置槽函数==================================================*/
	//获取边缘阈值 数值
	void slotGetEdgeThresholdtValue(int index);

	//获取边缘梯度阈值 数值
	void slotGetEdgeGradientThresholdtValue(int Value);

	//获取边缘极性 数值
	void slotGetCoordinateInputValue(int index);

	//获取扫描点数
	void slotGetScanPointsValue(int Value);

	//获取抽样点数 数值
	void slotGetSamplingPointsValue(int Value);

	//获取检测方向 数值
	void slotGetDirectionOfDetectionValue(int index);

	//获取拟合范围 数值
	void slotGetScopeOfFitValue(int Value);

	//获取拟合误差限制 数值
	void slotGetFittingErrorlimitsValue(int Value);

	//获取最小直线长度 数值
	void slotGetMinimumLineLengthValue(int Value);

    //获取最大直线长度 数值
	void slotGetMaximumLineLengthValue(int Value);
/*============================================================================================*/

/*================================掩膜设置槽函数==========================================*/

	//检测区域的掩膜 数值
	void slotMaskOfDetectionAreaValue(int Index);

	//获取编辑方式 数值
	void slotEditModeValue(int Index);

	//获取画笔尺寸 数值
	void slotBrushSizeValue(int Value);

	//点击清空掩膜
	void slotEmptyMaskIsClick();

	//点击掩盖所有
	void slotCoverUpEverythingClick();

	//点击保存修改
	void slotSaveChangesClick();

/*============================================================================================*/

/*===================================结果绘制槽函数=============================================*/
	//获取线条宽度 数值
	void slotGetLineWidthValue(int Value);

	//获取启动绘制选中信息
	void slotGetStartUpDrawingValue(bool state);

	//获取线条颜色 数值
	void slotGetLineColourValue(int index);
/*============================================================================================*/

/*===================================功能栏槽函数==============================================*/
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
/*=========================================================================================================*/


	/*
    void set_fuc_scene(FucScene *fuc_scene){m_fuc_scene_ptr = fuc_scene;}//![把scene指针传进来]
    void reset_select_out_vector();//![重新更改可以输出的管脚链表，重新刷新combox的内容]
    void init_a_row(int add_row_id, int fuc_id, int leg_out_id, bool check_state);//![外部调用，初始化的时候使用,在函数创建完成以后初始化这个]
	void create_select_out_vector();//![重新更改可以输出的管脚链表]
    void delet_all_row();
    void connect_event();//![连接事件]

protected:
    bool eventFilter(QObject *watched, QEvent *event);//![1.当鼠标点中任何一个控件的时候，选中当前的行，此时就记录了当前的行]

private:
	int m_select_row_id;
    Ui::CMvMassageSet *ui;
    FucScene *m_fuc_scene_ptr;
    QVector<FucLegOut*> m_select_out_vector;//![可以作为输出的的输出管脚]

    void creat_out_string_list(QStringList &fuc_out_string_list);//![创建输出列表的文字]
    void creat_a_row(int row_id);//![创建新的一行]
    void connect_a_row_event(int row_id);//![连接combox和checkbox的事件]

private slots:
    void slot_pushButton_add_massage();
    void slot_pushButton_delet_select_massage();
    void slot_pushButton_move_up_massage();
    void slot_pushButton_move_down_massage();
    void slot_combox0_current_item_change(int current_id);//![第一列的combox选择一项以后，调用此函数]
    void slot_mouse_push_check_change(int state);//![checkbox改变状态的时候调用此函数]

signals:
	void signal_format_type_change(int select_id);
	void signal_check_change(int check_id, bool val);
	void signal_combox_current_item_change(int table_row, int fuc_id, int leg_out_id, bool isActive);
	void signal_move_down_a_massage(int row_id);
	void signal_move_up_a_massage(int row_id);
	void signal_delet_a_select_row(int row_id);
	void signal_add_a_row(int row_id);
	*/
};

#endif // CMVFINDLINEPARAMWIDGET_H
