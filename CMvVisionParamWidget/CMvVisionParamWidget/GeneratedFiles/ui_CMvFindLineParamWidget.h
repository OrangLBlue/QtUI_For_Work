/********************************************************************************
** Form generated from reading UI file 'CMvFindLineParamWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMVFINDLINEPARAMWIDGET_H
#define UI_CMVFINDLINEPARAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMvFindLineParamWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_image;
    QGraphicsView *graphicsView_mainImage;
    QFrame *frame_had;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_zoomIn;
    QPushButton *pushButton_zoomOut;
    QPushButton *pushButton_zoomBest;
    QPushButton *pushButton_lockRoiMove;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_mousePos;
    QWidget *widget_param;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget_param;
    QWidget *tab_input;
    QLabel *label_funcName;
    QPlainTextEdit *plainTextEdit_funcName;
    QLabel *label_roiCreat;
    QCheckBox *checkBox_enableFunc;
    QTableWidget *tableWidget_input;
    QComboBox *comboBox_imageSource_2;
    QCheckBox *checkBox_roiCreat;
    QWidget *tab_paramSet;
    QLabel *label_thresholdType;
    QComboBox *comboBox_thresholdType;
    QComboBox *comboBox_scanDirection;
    QLabel *label_scanDirection;
    QComboBox *comboBox_edgeCheckType;
    QLabel *label_edgeCheckType;
    QSpinBox *spinBox_scanPointSum;
    QLabel *label_samplingPointSum;
    QSpinBox *spinBox_samplingPointSum;
    QLabel *label_scanPointSum;
    QLabel *label_fitRange;
    QSpinBox *spinBox_fitRange;
    QLabel *label_threshold;
    QSpinBox *spinBox_threshold;
    QWidget *widget_Judged;
    QSpinBox *spinBox_fitBias;
    QLabel *label_fitBias;
    QSpinBox *spinBox_minLineLong;
    QLabel *label_minLineLong;
    QSpinBox *spinBox_maxLineLong;
    QLabel *label_maxLineLong;
    QLabel *label_titleJudged;
    QWidget *tab_2;
    QComboBox *comboBox_lightOutputIo_5;
    QLabel *label_lightOutputIo_8;
    QWidget *widget_3;
    QLabel *label_penWidth;
    QSpinBox *spinBox_lightTime_2;
    QPushButton *pushButton_maskAll;
    QPushButton *pushButton_maskNull;
    QPushButton *pushButton_saveMask;
    QLabel *label_lightOutputIo_9;
    QComboBox *comboBox_lightOutputIo_6;
    QWidget *tab_5;
    QLabel *label_lightOutputIo_17;
    QComboBox *comboBox_lightOutputIo_10;
    QSpinBox *spinBox_lightTime_3;
    QLabel *label_lightOutputIo_18;
    QCheckBox *checkBox_valuTrig_3;
    QHBoxLayout *horizontalLayout_head;
    QPushButton *pushButton_ones;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ensure;
    QPushButton *pbPrev_cancel;

    void setupUi(QWidget *CMvFindLineParamWidget)
    {
        if (CMvFindLineParamWidget->objectName().isEmpty())
            CMvFindLineParamWidget->setObjectName(QStringLiteral("CMvFindLineParamWidget"));
        CMvFindLineParamWidget->resize(887, 644);
        horizontalLayout = new QHBoxLayout(CMvFindLineParamWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(CMvFindLineParamWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_image = new QVBoxLayout(layoutWidget);
        verticalLayout_image->setSpacing(0);
        verticalLayout_image->setContentsMargins(11, 11, 11, 11);
        verticalLayout_image->setObjectName(QStringLiteral("verticalLayout_image"));
        verticalLayout_image->setContentsMargins(0, 0, 0, 0);
        graphicsView_mainImage = new QGraphicsView(layoutWidget);
        graphicsView_mainImage->setObjectName(QStringLiteral("graphicsView_mainImage"));
        graphicsView_mainImage->setMinimumSize(QSize(500, 600));
        graphicsView_mainImage->setDragMode(QGraphicsView::NoDrag);
        graphicsView_mainImage->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView_mainImage->setResizeAnchor(QGraphicsView::NoAnchor);

        verticalLayout_image->addWidget(graphicsView_mainImage);

        frame_had = new QFrame(layoutWidget);
        frame_had->setObjectName(QStringLiteral("frame_had"));
        frame_had->setMinimumSize(QSize(0, 42));
        frame_had->setMaximumSize(QSize(16777215, 42));
        frame_had->setFrameShape(QFrame::StyledPanel);
        frame_had->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_had);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(2, 0, 0, 0);
        pushButton_zoomIn = new QPushButton(frame_had);
        pushButton_zoomIn->setObjectName(QStringLiteral("pushButton_zoomIn"));
        pushButton_zoomIn->setMinimumSize(QSize(70, 40));
        pushButton_zoomIn->setMaximumSize(QSize(70, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/action/zoomIn.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_zoomIn->setIcon(icon);
        pushButton_zoomIn->setIconSize(QSize(28, 28));
        pushButton_zoomIn->setFlat(false);

        horizontalLayout_5->addWidget(pushButton_zoomIn);

        pushButton_zoomOut = new QPushButton(frame_had);
        pushButton_zoomOut->setObjectName(QStringLiteral("pushButton_zoomOut"));
        pushButton_zoomOut->setMinimumSize(QSize(70, 40));
        pushButton_zoomOut->setMaximumSize(QSize(70, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/action/zoomOut.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_zoomOut->setIcon(icon1);
        pushButton_zoomOut->setIconSize(QSize(28, 28));
        pushButton_zoomOut->setFlat(false);

        horizontalLayout_5->addWidget(pushButton_zoomOut);

        pushButton_zoomBest = new QPushButton(frame_had);
        pushButton_zoomBest->setObjectName(QStringLiteral("pushButton_zoomBest"));
        pushButton_zoomBest->setMinimumSize(QSize(70, 40));
        pushButton_zoomBest->setMaximumSize(QSize(70, 40));
        pushButton_zoomBest->setIconSize(QSize(28, 28));
        pushButton_zoomBest->setFlat(false);

        horizontalLayout_5->addWidget(pushButton_zoomBest);

        pushButton_lockRoiMove = new QPushButton(frame_had);
        pushButton_lockRoiMove->setObjectName(QStringLiteral("pushButton_lockRoiMove"));
        pushButton_lockRoiMove->setMinimumSize(QSize(70, 40));
        pushButton_lockRoiMove->setMaximumSize(QSize(70, 40));
        pushButton_lockRoiMove->setIconSize(QSize(28, 28));
        pushButton_lockRoiMove->setCheckable(true);
        pushButton_lockRoiMove->setChecked(false);
        pushButton_lockRoiMove->setFlat(false);

        horizontalLayout_5->addWidget(pushButton_lockRoiMove);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_mousePos = new QLabel(frame_had);
        label_mousePos->setObjectName(QStringLiteral("label_mousePos"));
        label_mousePos->setMinimumSize(QSize(150, 0));
        label_mousePos->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(label_mousePos);


        verticalLayout_image->addWidget(frame_had);

        splitter->addWidget(layoutWidget);
        widget_param = new QWidget(splitter);
        widget_param->setObjectName(QStringLiteral("widget_param"));
        widget_param->setMinimumSize(QSize(380, 0));
        widget_param->setMaximumSize(QSize(380, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_param);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget_param = new QTabWidget(widget_param);
        tabWidget_param->setObjectName(QStringLiteral("tabWidget_param"));
        tabWidget_param->setFocusPolicy(Qt::StrongFocus);
        tabWidget_param->setTabPosition(QTabWidget::North);
        tabWidget_param->setIconSize(QSize(16, 16));
        tab_input = new QWidget();
        tab_input->setObjectName(QStringLiteral("tab_input"));
        label_funcName = new QLabel(tab_input);
        label_funcName->setObjectName(QStringLiteral("label_funcName"));
        label_funcName->setGeometry(QRect(10, 20, 111, 31));
        plainTextEdit_funcName = new QPlainTextEdit(tab_input);
        plainTextEdit_funcName->setObjectName(QStringLiteral("plainTextEdit_funcName"));
        plainTextEdit_funcName->setGeometry(QRect(130, 20, 131, 31));
        plainTextEdit_funcName->setMaximumBlockCount(0);
        label_roiCreat = new QLabel(tab_input);
        label_roiCreat->setObjectName(QStringLiteral("label_roiCreat"));
        label_roiCreat->setGeometry(QRect(10, 60, 121, 31));
        checkBox_enableFunc = new QCheckBox(tab_input);
        checkBox_enableFunc->setObjectName(QStringLiteral("checkBox_enableFunc"));
        checkBox_enableFunc->setGeometry(QRect(270, 20, 101, 31));
        checkBox_enableFunc->setChecked(true);
        tableWidget_input = new QTableWidget(tab_input);
        if (tableWidget_input->columnCount() < 2)
            tableWidget_input->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget_input->rowCount() < 4)
            tableWidget_input->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/other/leg_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setIcon(icon2);
        tableWidget_input->setItem(0, 0, __qtablewidgetitem6);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/image/other/label_next.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setIcon(icon3);
        tableWidget_input->setItem(0, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setIcon(icon2);
        tableWidget_input->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setIcon(icon3);
        tableWidget_input->setItem(1, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setIcon(icon2);
        tableWidget_input->setItem(2, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setIcon(icon3);
        tableWidget_input->setItem(2, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setIcon(icon2);
        tableWidget_input->setItem(3, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setIcon(icon3);
        tableWidget_input->setItem(3, 1, __qtablewidgetitem13);
        tableWidget_input->setObjectName(QStringLiteral("tableWidget_input"));
        tableWidget_input->setGeometry(QRect(10, 110, 361, 381));
        tableWidget_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_input->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_input->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_input->setShowGrid(false);
        tableWidget_input->horizontalHeader()->setStretchLastSection(true);
        tableWidget_input->verticalHeader()->setVisible(false);
        comboBox_imageSource_2 = new QComboBox(tab_input);
        comboBox_imageSource_2->setObjectName(QStringLiteral("comboBox_imageSource_2"));
        comboBox_imageSource_2->setGeometry(QRect(130, 60, 131, 31));
        checkBox_roiCreat = new QCheckBox(tab_input);
        checkBox_roiCreat->setObjectName(QStringLiteral("checkBox_roiCreat"));
        checkBox_roiCreat->setGeometry(QRect(270, 60, 101, 31));
        checkBox_roiCreat->setChecked(true);
        tabWidget_param->addTab(tab_input, QString());
        tab_paramSet = new QWidget();
        tab_paramSet->setObjectName(QStringLiteral("tab_paramSet"));
        label_thresholdType = new QLabel(tab_paramSet);
        label_thresholdType->setObjectName(QStringLiteral("label_thresholdType"));
        label_thresholdType->setGeometry(QRect(10, 20, 121, 31));
        comboBox_thresholdType = new QComboBox(tab_paramSet);
        comboBox_thresholdType->setObjectName(QStringLiteral("comboBox_thresholdType"));
        comboBox_thresholdType->setGeometry(QRect(10, 50, 101, 31));
        comboBox_scanDirection = new QComboBox(tab_paramSet);
        comboBox_scanDirection->setObjectName(QStringLiteral("comboBox_scanDirection"));
        comboBox_scanDirection->setGeometry(QRect(10, 120, 101, 31));
        label_scanDirection = new QLabel(tab_paramSet);
        label_scanDirection->setObjectName(QStringLiteral("label_scanDirection"));
        label_scanDirection->setGeometry(QRect(10, 90, 121, 31));
        comboBox_edgeCheckType = new QComboBox(tab_paramSet);
        comboBox_edgeCheckType->setObjectName(QStringLiteral("comboBox_edgeCheckType"));
        comboBox_edgeCheckType->setGeometry(QRect(130, 120, 101, 31));
        label_edgeCheckType = new QLabel(tab_paramSet);
        label_edgeCheckType->setObjectName(QStringLiteral("label_edgeCheckType"));
        label_edgeCheckType->setGeometry(QRect(130, 90, 121, 31));
        spinBox_scanPointSum = new QSpinBox(tab_paramSet);
        spinBox_scanPointSum->setObjectName(QStringLiteral("spinBox_scanPointSum"));
        spinBox_scanPointSum->setGeometry(QRect(10, 190, 101, 31));
        spinBox_scanPointSum->setMinimum(5);
        spinBox_scanPointSum->setMaximum(299);
        label_samplingPointSum = new QLabel(tab_paramSet);
        label_samplingPointSum->setObjectName(QStringLiteral("label_samplingPointSum"));
        label_samplingPointSum->setGeometry(QRect(130, 160, 111, 31));
        spinBox_samplingPointSum = new QSpinBox(tab_paramSet);
        spinBox_samplingPointSum->setObjectName(QStringLiteral("spinBox_samplingPointSum"));
        spinBox_samplingPointSum->setGeometry(QRect(130, 190, 101, 31));
        spinBox_samplingPointSum->setMinimum(5);
        spinBox_samplingPointSum->setMaximum(299);
        label_scanPointSum = new QLabel(tab_paramSet);
        label_scanPointSum->setObjectName(QStringLiteral("label_scanPointSum"));
        label_scanPointSum->setGeometry(QRect(10, 160, 111, 31));
        label_fitRange = new QLabel(tab_paramSet);
        label_fitRange->setObjectName(QStringLiteral("label_fitRange"));
        label_fitRange->setGeometry(QRect(250, 160, 111, 31));
        spinBox_fitRange = new QSpinBox(tab_paramSet);
        spinBox_fitRange->setObjectName(QStringLiteral("spinBox_fitRange"));
        spinBox_fitRange->setGeometry(QRect(250, 190, 101, 31));
        spinBox_fitRange->setMinimum(5);
        spinBox_fitRange->setMaximum(299);
        label_threshold = new QLabel(tab_paramSet);
        label_threshold->setObjectName(QStringLiteral("label_threshold"));
        label_threshold->setGeometry(QRect(130, 20, 121, 31));
        spinBox_threshold = new QSpinBox(tab_paramSet);
        spinBox_threshold->setObjectName(QStringLiteral("spinBox_threshold"));
        spinBox_threshold->setEnabled(false);
        spinBox_threshold->setGeometry(QRect(130, 50, 101, 31));
        spinBox_threshold->setMinimum(5);
        spinBox_threshold->setMaximum(299);
        widget_Judged = new QWidget(tab_paramSet);
        widget_Judged->setObjectName(QStringLiteral("widget_Judged"));
        widget_Judged->setGeometry(QRect(0, 280, 371, 161));
        spinBox_fitBias = new QSpinBox(widget_Judged);
        spinBox_fitBias->setObjectName(QStringLiteral("spinBox_fitBias"));
        spinBox_fitBias->setGeometry(QRect(10, 40, 101, 31));
        spinBox_fitBias->setMinimum(5);
        spinBox_fitBias->setMaximum(299);
        label_fitBias = new QLabel(widget_Judged);
        label_fitBias->setObjectName(QStringLiteral("label_fitBias"));
        label_fitBias->setGeometry(QRect(10, 10, 111, 31));
        spinBox_minLineLong = new QSpinBox(widget_Judged);
        spinBox_minLineLong->setObjectName(QStringLiteral("spinBox_minLineLong"));
        spinBox_minLineLong->setGeometry(QRect(10, 110, 101, 31));
        spinBox_minLineLong->setMinimum(5);
        spinBox_minLineLong->setMaximum(299);
        label_minLineLong = new QLabel(widget_Judged);
        label_minLineLong->setObjectName(QStringLiteral("label_minLineLong"));
        label_minLineLong->setGeometry(QRect(10, 80, 111, 31));
        spinBox_maxLineLong = new QSpinBox(widget_Judged);
        spinBox_maxLineLong->setObjectName(QStringLiteral("spinBox_maxLineLong"));
        spinBox_maxLineLong->setGeometry(QRect(130, 110, 101, 31));
        spinBox_maxLineLong->setMinimum(5);
        spinBox_maxLineLong->setMaximum(299);
        label_maxLineLong = new QLabel(widget_Judged);
        label_maxLineLong->setObjectName(QStringLiteral("label_maxLineLong"));
        label_maxLineLong->setGeometry(QRect(130, 80, 111, 31));
        label_titleJudged = new QLabel(tab_paramSet);
        label_titleJudged->setObjectName(QStringLiteral("label_titleJudged"));
        label_titleJudged->setGeometry(QRect(0, 250, 381, 31));
        label_titleJudged->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(80, 80, 80, 255), stop:1 rgba(120, 120, 120, 120));\n"
"color: rgb(255, 255, 255);"));
        label_titleJudged->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget_param->addTab(tab_paramSet, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        comboBox_lightOutputIo_5 = new QComboBox(tab_2);
        comboBox_lightOutputIo_5->setObjectName(QStringLiteral("comboBox_lightOutputIo_5"));
        comboBox_lightOutputIo_5->setGeometry(QRect(130, 20, 131, 31));
        label_lightOutputIo_8 = new QLabel(tab_2);
        label_lightOutputIo_8->setObjectName(QStringLiteral("label_lightOutputIo_8"));
        label_lightOutputIo_8->setGeometry(QRect(10, 20, 111, 31));
        widget_3 = new QWidget(tab_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setEnabled(false);
        widget_3->setGeometry(QRect(0, 50, 371, 251));
        label_penWidth = new QLabel(widget_3);
        label_penWidth->setObjectName(QStringLiteral("label_penWidth"));
        label_penWidth->setGeometry(QRect(10, 50, 111, 31));
        spinBox_lightTime_2 = new QSpinBox(widget_3);
        spinBox_lightTime_2->setObjectName(QStringLiteral("spinBox_lightTime_2"));
        spinBox_lightTime_2->setGeometry(QRect(130, 50, 131, 31));
        spinBox_lightTime_2->setMinimum(5);
        spinBox_lightTime_2->setMaximum(1000);
        pushButton_maskAll = new QPushButton(widget_3);
        pushButton_maskAll->setObjectName(QStringLiteral("pushButton_maskAll"));
        pushButton_maskAll->setGeometry(QRect(10, 160, 121, 40));
        pushButton_maskAll->setMinimumSize(QSize(0, 40));
        pushButton_maskAll->setMaximumSize(QSize(16777215, 30));
        pushButton_maskNull = new QPushButton(widget_3);
        pushButton_maskNull->setObjectName(QStringLiteral("pushButton_maskNull"));
        pushButton_maskNull->setEnabled(false);
        pushButton_maskNull->setGeometry(QRect(10, 110, 121, 40));
        pushButton_maskNull->setMinimumSize(QSize(0, 40));
        pushButton_maskNull->setMaximumSize(QSize(16777215, 30));
        pushButton_saveMask = new QPushButton(widget_3);
        pushButton_saveMask->setObjectName(QStringLiteral("pushButton_saveMask"));
        pushButton_saveMask->setGeometry(QRect(10, 210, 121, 40));
        pushButton_saveMask->setMinimumSize(QSize(0, 40));
        pushButton_saveMask->setMaximumSize(QSize(16777215, 30));
        label_lightOutputIo_9 = new QLabel(widget_3);
        label_lightOutputIo_9->setObjectName(QStringLiteral("label_lightOutputIo_9"));
        label_lightOutputIo_9->setGeometry(QRect(10, 10, 111, 31));
        comboBox_lightOutputIo_6 = new QComboBox(widget_3);
        comboBox_lightOutputIo_6->setObjectName(QStringLiteral("comboBox_lightOutputIo_6"));
        comboBox_lightOutputIo_6->setGeometry(QRect(130, 10, 131, 31));
        tabWidget_param->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        label_lightOutputIo_17 = new QLabel(tab_5);
        label_lightOutputIo_17->setObjectName(QStringLiteral("label_lightOutputIo_17"));
        label_lightOutputIo_17->setGeometry(QRect(10, 20, 121, 31));
        comboBox_lightOutputIo_10 = new QComboBox(tab_5);
        comboBox_lightOutputIo_10->setObjectName(QStringLiteral("comboBox_lightOutputIo_10"));
        comboBox_lightOutputIo_10->setGeometry(QRect(130, 60, 131, 31));
        spinBox_lightTime_3 = new QSpinBox(tab_5);
        spinBox_lightTime_3->setObjectName(QStringLiteral("spinBox_lightTime_3"));
        spinBox_lightTime_3->setGeometry(QRect(130, 20, 131, 31));
        spinBox_lightTime_3->setMinimum(1);
        spinBox_lightTime_3->setMaximum(5);
        label_lightOutputIo_18 = new QLabel(tab_5);
        label_lightOutputIo_18->setObjectName(QStringLiteral("label_lightOutputIo_18"));
        label_lightOutputIo_18->setGeometry(QRect(10, 60, 121, 31));
        checkBox_valuTrig_3 = new QCheckBox(tab_5);
        checkBox_valuTrig_3->setObjectName(QStringLiteral("checkBox_valuTrig_3"));
        checkBox_valuTrig_3->setGeometry(QRect(270, 20, 101, 31));
        checkBox_valuTrig_3->setChecked(true);
        tabWidget_param->addTab(tab_5, QString());

        verticalLayout_2->addWidget(tabWidget_param);

        horizontalLayout_head = new QHBoxLayout();
        horizontalLayout_head->setSpacing(1);
        horizontalLayout_head->setObjectName(QStringLiteral("horizontalLayout_head"));
        horizontalLayout_head->setContentsMargins(1, 1, 1, 1);
        pushButton_ones = new QPushButton(widget_param);
        pushButton_ones->setObjectName(QStringLiteral("pushButton_ones"));
        pushButton_ones->setEnabled(true);
        pushButton_ones->setMinimumSize(QSize(80, 40));
        pushButton_ones->setMaximumSize(QSize(80, 16777215));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/image/other/action_next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_ones->setIcon(icon4);
        pushButton_ones->setIconSize(QSize(28, 28));

        horizontalLayout_head->addWidget(pushButton_ones);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_head->addItem(horizontalSpacer);

        pushButton_ensure = new QPushButton(widget_param);
        pushButton_ensure->setObjectName(QStringLiteral("pushButton_ensure"));
        pushButton_ensure->setEnabled(true);
        pushButton_ensure->setMinimumSize(QSize(80, 40));
        pushButton_ensure->setMaximumSize(QSize(80, 16777215));
        pushButton_ensure->setIcon(icon4);
        pushButton_ensure->setIconSize(QSize(28, 28));

        horizontalLayout_head->addWidget(pushButton_ensure);

        pbPrev_cancel = new QPushButton(widget_param);
        pbPrev_cancel->setObjectName(QStringLiteral("pbPrev_cancel"));
        pbPrev_cancel->setEnabled(true);
        pbPrev_cancel->setMinimumSize(QSize(80, 40));
        pbPrev_cancel->setMaximumSize(QSize(80, 16777215));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/image/other/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPrev_cancel->setIcon(icon5);
        pbPrev_cancel->setIconSize(QSize(28, 28));

        horizontalLayout_head->addWidget(pbPrev_cancel);


        verticalLayout_2->addLayout(horizontalLayout_head);

        splitter->addWidget(widget_param);

        horizontalLayout->addWidget(splitter);


        retranslateUi(CMvFindLineParamWidget);

        tabWidget_param->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(CMvFindLineParamWidget);
    } // setupUi

    void retranslateUi(QWidget *CMvFindLineParamWidget)
    {
        CMvFindLineParamWidget->setWindowTitle(QApplication::translate("CMvFindLineParamWidget", "CyMassageSet", Q_NULLPTR));
        pushButton_zoomIn->setText(QApplication::translate("CMvFindLineParamWidget", "\346\224\276\345\244\247", Q_NULLPTR));
        pushButton_zoomOut->setText(QApplication::translate("CMvFindLineParamWidget", "\347\274\251\345\260\217", Q_NULLPTR));
        pushButton_zoomBest->setText(QApplication::translate("CMvFindLineParamWidget", "\346\234\200\345\245\275\345\260\272\345\257\270", Q_NULLPTR));
        pushButton_lockRoiMove->setText(QApplication::translate("CMvFindLineParamWidget", "\351\224\201\345\256\232ROI", Q_NULLPTR));
        label_mousePos->setText(QApplication::translate("CMvFindLineParamWidget", "TextLabel", Q_NULLPTR));
        label_funcName->setText(QApplication::translate("CMvFindLineParamWidget", "\346\243\200\346\265\213\345\231\250\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        plainTextEdit_funcName->setPlainText(QString());
        label_roiCreat->setText(QApplication::translate("CMvFindLineParamWidget", "ROI\346\235\245\346\272\220\357\274\232", Q_NULLPTR));
        checkBox_enableFunc->setText(QApplication::translate("CMvFindLineParamWidget", "\345\220\257\347\224\250\346\243\200\346\265\213\345\231\250", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_input->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CMvFindLineParamWidget", "\350\276\223\345\205\245\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_input->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CMvFindLineParamWidget", "\346\225\260\346\215\256\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_input->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("CMvFindLineParamWidget", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_input->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("CMvFindLineParamWidget", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_input->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("CMvFindLineParamWidget", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_input->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("CMvFindLineParamWidget", "4", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget_input->isSortingEnabled();
        tableWidget_input->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_input->item(0, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("CMvFindLineParamWidget", "\345\233\276\345\203\217\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_input->item(0, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("CMvFindLineParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_input->item(1, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("CMvFindLineParamWidget", "ROI\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_input->item(1, 1);
        ___qtablewidgetitem9->setText(QApplication::translate("CMvFindLineParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_input->item(2, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("CMvFindLineParamWidget", "ROI\344\275\215\347\275\256\344\277\256\346\255\243", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_input->item(2, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("CMvFindLineParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_input->item(3, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("CMvFindLineParamWidget", "\346\216\251\350\206\234\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_input->item(3, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("CMvFindLineParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        tableWidget_input->setSortingEnabled(__sortingEnabled);

        comboBox_imageSource_2->clear();
        comboBox_imageSource_2->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\346\255\243\347\237\251\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\346\227\213\350\275\254\347\237\251\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\345\234\206\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\345\234\206\347\216\257\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\350\207\252\345\256\232\344\271\211\345\244\232\350\276\271\345\275\242", Q_NULLPTR)
        );
        checkBox_roiCreat->setText(QApplication::translate("CMvFindLineParamWidget", "\350\207\252\345\267\261\345\210\233\345\273\272", Q_NULLPTR));
        tabWidget_param->setTabText(tabWidget_param->indexOf(tab_input), QApplication::translate("CMvFindLineParamWidget", "\350\276\223\345\205\245\350\256\276\347\275\256", Q_NULLPTR));
        label_thresholdType->setText(QApplication::translate("CMvFindLineParamWidget", "\351\230\210\345\200\274\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        comboBox_thresholdType->clear();
        comboBox_thresholdType->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\350\207\252\345\212\250", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\346\211\213\345\212\250", Q_NULLPTR)
        );
        comboBox_scanDirection->clear();
        comboBox_scanDirection->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\344\273\216\344\270\212\345\210\260\344\270\213", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\344\273\216\344\270\213\345\210\260\344\270\212", Q_NULLPTR)
        );
        label_scanDirection->setText(QApplication::translate("CMvFindLineParamWidget", "\346\211\253\346\217\217\346\226\271\345\220\221\357\274\232", Q_NULLPTR));
        comboBox_edgeCheckType->clear();
        comboBox_edgeCheckType->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\344\273\216\347\231\275\345\210\260\351\273\221", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\344\273\216\351\273\221\345\210\260\347\231\275", Q_NULLPTR)
        );
        label_edgeCheckType->setText(QApplication::translate("CMvFindLineParamWidget", "\350\276\271\347\274\230\346\243\200\346\265\213\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        spinBox_scanPointSum->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\202\271", Q_NULLPTR));
        label_samplingPointSum->setText(QApplication::translate("CMvFindLineParamWidget", "\346\212\275\346\240\267\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        spinBox_samplingPointSum->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\202\271", Q_NULLPTR));
        label_scanPointSum->setText(QApplication::translate("CMvFindLineParamWidget", "\346\211\253\346\217\217\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        label_fitRange->setText(QApplication::translate("CMvFindLineParamWidget", "\346\213\237\345\220\210\350\214\203\345\233\264\357\274\232", Q_NULLPTR));
        spinBox_fitRange->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\202\271", Q_NULLPTR));
        label_threshold->setText(QApplication::translate("CMvFindLineParamWidget", "\350\276\271\347\274\230\347\202\271\346\217\220\345\217\226\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        spinBox_threshold->setSuffix(QString());
        spinBox_fitBias->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\202\271", Q_NULLPTR));
        label_fitBias->setText(QApplication::translate("CMvFindLineParamWidget", "\346\213\237\345\220\210\350\257\257\345\267\256\351\231\220\345\210\266\357\274\232", Q_NULLPTR));
        spinBox_minLineLong->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\202\271", Q_NULLPTR));
        label_minLineLong->setText(QApplication::translate("CMvFindLineParamWidget", "\346\234\200\345\260\217\347\233\264\347\272\277\351\225\277\345\272\246\357\274\232", Q_NULLPTR));
        spinBox_maxLineLong->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\202\271", Q_NULLPTR));
        label_maxLineLong->setText(QApplication::translate("CMvFindLineParamWidget", "\346\234\200\345\244\247\347\233\264\347\272\277\351\225\277\345\272\246\357\274\232", Q_NULLPTR));
        label_titleJudged->setText(QApplication::translate("CMvFindLineParamWidget", "  \347\273\223\346\236\234\345\210\244\345\256\232", Q_NULLPTR));
        tabWidget_param->setTabText(tabWidget_param->indexOf(tab_paramSet), QApplication::translate("CMvFindLineParamWidget", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        comboBox_lightOutputIo_5->clear();
        comboBox_lightOutputIo_5->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\344\270\215\344\275\277\347\224\250\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\346\234\254\346\243\200\346\265\213\345\231\250ROI\345\206\205\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\345\205\266\344\273\226\347\256\227\346\263\225\347\232\204\346\216\251\350\206\234", Q_NULLPTR)
        );
        label_lightOutputIo_8->setText(QApplication::translate("CMvFindLineParamWidget", "\346\243\200\346\265\213\345\214\272\345\237\237\347\232\204\346\216\251\350\206\234\357\274\232", Q_NULLPTR));
        label_penWidth->setText(QApplication::translate("CMvFindLineParamWidget", "\347\224\273\347\254\224\345\260\272\345\257\270\357\274\232", Q_NULLPTR));
        spinBox_lightTime_2->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\345\203\217\347\264\240", Q_NULLPTR));
        pushButton_maskAll->setText(QApplication::translate("CMvFindLineParamWidget", "\346\216\251\347\233\226\346\211\200\346\234\211", Q_NULLPTR));
        pushButton_maskNull->setText(QApplication::translate("CMvFindLineParamWidget", "\346\270\205\347\251\272\346\216\251\350\206\234", Q_NULLPTR));
        pushButton_saveMask->setText(QApplication::translate("CMvFindLineParamWidget", "\344\277\235\345\255\230\344\277\256\346\224\271", Q_NULLPTR));
        label_lightOutputIo_9->setText(QApplication::translate("CMvFindLineParamWidget", "\347\274\226\350\276\221\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        comboBox_lightOutputIo_6->clear();
        comboBox_lightOutputIo_6->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\345\242\236\345\212\240\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvFindLineParamWidget", "\345\210\240\351\231\244\346\216\251\350\206\234", Q_NULLPTR)
        );
        tabWidget_param->setTabText(tabWidget_param->indexOf(tab_2), QApplication::translate("CMvFindLineParamWidget", "\346\216\251\350\206\234\350\256\276\347\275\256", Q_NULLPTR));
        label_lightOutputIo_17->setText(QApplication::translate("CMvFindLineParamWidget", "\347\272\277\346\235\241\345\256\275\345\272\246\357\274\232", Q_NULLPTR));
        comboBox_lightOutputIo_10->clear();
        comboBox_lightOutputIo_10->insertItems(0, QStringList()
         << QApplication::translate("CMvFindLineParamWidget", "\351\242\234\350\211\262", Q_NULLPTR)
        );
        spinBox_lightTime_3->setSuffix(QApplication::translate("CMvFindLineParamWidget", "\347\243\205", Q_NULLPTR));
        label_lightOutputIo_18->setText(QApplication::translate("CMvFindLineParamWidget", "\347\272\277\346\235\241\351\242\234\350\211\262\357\274\232", Q_NULLPTR));
        checkBox_valuTrig_3->setText(QApplication::translate("CMvFindLineParamWidget", "\345\220\257\347\224\250\347\273\230\345\210\266", Q_NULLPTR));
        tabWidget_param->setTabText(tabWidget_param->indexOf(tab_5), QApplication::translate("CMvFindLineParamWidget", "\347\273\223\346\236\234\347\273\230\345\210\266", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_ones->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_ones->setText(QApplication::translate("CMvFindLineParamWidget", "\345\215\225\346\254\241", Q_NULLPTR));
        pushButton_ones->setShortcut(QApplication::translate("CMvFindLineParamWidget", "Alt+Q", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_ensure->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_ensure->setText(QApplication::translate("CMvFindLineParamWidget", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_ensure->setShortcut(QApplication::translate("CMvFindLineParamWidget", "Alt+Q", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbPrev_cancel->setToolTip(QApplication::translate("CMvFindLineParamWidget", "\345\277\253\346\215\267\351\224\256Ctrl+B", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbPrev_cancel->setText(QApplication::translate("CMvFindLineParamWidget", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMvFindLineParamWidget: public Ui_CMvFindLineParamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMVFINDLINEPARAMWIDGET_H
