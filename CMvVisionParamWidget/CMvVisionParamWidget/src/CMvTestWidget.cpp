#include <QDebug>
#include "CMvTestWidget.h"
#include "ui_CMvTestWidget.h"
#include "CMvFindRoundParamWidget.h"
#include "CMvFindLineParamWidget.h"
#include "CMvColorImagesCut.h"
#include "CMvBlackAndWhiteConversionColor.h"
#include "CMvColorConversionBlackAndWhite.h"
#include "CMvFourArithmeticOperation.h"
#include "CMvBlobRapidDetection.h"
#include "CMvColorSelection.h"
#include "CMvColorArea.h"
#include "CMvKNNColorSelection.h"
#include "CMvImagesCut.h"
#include "CMvImageRotation.h"
#include "CMvAlgorithmProcessing.h"
#include "CMvAdditionAndSubtraction.h"
#include "CMvImageEnhancement.h"
#include "CMvMultiplicationAndDivision.h"
#include "CMvManualBinary.h"
#include "CMvAdaptiveBinarization.h"
#include "CMvDenoiseBinarization.h"
#include "CMvCannyEdgeExtracting.h"
#include "CMvImageDefect.h"
#include "CMvBarCodeDefect.h"
#include "CMvGraphicDefects.h"
#include "CMvChipDefect.h"
#include "CMvChipMainGrid.h"
#include "CMvContactAttitudeDefect.h"
#include "CMvEdgeDefect.h"
#include "CMvRingGlueDefect.h"
#include "CMvRectangleGlueDefect.h"
#include "CMvPositiveNegativeContacts.h"
#include "CMvRingDefect.h"
#include "CMvTemplateMatching.h"
#include "CMvContourMatching.h"
#include "CMvFeatureMatching.h"


#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvTestWidget * CMvTestWidget::s_pTestWidget = nullptr;

CMvTestWidget::CMvTestWidget(QWidget *parent)
	: QWidget(parent),
      ui(new Ui::CMvTestWidget)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_iFunctionIndex = ui->comboBox_selectionFunction->currentIndex();

	//选择功能
	connect(ui->comboBox_selectionFunction, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSelectFunction(int)));
	
	//打开界面
	connect(ui->pushButton_openWindow, SIGNAL(clicked()), this, SLOT(slotOpenWindow()));

	//设置关闭窗体时释放资源
	m_pTestWidget = nullptr;
	setAttribute(Qt::WA_DeleteOnClose);
}

CMvTestWidget::~CMvTestWidget()
{
	qDebug() << "析构函数";

	//查找直线
	CMvFindLineParamWidget::destroy();
	
	//查找圆
	CMvFindRoundParamWidget::destroy();
	
	//裁剪图片
	CMvColorImagesCut::destroy();
	
	//彩色转黑白
	CMvColorConversionBlackAndWhite::destroy();

	//黑白转彩色
	CMvBlackAndWhiteConversionColor::destroy();

	//四则运算
	CMvFourArithmeticOperation::destroy();
	
	//Blob快速检测
	CMvBlobRapidDetection::destroy();

	//颜色选定
	CMvColorSelection::destroy();

	//KNN颜色选定
	CMvKNNColorSelection::destroy();

	//颜色区域
	CMvColorArea::destroy();

	//图片裁剪
	CMvImagesCut::destroy();

	//图像旋转
	CMvImageRotation::destroy();

	//公式算法处理
	CMvAlgorithmProcessing::destroy();

	//图像增强
	CMvImageEnhancement::destroy();

	//加减法处理
	CMvAdditionAndSubtraction::destroy();

	//乘除法处理
	CMvMultiplicationAndDivision::destroy();

	//手动二值化
	CMvManualBinary::destroy();

	//自适应二值化
	CMvAdaptiveBinarization::destroy();

	//去噪二值化
	CMvDenoiseBinarization::destroy();

	//Canny边缘提取
	CMvCannyEdgeExtracting::destroy();

	//图像缺陷
	CMvImageDefect::destroy();

	//条码缺陷
	CMvBarCodeDefect::destroy();
	
	//图形缺陷
	CMvGraphicDefects::destroy();

	//晶片缺陷
	CMvChipDefect::destroy();
	
	//晶片主栅线
	CMvChipMainGrid::destroy();

	//触点姿态缺陷
	CMvContactAttitudeDefect::destroy();

	//边缘缺陷
	CMvEdgeDefect::destroy();

	//环胶缺陷
	CMvRingGlueDefect::destroy();

	//矩形胶缺陷
	CMvRectangleGlueDefect::destroy();

	//触点正反
	CMvPositiveNegativeContacts::destroy();
	
	//圆环缺口
	CMvRingDefect::destroy();

	//模板匹配
	CMvTemplateMatching::destroy();

	//轮廓匹配
	CMvContourMatching::destroy();
	
	//特征匹配
	CMvFeatureMatching::destroy();
	
	m_pTestWidget = nullptr;
	delete ui;
}

