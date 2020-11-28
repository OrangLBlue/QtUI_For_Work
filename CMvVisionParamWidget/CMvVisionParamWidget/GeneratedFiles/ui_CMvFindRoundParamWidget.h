/********************************************************************************
** Form generated from reading UI file 'CMvFindRoundParamWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMVFINDROUNDPARAMWIDGET_H
#define UI_CMVFINDROUNDPARAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMvFindRoundParamWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView_mainImage;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_zoomIn;
    QPushButton *pushButton_zoomOut;
    QPushButton *pushButton_zoomBest;
    QPushButton *pushButton_lockRoiMove;
    QSpacerItem *horizontalSpacer;
    QLabel *label_mousePos;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidget_input;
    QLabel *label_funcName_2;
    QLabel *label_roiCreat_2;
    QCheckBox *checkBox_enableFunc_2;
    QCheckBox *checkBox_roiCreat_2;
    QPlainTextEdit *plainTextEdit_funcName_2;
    QComboBox *comboBox_imageSource_3;
    QWidget *tab_2;
    QSpinBox *spinBox_threshold_2;
    QComboBox *comboBox_thresholdType_2;
    QLabel *label_thresholdType_2;
    QLabel *label_scanDirection_2;
    QLabel *label_threshold_2;
    QLabel *label_edgeCheckType_2;
    QLabel *label_scanPointSum_2;
    QLabel *label_samplingPointSum_2;
    QLabel *label_fitRange_2;
    QComboBox *comboBox_scanDirection_2;
    QComboBox *comboBox_edgeCheckType_2;
    QLabel *label_titleJudged_2;
    QSpinBox *spinBox_scanPointSum_2;
    QSpinBox *spinBox_samplingPointSum_2;
    QSpinBox *spinBox_fitRange_2;
    QCheckBox *checkBox_concaveConvex;
    QWidget *widget_Judged_2;
    QSpinBox *spinBox_fitBias_2;
    QLabel *label_fitBias_2;
    QSpinBox *spinBox_minRoundRadius;
    QLabel *label_minRoundRadius;
    QSpinBox *spinBox_maxRoundRadius;
    QLabel *label_maxRoundRadius;
    QWidget *widget_concaveConvex;
    QDoubleSpinBox *doubleSpinBox_minimumDepth;
    QLabel *label_minimumDepth;
    QDoubleSpinBox *doubleSpinBox_minimumSamplingPoints;
    QLabel *label_2_minimumSamplingPoints;
    QPushButton *pushButton_unqualifiedPiont;
    QLabel *label_unqualifiedPiont;
    QWidget *tab_3;
    QWidget *widget_3;
    QLabel *label_penWidth_2;
    QSpinBox *spinBox_lightTime_3;
    QPushButton *pushButton_maskAll_2;
    QPushButton *pushButton_maskNull_2;
    QPushButton *pushButton_saveMask_2;
    QLabel *label_lightOutputIo_10;
    QComboBox *comboBox_lightOutputIo_7;
    QLabel *label_dEtectionMask;
    QComboBox *comboBox_dEtectionMask;
    QWidget *tab_4;
    QCheckBox *checkBox_valuTrig_4;
    QLabel *label_lightOutputIo_19;
    QSpinBox *spinBox_lightTime_5;
    QComboBox *comboBox_lightOutputIo_11;
    QLabel *label_lightOutputIo_20;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_ones;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_affirm;
    QPushButton *pbPrev_cancel;

    void setupUi(QWidget *CMvFindRoundParamWidget)
    {
        if (CMvFindRoundParamWidget->objectName().isEmpty())
            CMvFindRoundParamWidget->setObjectName(QStringLiteral("CMvFindRoundParamWidget"));
        CMvFindRoundParamWidget->resize(892, 652);
        horizontalLayout_3 = new QHBoxLayout(CMvFindRoundParamWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView_mainImage = new QGraphicsView(CMvFindRoundParamWidget);
        graphicsView_mainImage->setObjectName(QStringLiteral("graphicsView_mainImage"));
        graphicsView_mainImage->setMinimumSize(QSize(500, 600));

        verticalLayout->addWidget(graphicsView_mainImage);

        frame = new QFrame(CMvFindRoundParamWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(0, 42));
        frame->setMaximumSize(QSize(16777215, 42));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 0, 0);
        pushButton_zoomIn = new QPushButton(frame);
        pushButton_zoomIn->setObjectName(QStringLiteral("pushButton_zoomIn"));
        pushButton_zoomIn->setMinimumSize(QSize(70, 40));
        pushButton_zoomIn->setMaximumSize(QSize(70, 40));

        horizontalLayout->addWidget(pushButton_zoomIn);

        pushButton_zoomOut = new QPushButton(frame);
        pushButton_zoomOut->setObjectName(QStringLiteral("pushButton_zoomOut"));
        pushButton_zoomOut->setMinimumSize(QSize(70, 40));
        pushButton_zoomOut->setMaximumSize(QSize(70, 40));

        horizontalLayout->addWidget(pushButton_zoomOut);

        pushButton_zoomBest = new QPushButton(frame);
        pushButton_zoomBest->setObjectName(QStringLiteral("pushButton_zoomBest"));
        pushButton_zoomBest->setMinimumSize(QSize(70, 40));
        pushButton_zoomBest->setMaximumSize(QSize(70, 40));

        horizontalLayout->addWidget(pushButton_zoomBest);

        pushButton_lockRoiMove = new QPushButton(frame);
        pushButton_lockRoiMove->setObjectName(QStringLiteral("pushButton_lockRoiMove"));
        pushButton_lockRoiMove->setMinimumSize(QSize(70, 40));
        pushButton_lockRoiMove->setMaximumSize(QSize(70, 40));

        horizontalLayout->addWidget(pushButton_lockRoiMove);

        horizontalSpacer = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_mousePos = new QLabel(frame);
        label_mousePos->setObjectName(QStringLiteral("label_mousePos"));
        label_mousePos->setMinimumSize(QSize(150, 40));
        label_mousePos->setMaximumSize(QSize(150, 40));

        horizontalLayout->addWidget(label_mousePos);


        verticalLayout->addWidget(frame);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(CMvFindRoundParamWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(382, 602));
        tabWidget->setMaximumSize(QSize(380, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tableWidget_input = new QTableWidget(tab);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_input->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_input->setItem(0, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_input->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_input->setItem(1, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_input->setItem(2, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_input->setItem(2, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_input->setItem(3, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_input->setItem(3, 1, __qtablewidgetitem13);
        tableWidget_input->setObjectName(QStringLiteral("tableWidget_input"));
        tableWidget_input->setGeometry(QRect(10, 110, 361, 382));
        tableWidget_input->setMinimumSize(QSize(361, 382));
        tableWidget_input->setMaximumSize(QSize(361, 382));
        tableWidget_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_input->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_input->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_input->setShowGrid(false);
        tableWidget_input->horizontalHeader()->setStretchLastSection(true);
        tableWidget_input->verticalHeader()->setVisible(false);
        label_funcName_2 = new QLabel(tab);
        label_funcName_2->setObjectName(QStringLiteral("label_funcName_2"));
        label_funcName_2->setGeometry(QRect(20, 30, 81, 16));
        label_roiCreat_2 = new QLabel(tab);
        label_roiCreat_2->setObjectName(QStringLiteral("label_roiCreat_2"));
        label_roiCreat_2->setGeometry(QRect(20, 70, 91, 16));
        checkBox_enableFunc_2 = new QCheckBox(tab);
        checkBox_enableFunc_2->setObjectName(QStringLiteral("checkBox_enableFunc_2"));
        checkBox_enableFunc_2->setGeometry(QRect(270, 20, 101, 31));
        checkBox_enableFunc_2->setMinimumSize(QSize(101, 31));
        checkBox_enableFunc_2->setChecked(true);
        checkBox_roiCreat_2 = new QCheckBox(tab);
        checkBox_roiCreat_2->setObjectName(QStringLiteral("checkBox_roiCreat_2"));
        checkBox_roiCreat_2->setGeometry(QRect(270, 60, 101, 31));
        checkBox_roiCreat_2->setMinimumSize(QSize(101, 31));
        checkBox_roiCreat_2->setChecked(true);
        checkBox_roiCreat_2->setTristate(false);
        plainTextEdit_funcName_2 = new QPlainTextEdit(tab);
        plainTextEdit_funcName_2->setObjectName(QStringLiteral("plainTextEdit_funcName_2"));
        plainTextEdit_funcName_2->setGeometry(QRect(130, 20, 131, 31));
        plainTextEdit_funcName_2->setMinimumSize(QSize(131, 31));
        plainTextEdit_funcName_2->setMaximumSize(QSize(131, 31));
        plainTextEdit_funcName_2->setOverwriteMode(false);
        comboBox_imageSource_3 = new QComboBox(tab);
        comboBox_imageSource_3->setObjectName(QStringLiteral("comboBox_imageSource_3"));
        comboBox_imageSource_3->setGeometry(QRect(130, 60, 131, 31));
        comboBox_imageSource_3->setMinimumSize(QSize(131, 31));
        comboBox_imageSource_3->setMaximumSize(QSize(131, 31));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        spinBox_threshold_2 = new QSpinBox(tab_2);
        spinBox_threshold_2->setObjectName(QStringLiteral("spinBox_threshold_2"));
        spinBox_threshold_2->setEnabled(false);
        spinBox_threshold_2->setGeometry(QRect(130, 50, 101, 31));
        spinBox_threshold_2->setMinimumSize(QSize(101, 31));
        spinBox_threshold_2->setMaximumSize(QSize(101, 31));
        spinBox_threshold_2->setMinimum(5);
        spinBox_threshold_2->setMaximum(299);
        comboBox_thresholdType_2 = new QComboBox(tab_2);
        comboBox_thresholdType_2->setObjectName(QStringLiteral("comboBox_thresholdType_2"));
        comboBox_thresholdType_2->setGeometry(QRect(10, 50, 101, 31));
        comboBox_thresholdType_2->setMinimumSize(QSize(101, 31));
        label_thresholdType_2 = new QLabel(tab_2);
        label_thresholdType_2->setObjectName(QStringLiteral("label_thresholdType_2"));
        label_thresholdType_2->setGeometry(QRect(10, 20, 111, 31));
        label_scanDirection_2 = new QLabel(tab_2);
        label_scanDirection_2->setObjectName(QStringLiteral("label_scanDirection_2"));
        label_scanDirection_2->setGeometry(QRect(10, 90, 111, 31));
        label_threshold_2 = new QLabel(tab_2);
        label_threshold_2->setObjectName(QStringLiteral("label_threshold_2"));
        label_threshold_2->setGeometry(QRect(130, 20, 111, 31));
        label_edgeCheckType_2 = new QLabel(tab_2);
        label_edgeCheckType_2->setObjectName(QStringLiteral("label_edgeCheckType_2"));
        label_edgeCheckType_2->setGeometry(QRect(130, 90, 111, 31));
        label_scanPointSum_2 = new QLabel(tab_2);
        label_scanPointSum_2->setObjectName(QStringLiteral("label_scanPointSum_2"));
        label_scanPointSum_2->setGeometry(QRect(10, 160, 111, 31));
        label_samplingPointSum_2 = new QLabel(tab_2);
        label_samplingPointSum_2->setObjectName(QStringLiteral("label_samplingPointSum_2"));
        label_samplingPointSum_2->setGeometry(QRect(130, 160, 111, 31));
        label_fitRange_2 = new QLabel(tab_2);
        label_fitRange_2->setObjectName(QStringLiteral("label_fitRange_2"));
        label_fitRange_2->setGeometry(QRect(250, 160, 111, 31));
        comboBox_scanDirection_2 = new QComboBox(tab_2);
        comboBox_scanDirection_2->setObjectName(QStringLiteral("comboBox_scanDirection_2"));
        comboBox_scanDirection_2->setGeometry(QRect(10, 120, 101, 31));
        comboBox_scanDirection_2->setMinimumSize(QSize(101, 31));
        comboBox_edgeCheckType_2 = new QComboBox(tab_2);
        comboBox_edgeCheckType_2->setObjectName(QStringLiteral("comboBox_edgeCheckType_2"));
        comboBox_edgeCheckType_2->setGeometry(QRect(130, 120, 101, 31));
        comboBox_edgeCheckType_2->setMinimumSize(QSize(101, 31));
        label_titleJudged_2 = new QLabel(tab_2);
        label_titleJudged_2->setObjectName(QStringLiteral("label_titleJudged_2"));
        label_titleJudged_2->setGeometry(QRect(0, 230, 381, 31));
        label_titleJudged_2->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(80, 80, 80, 255), stop:1 rgba(120, 120, 120, 120));\n"
"color: rgb(255, 255, 255);"));
        label_titleJudged_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBox_scanPointSum_2 = new QSpinBox(tab_2);
        spinBox_scanPointSum_2->setObjectName(QStringLiteral("spinBox_scanPointSum_2"));
        spinBox_scanPointSum_2->setGeometry(QRect(10, 190, 101, 31));
        spinBox_scanPointSum_2->setMinimumSize(QSize(101, 31));
        spinBox_scanPointSum_2->setMaximumSize(QSize(101, 31));
        spinBox_scanPointSum_2->setMinimum(5);
        spinBox_scanPointSum_2->setMaximum(299);
        spinBox_samplingPointSum_2 = new QSpinBox(tab_2);
        spinBox_samplingPointSum_2->setObjectName(QStringLiteral("spinBox_samplingPointSum_2"));
        spinBox_samplingPointSum_2->setGeometry(QRect(130, 190, 101, 31));
        spinBox_samplingPointSum_2->setMinimumSize(QSize(101, 31));
        spinBox_samplingPointSum_2->setMaximumSize(QSize(101, 31));
        spinBox_samplingPointSum_2->setMinimum(5);
        spinBox_samplingPointSum_2->setMaximum(299);
        spinBox_fitRange_2 = new QSpinBox(tab_2);
        spinBox_fitRange_2->setObjectName(QStringLiteral("spinBox_fitRange_2"));
        spinBox_fitRange_2->setGeometry(QRect(250, 190, 101, 31));
        spinBox_fitRange_2->setMinimumSize(QSize(101, 31));
        spinBox_fitRange_2->setMaximumSize(QSize(101, 31));
        spinBox_fitRange_2->setMinimum(5);
        spinBox_fitRange_2->setMaximum(299);
        checkBox_concaveConvex = new QCheckBox(tab_2);
        checkBox_concaveConvex->setObjectName(QStringLiteral("checkBox_concaveConvex"));
        checkBox_concaveConvex->setGeometry(QRect(10, 430, 111, 31));
        widget_Judged_2 = new QWidget(tab_2);
        widget_Judged_2->setObjectName(QStringLiteral("widget_Judged_2"));
        widget_Judged_2->setGeometry(QRect(0, 260, 371, 161));
        spinBox_fitBias_2 = new QSpinBox(widget_Judged_2);
        spinBox_fitBias_2->setObjectName(QStringLiteral("spinBox_fitBias_2"));
        spinBox_fitBias_2->setGeometry(QRect(10, 40, 101, 31));
        spinBox_fitBias_2->setMinimum(5);
        spinBox_fitBias_2->setMaximum(299);
        label_fitBias_2 = new QLabel(widget_Judged_2);
        label_fitBias_2->setObjectName(QStringLiteral("label_fitBias_2"));
        label_fitBias_2->setGeometry(QRect(10, 10, 111, 31));
        spinBox_minRoundRadius = new QSpinBox(widget_Judged_2);
        spinBox_minRoundRadius->setObjectName(QStringLiteral("spinBox_minRoundRadius"));
        spinBox_minRoundRadius->setGeometry(QRect(10, 110, 101, 31));
        spinBox_minRoundRadius->setMinimum(5);
        spinBox_minRoundRadius->setMaximum(299);
        label_minRoundRadius = new QLabel(widget_Judged_2);
        label_minRoundRadius->setObjectName(QStringLiteral("label_minRoundRadius"));
        label_minRoundRadius->setGeometry(QRect(10, 80, 111, 31));
        spinBox_maxRoundRadius = new QSpinBox(widget_Judged_2);
        spinBox_maxRoundRadius->setObjectName(QStringLiteral("spinBox_maxRoundRadius"));
        spinBox_maxRoundRadius->setGeometry(QRect(130, 110, 101, 31));
        spinBox_maxRoundRadius->setMinimum(5);
        spinBox_maxRoundRadius->setMaximum(299);
        label_maxRoundRadius = new QLabel(widget_Judged_2);
        label_maxRoundRadius->setObjectName(QStringLiteral("label_maxRoundRadius"));
        label_maxRoundRadius->setGeometry(QRect(130, 80, 111, 31));
        widget_concaveConvex = new QWidget(tab_2);
        widget_concaveConvex->setObjectName(QStringLiteral("widget_concaveConvex"));
        widget_concaveConvex->setEnabled(false);
        widget_concaveConvex->setGeometry(QRect(10, 460, 361, 101));
        doubleSpinBox_minimumDepth = new QDoubleSpinBox(widget_concaveConvex);
        doubleSpinBox_minimumDepth->setObjectName(QStringLiteral("doubleSpinBox_minimumDepth"));
        doubleSpinBox_minimumDepth->setGeometry(QRect(0, 40, 101, 31));
        label_minimumDepth = new QLabel(widget_concaveConvex);
        label_minimumDepth->setObjectName(QStringLiteral("label_minimumDepth"));
        label_minimumDepth->setGeometry(QRect(0, 10, 111, 31));
        doubleSpinBox_minimumSamplingPoints = new QDoubleSpinBox(widget_concaveConvex);
        doubleSpinBox_minimumSamplingPoints->setObjectName(QStringLiteral("doubleSpinBox_minimumSamplingPoints"));
        doubleSpinBox_minimumSamplingPoints->setGeometry(QRect(120, 40, 101, 31));
        label_2_minimumSamplingPoints = new QLabel(widget_concaveConvex);
        label_2_minimumSamplingPoints->setObjectName(QStringLiteral("label_2_minimumSamplingPoints"));
        label_2_minimumSamplingPoints->setGeometry(QRect(120, 10, 111, 31));
        pushButton_unqualifiedPiont = new QPushButton(widget_concaveConvex);
        pushButton_unqualifiedPiont->setObjectName(QStringLiteral("pushButton_unqualifiedPiont"));
        pushButton_unqualifiedPiont->setGeometry(QRect(240, 40, 101, 31));
        label_unqualifiedPiont = new QLabel(widget_concaveConvex);
        label_unqualifiedPiont->setObjectName(QStringLiteral("label_unqualifiedPiont"));
        label_unqualifiedPiont->setGeometry(QRect(240, 10, 111, 31));
        tabWidget->addTab(tab_2, QString());
        widget_concaveConvex->raise();
        spinBox_threshold_2->raise();
        comboBox_thresholdType_2->raise();
        label_thresholdType_2->raise();
        label_scanDirection_2->raise();
        label_threshold_2->raise();
        label_edgeCheckType_2->raise();
        label_scanPointSum_2->raise();
        label_samplingPointSum_2->raise();
        label_fitRange_2->raise();
        comboBox_scanDirection_2->raise();
        comboBox_edgeCheckType_2->raise();
        label_titleJudged_2->raise();
        spinBox_scanPointSum_2->raise();
        spinBox_samplingPointSum_2->raise();
        spinBox_fitRange_2->raise();
        checkBox_concaveConvex->raise();
        widget_Judged_2->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        widget_3 = new QWidget(tab_3);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setEnabled(false);
        widget_3->setGeometry(QRect(0, 50, 371, 251));
        label_penWidth_2 = new QLabel(widget_3);
        label_penWidth_2->setObjectName(QStringLiteral("label_penWidth_2"));
        label_penWidth_2->setGeometry(QRect(10, 50, 111, 31));
        spinBox_lightTime_3 = new QSpinBox(widget_3);
        spinBox_lightTime_3->setObjectName(QStringLiteral("spinBox_lightTime_3"));
        spinBox_lightTime_3->setGeometry(QRect(130, 50, 131, 31));
        spinBox_lightTime_3->setMinimum(5);
        spinBox_lightTime_3->setMaximum(1000);
        pushButton_maskAll_2 = new QPushButton(widget_3);
        pushButton_maskAll_2->setObjectName(QStringLiteral("pushButton_maskAll_2"));
        pushButton_maskAll_2->setGeometry(QRect(10, 160, 121, 40));
        pushButton_maskAll_2->setMinimumSize(QSize(0, 40));
        pushButton_maskAll_2->setMaximumSize(QSize(16777215, 30));
        pushButton_maskNull_2 = new QPushButton(widget_3);
        pushButton_maskNull_2->setObjectName(QStringLiteral("pushButton_maskNull_2"));
        pushButton_maskNull_2->setEnabled(false);
        pushButton_maskNull_2->setGeometry(QRect(10, 110, 121, 40));
        pushButton_maskNull_2->setMinimumSize(QSize(0, 40));
        pushButton_maskNull_2->setMaximumSize(QSize(16777215, 30));
        pushButton_saveMask_2 = new QPushButton(widget_3);
        pushButton_saveMask_2->setObjectName(QStringLiteral("pushButton_saveMask_2"));
        pushButton_saveMask_2->setGeometry(QRect(10, 210, 121, 40));
        pushButton_saveMask_2->setMinimumSize(QSize(0, 40));
        pushButton_saveMask_2->setMaximumSize(QSize(16777215, 30));
        label_lightOutputIo_10 = new QLabel(widget_3);
        label_lightOutputIo_10->setObjectName(QStringLiteral("label_lightOutputIo_10"));
        label_lightOutputIo_10->setGeometry(QRect(10, 10, 111, 31));
        comboBox_lightOutputIo_7 = new QComboBox(widget_3);
        comboBox_lightOutputIo_7->setObjectName(QStringLiteral("comboBox_lightOutputIo_7"));
        comboBox_lightOutputIo_7->setGeometry(QRect(130, 10, 131, 31));
        label_dEtectionMask = new QLabel(tab_3);
        label_dEtectionMask->setObjectName(QStringLiteral("label_dEtectionMask"));
        label_dEtectionMask->setGeometry(QRect(10, 20, 111, 31));
        comboBox_dEtectionMask = new QComboBox(tab_3);
        comboBox_dEtectionMask->setObjectName(QStringLiteral("comboBox_dEtectionMask"));
        comboBox_dEtectionMask->setGeometry(QRect(130, 20, 131, 31));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        checkBox_valuTrig_4 = new QCheckBox(tab_4);
        checkBox_valuTrig_4->setObjectName(QStringLiteral("checkBox_valuTrig_4"));
        checkBox_valuTrig_4->setGeometry(QRect(270, 20, 101, 31));
        checkBox_valuTrig_4->setChecked(true);
        label_lightOutputIo_19 = new QLabel(tab_4);
        label_lightOutputIo_19->setObjectName(QStringLiteral("label_lightOutputIo_19"));
        label_lightOutputIo_19->setGeometry(QRect(10, 60, 121, 31));
        spinBox_lightTime_5 = new QSpinBox(tab_4);
        spinBox_lightTime_5->setObjectName(QStringLiteral("spinBox_lightTime_5"));
        spinBox_lightTime_5->setGeometry(QRect(130, 20, 131, 31));
        spinBox_lightTime_5->setMinimum(1);
        spinBox_lightTime_5->setMaximum(5);
        comboBox_lightOutputIo_11 = new QComboBox(tab_4);
        comboBox_lightOutputIo_11->setObjectName(QStringLiteral("comboBox_lightOutputIo_11"));
        comboBox_lightOutputIo_11->setGeometry(QRect(130, 60, 131, 31));
        label_lightOutputIo_20 = new QLabel(tab_4);
        label_lightOutputIo_20->setObjectName(QStringLiteral("label_lightOutputIo_20"));
        label_lightOutputIo_20->setGeometry(QRect(10, 20, 121, 31));
        tabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        pushButton_ones = new QPushButton(CMvFindRoundParamWidget);
        pushButton_ones->setObjectName(QStringLiteral("pushButton_ones"));
        pushButton_ones->setMinimumSize(QSize(80, 40));
        pushButton_ones->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButton_ones);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_affirm = new QPushButton(CMvFindRoundParamWidget);
        pushButton_affirm->setObjectName(QStringLiteral("pushButton_affirm"));
        pushButton_affirm->setMinimumSize(QSize(80, 40));
        pushButton_affirm->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButton_affirm);

        pbPrev_cancel = new QPushButton(CMvFindRoundParamWidget);
        pbPrev_cancel->setObjectName(QStringLiteral("pbPrev_cancel"));
        pbPrev_cancel->setMinimumSize(QSize(80, 40));
        pbPrev_cancel->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pbPrev_cancel);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(CMvFindRoundParamWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CMvFindRoundParamWidget);
    } // setupUi

    void retranslateUi(QWidget *CMvFindRoundParamWidget)
    {
        CMvFindRoundParamWidget->setWindowTitle(QApplication::translate("CMvFindRoundParamWidget", "CMvFindRoundParamWidget", Q_NULLPTR));
        pushButton_zoomIn->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\224\276\345\244\247", Q_NULLPTR));
        pushButton_zoomOut->setText(QApplication::translate("CMvFindRoundParamWidget", "\347\274\251\345\260\217", Q_NULLPTR));
        pushButton_zoomBest->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\234\200\345\245\275\345\260\272\345\257\270", Q_NULLPTR));
        pushButton_lockRoiMove->setText(QApplication::translate("CMvFindRoundParamWidget", "\351\224\201\345\256\232ROI", Q_NULLPTR));
        label_mousePos->setText(QApplication::translate("CMvFindRoundParamWidget", "TextLabel", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_input->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CMvFindRoundParamWidget", "\350\276\223\345\205\245\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_input->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\225\260\346\215\256\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_input->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("CMvFindRoundParamWidget", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_input->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("CMvFindRoundParamWidget", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_input->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("CMvFindRoundParamWidget", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_input->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("CMvFindRoundParamWidget", "4", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget_input->isSortingEnabled();
        tableWidget_input->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_input->item(0, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\233\276\345\203\217\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_input->item(0, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_input->item(1, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("CMvFindRoundParamWidget", "ROI\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_input->item(1, 1);
        ___qtablewidgetitem9->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_input->item(2, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("CMvFindRoundParamWidget", "ROI\344\275\215\347\275\256\344\277\256\346\255\243", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_input->item(2, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_input->item(3, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\216\251\350\206\234\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_input->item(3, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        tableWidget_input->setSortingEnabled(__sortingEnabled);

        label_funcName_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\243\200\346\265\213\345\231\250\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        label_roiCreat_2->setText(QApplication::translate("CMvFindRoundParamWidget", "ROI\346\235\245\346\272\220\357\274\232", Q_NULLPTR));
        checkBox_enableFunc_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\220\257\347\224\250\346\243\200\346\265\213\345\231\250", Q_NULLPTR));
        checkBox_roiCreat_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\350\207\252\345\267\261\345\210\233\345\273\272", Q_NULLPTR));
        comboBox_imageSource_3->clear();
        comboBox_imageSource_3->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\346\255\243\346\226\271\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\345\234\206\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\345\244\232\350\276\271\345\275\242", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CMvFindRoundParamWidget", "\350\276\223\345\205\245\350\256\276\347\275\256", Q_NULLPTR));
        comboBox_thresholdType_2->clear();
        comboBox_thresholdType_2->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\350\207\252\345\212\250", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\346\211\213\345\212\250", Q_NULLPTR)
        );
        label_thresholdType_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\351\230\210\345\200\274\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        label_scanDirection_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\211\253\346\217\217\346\226\271\345\220\221\357\274\232", Q_NULLPTR));
        label_threshold_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\350\276\271\347\274\230\347\202\271\346\217\220\345\217\226\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        label_edgeCheckType_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\350\276\271\347\274\230\346\243\200\346\265\213\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        label_scanPointSum_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\211\253\346\217\217\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        label_samplingPointSum_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\212\275\346\240\267\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        label_fitRange_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\213\237\345\220\210\350\214\203\345\233\264\357\274\232", Q_NULLPTR));
        comboBox_scanDirection_2->clear();
        comboBox_scanDirection_2->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\344\273\216\344\270\212\345\210\260\344\270\213", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\344\273\216\344\270\213\345\210\260\344\270\212", Q_NULLPTR)
        );
        comboBox_edgeCheckType_2->clear();
        comboBox_edgeCheckType_2->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\344\273\216\347\231\275\345\210\260\351\273\221", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\344\273\216\351\273\221\345\210\260\347\231\275", Q_NULLPTR)
        );
        label_titleJudged_2->setText(QApplication::translate("CMvFindRoundParamWidget", "  \347\273\223\346\236\234\345\210\244\345\256\232", Q_NULLPTR));
        spinBox_scanPointSum_2->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\202\271", Q_NULLPTR));
        spinBox_samplingPointSum_2->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\202\271", Q_NULLPTR));
        spinBox_fitRange_2->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\202\271", Q_NULLPTR));
        checkBox_concaveConvex->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\274\200\345\220\257\345\207\271\345\207\270\346\200\247\346\243\200\346\265\213", Q_NULLPTR));
        spinBox_fitBias_2->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\202\271", Q_NULLPTR));
        label_fitBias_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\213\237\345\220\210\350\257\257\345\267\256\351\231\220\345\210\266\357\274\232", Q_NULLPTR));
        spinBox_minRoundRadius->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\202\271", Q_NULLPTR));
        label_minRoundRadius->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\215\212\345\276\204\344\270\213\351\231\220", Q_NULLPTR));
        spinBox_maxRoundRadius->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\202\271", Q_NULLPTR));
        label_maxRoundRadius->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\215\212\345\276\204\344\270\212\351\231\220", Q_NULLPTR));
        label_minimumDepth->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\234\200\345\260\217\346\267\261\345\272\246", Q_NULLPTR));
        label_2_minimumSamplingPoints->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\234\200\345\260\217\346\212\275\346\240\267\347\202\271\346\225\260", Q_NULLPTR));
        pushButton_unqualifiedPiont->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\230\276\347\244\272\345\207\271\345\207\270\347\202\271\344\277\241\346\201\257", Q_NULLPTR));
        label_unqualifiedPiont->setText(QApplication::translate("CMvFindRoundParamWidget", "\344\270\215\345\220\210\346\240\274\347\202\271\344\277\241\346\201\257", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("CMvFindRoundParamWidget", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label_penWidth_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\347\224\273\347\254\224\345\260\272\345\257\270\357\274\232", Q_NULLPTR));
        spinBox_lightTime_3->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\345\203\217\347\264\240", Q_NULLPTR));
        pushButton_maskAll_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\216\251\347\233\226\346\211\200\346\234\211", Q_NULLPTR));
        pushButton_maskNull_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\270\205\347\251\272\346\216\251\350\206\234", Q_NULLPTR));
        pushButton_saveMask_2->setText(QApplication::translate("CMvFindRoundParamWidget", "\344\277\235\345\255\230\344\277\256\346\224\271", Q_NULLPTR));
        label_lightOutputIo_10->setText(QApplication::translate("CMvFindRoundParamWidget", "\347\274\226\350\276\221\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        comboBox_lightOutputIo_7->clear();
        comboBox_lightOutputIo_7->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\345\242\236\345\212\240\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\345\210\240\351\231\244\346\216\251\350\206\234", Q_NULLPTR)
        );
        label_dEtectionMask->setText(QApplication::translate("CMvFindRoundParamWidget", "\346\243\200\346\265\213\345\214\272\345\237\237\347\232\204\346\216\251\350\206\234\357\274\232", Q_NULLPTR));
        comboBox_dEtectionMask->clear();
        comboBox_dEtectionMask->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\344\270\215\344\275\277\347\224\250\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\346\234\254\346\243\200\346\265\213\345\231\250ROI\345\206\205\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvFindRoundParamWidget", "\345\205\266\344\273\226\347\256\227\346\263\225\347\232\204\346\216\251\350\206\234", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("CMvFindRoundParamWidget", "\346\216\251\350\206\234\350\256\276\347\275\256", Q_NULLPTR));
        checkBox_valuTrig_4->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\220\257\347\224\250\347\273\230\345\210\266", Q_NULLPTR));
        label_lightOutputIo_19->setText(QApplication::translate("CMvFindRoundParamWidget", "\347\272\277\346\235\241\351\242\234\350\211\262\357\274\232", Q_NULLPTR));
        spinBox_lightTime_5->setSuffix(QApplication::translate("CMvFindRoundParamWidget", "\347\243\205", Q_NULLPTR));
        comboBox_lightOutputIo_11->clear();
        comboBox_lightOutputIo_11->insertItems(0, QStringList()
         << QApplication::translate("CMvFindRoundParamWidget", "\351\242\234\350\211\262", Q_NULLPTR)
        );
        label_lightOutputIo_20->setText(QApplication::translate("CMvFindRoundParamWidget", "\347\272\277\346\235\241\345\256\275\345\272\246\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("CMvFindRoundParamWidget", "\347\273\223\346\236\234\347\273\230\345\210\266", Q_NULLPTR));
        pushButton_ones->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\215\225\346\254\241", Q_NULLPTR));
        pushButton_affirm->setText(QApplication::translate("CMvFindRoundParamWidget", "\347\241\256\345\256\232", Q_NULLPTR));
        pbPrev_cancel->setText(QApplication::translate("CMvFindRoundParamWidget", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMvFindRoundParamWidget: public Ui_CMvFindRoundParamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMVFINDROUNDPARAMWIDGET_H
