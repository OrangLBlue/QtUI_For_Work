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
#include "CMvMultiObjectiveContourMatching.h"
#include "CMvMultiTemplateFeatureMatching.h"
#include "CMvSimpleRelationPointLines.h"
#include "CMvPointLineOffset.h"
#include "CMvAngleOffset.h"
#include "CMvEdgeDistance.h"
#include "CMvPinSpacing.h"
#include "CMvExtractFarthestPoints.h"
#include "CMvEdgeCaliper.h"
#include "CMvBlobExtract.h"
#include "CMvBlobScreen.h"
#include "CMvBlobSortOutput.h"
#include "CMvBlobRelevantGetting.h"
#include "CMvBlobCumulativeArea.h"
#include "CMvBlobInnerObliqueRectangle.h"
#include "CMvCharacterRecognition.h"
#include "CMv1DCodeRecognition.h"
#include "CMv2DCodeRecognition.h"
#include "CMvMatchingCharacterRecognition.h"
#include "CMvCustomCoordinates.h"
#include "CMvPointOffsetWithCoordinates.h"

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

	//多目标轮廓匹配
	CMvMultiObjectiveContourMatching::destroy();

	//多模板特征匹配
	CMvMultiTemplateFeatureMatching::destroy();
	
	//点、线简单关系测量
	CMvSimpleRelationPointLines::destroy();
	
	//点线偏移
	CMvPointLineOffset::destroy();

	//角度偏移
	CMvAngleOffset::destroy();

	//边缘距离
	CMvEdgeDistance::destroy();
	
	//引脚间距
	CMvPinSpacing::destroy();

	//最远点提取
	CMvExtractFarthestPoints::destroy();

	//边缘卡尺
	CMvEdgeCaliper::destroy();
	
	//Blob提取
	CMvBlobExtract::destroy();

	//Blob筛选
	CMvBlobScreen::destroy();

	//Blob排序输出
	CMvBlobSortOutput::destroy();

	//Blob相关获取
	CMvBlobRelevantGetting::destroy();

	//Blob面积累计
	CMvBlobCumulativeArea::destroy();

	//Blob内接斜矩形
	CMvBlobInnerObliqueRectangle::destroy();

	//字符识别
	CMvCharacterRecognition::destroy();

	//一维码识别
	CMv1DCodeRecognition::destroy();

	//二维码识别
	CMv2DCodeRecognition::destroy();

	//匹配法字符识别
	CMvMatchingCharacterRecognition::destroy();

	//自定义坐标系
	CMvCustomCoordinates::destroy();
	
	//点随坐标系偏移
	CMvPointOffsetWithCoordinates::destroy();
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
		case 34:
		{
			//多目标轮廓匹配
			CMvMultiObjectiveContourMatching::destroy();
		}break;
		case 35:
		{
			//多模板特征匹配
			CMvMultiTemplateFeatureMatching::destroy();
		}break;
		case 36:
		{
			//点、线简单关系测量
			CMvSimpleRelationPointLines::destroy();
		}break;
		case 37:
		{
			//点线偏移
			CMvPointLineOffset::destroy();
		}break;
		case 38:
		{
			//角度偏移
			CMvAngleOffset::destroy();
		}break;
		case 39:
		{
			//边缘距离
			CMvEdgeDistance::destroy();
		}break;
		case 40:
		{
			//引脚间距
			CMvPinSpacing::destroy();
		}break;


		case 41:
		{
			//最远点提取
			CMvExtractFarthestPoints::destroy();

		}break;


		case 42:
		{
			//边缘卡尺
			CMvEdgeCaliper::destroy();

		}break;
		case 43:
		{
			//Blob提取
			CMvBlobExtract::destroy();

		}break;
		case 44:
		{
			//Blob筛选
			CMvBlobScreen::destroy();

		}break;
		case 45:
		{
			//Blob排序输出
			CMvBlobSortOutput::destroy();

		}break;
		case 46:
		{
			//Blob相关获取
			CMvBlobRelevantGetting::destroy();
		}break;

		case 47:
		{
			//Blob面积累计
			CMvBlobCumulativeArea::destroy();
		}break;

		case 48:
		{
			//Blob内接斜矩形
			CMvBlobInnerObliqueRectangle::destroy();
		}break;

		case 49:
		{
			//字符识别
			CMvCharacterRecognition::destroy();
		}break;

		case 50:
		{
			//一维码识别
			CMv1DCodeRecognition::destroy();
		}break;

		case 51:
		{
			//二维码识别
			CMv2DCodeRecognition::destroy();
		}break;
		case 52:
		{
			//匹配法字符识别
			CMvMatchingCharacterRecognition::destroy();
		}break;
		case 53:
		{
			//自定义坐标系
			CMvCustomCoordinates::destroy();

		}break;
		case 54:
		{
			//点随坐标系偏移
			CMvPointOffsetWithCoordinates::destroy();
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
	case 34:
	{
		//多目标轮廓匹配
		m_pTestWidget = CMvMultiObjectiveContourMatching::Instance();
	}break;
	case 35:
	{
		//多模板特征匹配
		m_pTestWidget = CMvMultiTemplateFeatureMatching::Instance();
	}break;
	case 36:
	{
		//点、线简单关系测量
		m_pTestWidget = CMvSimpleRelationPointLines::Instance();
	}break;
	case 37:
	{
		//点线偏移
		m_pTestWidget = CMvPointLineOffset::Instance();
	}break;
	case 38:
	{
		//角度偏移
		m_pTestWidget = CMvAngleOffset::Instance();
	}break;
	case 39:
	{
		//边缘距离
		m_pTestWidget = CMvEdgeDistance::Instance();
	}break;
	case 40:
	{
		//引脚间距
		m_pTestWidget = CMvPinSpacing::Instance();
	}break;
	case 41:
	{
		//最远点提取
		m_pTestWidget = CMvExtractFarthestPoints::Instance();
	}break;
	case 42:
	{
		//边缘卡尺
		m_pTestWidget = CMvEdgeCaliper::Instance();

	}break;
	case 43:
	{
		//Blob提取
		m_pTestWidget = CMvBlobExtract::Instance();

	}break;
	case 44:
	{
		//Blob筛选
		m_pTestWidget =	CMvBlobScreen::Instance();

	}break;
	case 45:
	{
		//Blob排序输出
		m_pTestWidget = CMvBlobSortOutput::Instance();

	}break;
	case 46:
	{
		//Blob相关获取
		m_pTestWidget = CMvBlobRelevantGetting::Instance();
	}break;
	case 47:
	{
		//Blob面积累计
		m_pTestWidget = CMvBlobCumulativeArea::Instance();
	}break;
	case 48:
	{
		//Blob内接斜矩形
		m_pTestWidget = CMvBlobInnerObliqueRectangle::Instance();
	}break;
	case 49:
	{
		//字符识别
		m_pTestWidget = CMvCharacterRecognition::Instance();
	}break;
	case 50:
	{
		//一维码识别
		m_pTestWidget = CMv1DCodeRecognition::Instance();
	}break;
	case 51:
	{
		//二维码识别
		m_pTestWidget = CMv2DCodeRecognition::Instance();
	}break;
	case 52:
	{
		//匹配法字符识别
		m_pTestWidget = CMvMatchingCharacterRecognition::Instance();
	}break;
	case 53:
	{
		//自定义坐标系
		m_pTestWidget = CMvCustomCoordinates::Instance();
		
	}break;
	case 54:
	{
		//点随坐标系偏移
		m_pTestWidget = CMvPointOffsetWithCoordinates::Instance();
	}break;

	default:
		break;
	}//switch (widgetType)


	if (m_pTestWidget)
	{
		m_pTestWidget->show();
	}//if (m_pTestWidget)
}