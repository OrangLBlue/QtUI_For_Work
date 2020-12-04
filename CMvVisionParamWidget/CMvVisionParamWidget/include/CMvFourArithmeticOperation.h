#ifndef CMVFOURARITHMETICOPERATION_H
#define CMVFOURARITHMETICOPERATION_H

#include <QtWidgets/QWidget>
#include <QComboBox>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvFourArithmeticOperation;
}

class CMvFourArithmeticOperation : public QWidget
{
    Q_OBJECT

public:
	//单实例
	static CMvFourArithmeticOperation * Instance();

	//释放内存
	static void destroy();

	//初始化四则运算选择框
	void initcomboBoxOfOperationChange();

	//初始化菜单
	void initMenuByTest();

	//初始化数据 
	void initCMvFourArithmeticOperation();

private slots:

	//根据点击位置选择弹框
	void slotClickPushButton(int row, int col);

	//菜单动作点击
	void slotMenuTriggered(QAction* action);

	//选择四则运算
	void slotChangeOperation(int index);
private:
    Ui::CMvFourArithmeticOperation *ui;

	static CMvFourArithmeticOperation * s_pFourArithmeticOperation;

	QComboBox *m_comboBox_operationChange;

	bool m_signalEnable;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pvalue1Menu;//数值一菜单
	QMenu* m_pvalue2Menu;//数值二菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_value1MenuData;//数值一菜单数据
	QVector<CMvSecondLevelMenu::cyAction*>  m_value2MenuData;//数值二菜单数据

	CMvFourArithmeticOperation(QWidget *parent = Q_NULLPTR);
	~CMvFourArithmeticOperation();
};

#endif