//单实例化
CMvTestWidget* CMvTestWidget::Instance()
{
	if (s_pTestWidget == nullptr)
	{
		s_pTestWidget = new CMvTestWidget;
	}
	return s_pTestWidget;
}

//释放内存
void CMvTestWidget::destroy()
{
	if (s_pTestWidget)
	{
		delete s_pTestWidget;
		s_pTestWidget = nullptr;
	}//if (c_pUniqueShowMessage)
}

//选择功能
void CMvTestWidget::slotSelectFunction(int Index)
{
	qDebug() << "选择功能" << ui->comboBox_selectionFunction->itemText(Index) <<  Index;

	m_iFunctionIndex = Index;
}

//打开界面
void CMvTestWidget::slotOpenWindow()
{
	if (m_pTestWidget)
	{
		switch (m_iFunctionIndex)
		{
		case 0://find line
		{
			CMvFindLineParamWidget::destroy();
			////pTestWidget->setWindowTitle("查找直线");
		}break;
		case 1://find round
		{
			CMvFindRoundParamWidget::destroy();
			//pTestWidget->setWindowTitle("查找圆");
		}break;
		case 2:
		{
			CMvColorImagesCut::destroy();
			//pTestWidget->setWindowTitle("裁剪图片");
		}break;
		case 3:
		{
			CMvColorConversionBlackAndWhite::destroy();
			//pTestWidget->setWindowTitle("彩色转黑白");
		}break;
		case 4:
		{
			CMvBlackAndWhiteConversionColor::destroy();
			//pTestWidget->setWindowTitle("黑白转彩色");
		}break;
		case 5:
		{
			CMvFourArithmeticOperation::destroy();
			//pTestWidget->setWindowTitle("四则运算");
		}break;
		case 6:
		{
			//blob快速检测
			CMvBlobRapidDetection::destroy();
	
		}break;
		case 7:
		{
			//颜色选定
			CMvColorSelection::destroy();
	
		}break;
		case 8:
		{
			//knn颜色选定
			CMvKNNColorSelection::destroy();

		}break;
		case 9:
		{
			//颜色区域
			CMvColorArea::destroy();
		
		}break;
		case 10:
		{
			//图片裁剪
			CMvImagesCut::destroy();
		}break;
		case 11:
		{
			//图像旋转
			CMvImageRotation::destroy();
		}break;
		case 12:
		{
			//公式算法处理
			CMvAlgorithmProcessing::destroy();
		}break;
		case 13:
		{
			//图像增强
			CMvImageEnhancement::destroy();
		}break;
		case 14:
		{
			//加减法处理
			CMvAdditionAndSubtraction::destroy();
		}break;
		case 15:
		{
			//乘除法处理
			CMvMultiplicationAndDivision::destroy();
		}break;
		case 16:
		{
			//手动二值化
			CMvManualBinary::destroy();
		}break;
		case 17:
		{
			//自适应二值化
			CMvAdaptiveBinarization::destroy();
		}break;
		case 18:
		{
			//去噪二值化
			CMvDenoiseBinarization::destroy();
		}break;
		case 19:
		{
			//Canny边缘提取
			CMvCannyEdgeExtracting::destroy();
		}break;
		case 20:
		{
			//图像缺陷
			CMvImageDefect::destroy();
		}break;
		case 21:
		{
			//条码缺陷
			CMvBarCodeDefect::destroy();
		}break;
		case 22:
		{
			//图形缺陷
			CMvGraphicDefects::destroy();
		}break;
		case 23:
		{
			//晶片缺陷
			CMvChipDefect::destroy();
		}break;
		case 24:
		{
			//晶片主栅线
			CMvChipMainGrid::destroy();
		}break;
		case 25:
		{
			//触点姿态缺陷
			CMvContactAttitudeDefect::destroy();
		}break;
		case 26:
		{
			//边缘缺陷
			 CMvEdgeDefect::destroy();
		}break;
		case 27:
		{
			//环胶缺陷
			CMvRingGlueDefect::destroy();
		}break;
		case 28:
		{
			//矩形胶缺陷
			CMvRectangleGlueDefect::destroy();
		}break;
		case 29:
		{
			//触点正反
			CMvPositiveNegativeContacts::destroy();
		}break;
		case 30:
		{
			//圆环缺口
			CMvRingDefect::destroy();
		}break;
		case 31:
		{
			//模板匹配
			CMvTemplateMatching::destroy();
		}break;
		case 32:
		{
			//轮廓匹配
			CMvContourMatching::destroy();
		}break;
		case 33:
		{
			//特征匹配
			CMvFeatureMatching::destroy();
		}break;
	

		default:
			break;
		}//switch (widgetType)
		m_pTestWidget = nullptr;
	}//if (m_pTestWidget)
	qDebug() << "打开界面" ;
	//QWidget *pTestWidget = nullptr;
	switch (m_iFunctionIndex)
	{
	case 0://find line
	{
		m_pTestWidget = CMvFindLineParamWidget::Instance();
		////pTestWidget->setWindowTitle("查找直线");
	}break;
	case 1://find round
	{
		m_pTestWidget = CMvFindRoundParamWidget::Instance();
		//pTestWidget->setWindowTitle("查找圆");
	}break;
	case 2:
	{
		m_pTestWidget = CMvColorImagesCut::Instance();
		//pTestWidget->setWindowTitle("裁剪图片");
	}break;
	case 3:
	{
		m_pTestWidget = CMvColorConversionBlackAndWhite::Instance();
		//pTestWidget->setWindowTitle("彩色转黑白");
	}break;
	case 4:
	{
		m_pTestWidget = CMvBlackAndWhiteConversionColor::Instance();
		//pTestWidget->setWindowTitle("黑白转彩色");
	}break;
	case 5:
	{
		m_pTestWidget = CMvFourArithmeticOperation::Instance();
		//pTestWidget->setWindowTitle("四则运算");
	}break;
	case 6:
	{
		m_pTestWidget = CMvBlobRapidDetection::Instance();
		//pTestWidget->setWindowTitle("Blob快速检测");
	}break;
	case 7:
	{
		m_pTestWidget = CMvColorSelection::Instance();
		
	}break;
	case 8:
	{
		m_pTestWidget = CMvKNNColorSelection::Instance();
		
	}break;
	case 9:
	{
		m_pTestWidget = CMvColorArea::Instance();
		
	}break;
	case 10:
	{
		m_pTestWidget = CMvImagesCut::Instance();

	}break;
	case 11:
	{
		m_pTestWidget = CMvImageRotation::Instance();

	}break;//
	case 12:
	{
		//公式算法处理
		m_pTestWidget = CMvAlgorithmProcessing::Instance();

	}break;
	case 13:
	{
		//图像增强
		m_pTestWidget = CMvImageEnhancement::Instance();

	}break;
	case 14:
	{
		//加减法处理
		m_pTestWidget = CMvAdditionAndSubtraction::Instance();

	}break; 
	case 15:
	{
		//乘除法处理
		m_pTestWidget = CMvMultiplicationAndDivision::Instance();

	}break;
	case 16:
	{
		//手动二值化
		m_pTestWidget = CMvManualBinary::Instance();
	}break;
	case 17:
	{
		//自适应二值化
		m_pTestWidget = CMvAdaptiveBinarization::Instance();
	}break;
	case 18:
	{
		//去噪二值化
		m_pTestWidget = CMvDenoiseBinarization::Instance();
	}break;
	case 19:
	{
		//Canny边缘提取
		m_pTestWidget = CMvCannyEdgeExtracting::Instance();
	}break;
	case 20:
	{
		//图像缺陷
		m_pTestWidget = CMvImageDefect::Instance();
	}break;
	case 21:
	{
		//条码缺陷
		m_pTestWidget = CMvBarCodeDefect::Instance();
	}break;
	case 22:
	{
		//图形缺陷
		m_pTestWidget = CMvGraphicDefects::Instance();
	}break;
	case 23:
	{
		//晶片缺陷
		m_pTestWidget = CMvChipDefect::Instance();
	}break;
	case 24:
	{
		//晶片主栅线
		m_pTestWidget = CMvChipMainGrid::Instance();
	}break;
	case 25:
	{
		//触点姿态缺陷
		m_pTestWidget = CMvContactAttitudeDefect::Instance();
	}break;

	case 26:
	{
		//边缘缺陷
		m_pTestWidget = CMvEdgeDefect::Instance();
	}break;
	case 27:
	{
		//环胶缺陷
		m_pTestWidget = CMvRingGlueDefect::Instance();
	}break;
	case 28:
	{
		//矩形胶缺陷
		m_pTestWidget = CMvRectangleGlueDefect::Instance();
	}break;
	case 29:
	{
		//触点正反
		m_pTestWidget = CMvPositiveNegativeContacts::Instance();
	}break;
	case 30:
	{
		//圆环缺口
		m_pTestWidget = CMvRingDefect::Instance();
	}break;
	case 31:
	{
		//模板匹配
		m_pTestWidget = CMvTemplateMatching::Instance();
	}break;
	case 32:
	{
		//轮廓匹配
		m_pTestWidget = CMvContourMatching::Instance();
	}break;
	case 33:
	{
		//特征匹配
		m_pTestWidget = CMvFeatureMatching::Instance(); 
	}break;
	default:
		break;
	}//switch (widgetType)

	if (m_pTestWidget)
	{
		m_pTestWidget->show();
	}//if (m_pTestWidget)
}