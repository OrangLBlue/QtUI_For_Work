/********************************************************************************
** Form generated from reading UI file 'CMvColorImagesCut.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMVCOLORIMAGESCUT_H
#define UI_CMVCOLORIMAGESCUT_H

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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMvColorImagesCut
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
    QLabel *label_funcName_2;
    QLabel *label_roiCreat_2;
    QCheckBox *checkBox_enableFunc_2;
    QCheckBox *checkBox_roiCreat_2;
    QPlainTextEdit *plainTextEdit_funcName_2;
    QComboBox *comboBox_imageSource_3;
    QTableWidget *tableWidget_input;
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
    QPushButton *pushbutton_cuttingPicture;
    QLabel *label_cuttingPicture;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_ones;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_affirm;
    QPushButton *pbPrev_cancel;

    void setupUi(QWidget *CMvColorImagesCut)
    {
        if (CMvColorImagesCut->objectName().isEmpty())
            CMvColorImagesCut->setObjectName(QStringLiteral("CMvColorImagesCut"));
        CMvColorImagesCut->resize(892, 652);
        horizontalLayout_3 = new QHBoxLayout(CMvColorImagesCut);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView_mainImage = new QGraphicsView(CMvColorImagesCut);
        graphicsView_mainImage->setObjectName(QStringLiteral("graphicsView_mainImage"));
        graphicsView_mainImage->setMinimumSize(QSize(500, 600));

        verticalLayout->addWidget(graphicsView_mainImage);

        frame = new QFrame(CMvColorImagesCut);
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
        tabWidget = new QTabWidget(CMvColorImagesCut);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(382, 602));
        tabWidget->setMaximumSize(QSize(380, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
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
        tableWidget_input = new QTableWidget(tab);
        if (tableWidget_input->columnCount() < 2)
            tableWidget_input->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget_input->rowCount() < 2)
            tableWidget_input->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_input->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_input->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_input->setItem(1, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_input->setItem(1, 1, __qtablewidgetitem7);
        tableWidget_input->setObjectName(QStringLiteral("tableWidget_input"));
        tableWidget_input->setGeometry(QRect(20, 120, 341, 361));
        tableWidget_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_input->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_input->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidget_input->setShowGrid(false);
        tableWidget_input->setSortingEnabled(false);
        tableWidget_input->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget_input->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget_input->horizontalHeader()->setStretchLastSection(true);
        tableWidget_input->verticalHeader()->setVisible(false);
        tableWidget_input->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        widget_3 = new QWidget(tab_3);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setEnabled(false);
        widget_3->setGeometry(QRect(0, 60, 371, 251));
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
        checkBox_valuTrig_4->setGeometry(QRect(120, 10, 80, 40));
        checkBox_valuTrig_4->setChecked(true);
        pushbutton_cuttingPicture = new QPushButton(tab_4);
        pushbutton_cuttingPicture->setObjectName(QStringLiteral("pushbutton_cuttingPicture"));
        pushbutton_cuttingPicture->setGeometry(QRect(10, 40, 80, 40));
        label_cuttingPicture = new QLabel(tab_4);
        label_cuttingPicture->setObjectName(QStringLiteral("label_cuttingPicture"));
        label_cuttingPicture->setGeometry(QRect(10, 10, 80, 40));
        tabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        pushButton_ones = new QPushButton(CMvColorImagesCut);
        pushButton_ones->setObjectName(QStringLiteral("pushButton_ones"));
        pushButton_ones->setMinimumSize(QSize(80, 40));
        pushButton_ones->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButton_ones);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_affirm = new QPushButton(CMvColorImagesCut);
        pushButton_affirm->setObjectName(QStringLiteral("pushButton_affirm"));
        pushButton_affirm->setMinimumSize(QSize(80, 40));
        pushButton_affirm->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButton_affirm);

        pbPrev_cancel = new QPushButton(CMvColorImagesCut);
        pbPrev_cancel->setObjectName(QStringLiteral("pbPrev_cancel"));
        pbPrev_cancel->setMinimumSize(QSize(80, 40));
        pbPrev_cancel->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pbPrev_cancel);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(CMvColorImagesCut);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CMvColorImagesCut);
    } // setupUi

    void retranslateUi(QWidget *CMvColorImagesCut)
    {
        CMvColorImagesCut->setWindowTitle(QApplication::translate("CMvColorImagesCut", "\345\233\276\347\211\207\350\243\201\345\211\252", Q_NULLPTR));
        pushButton_zoomIn->setText(QApplication::translate("CMvColorImagesCut", "\346\224\276\345\244\247", Q_NULLPTR));
        pushButton_zoomOut->setText(QApplication::translate("CMvColorImagesCut", "\347\274\251\345\260\217", Q_NULLPTR));
        pushButton_zoomBest->setText(QApplication::translate("CMvColorImagesCut", "\346\234\200\345\245\275\345\260\272\345\257\270", Q_NULLPTR));
        pushButton_lockRoiMove->setText(QApplication::translate("CMvColorImagesCut", "\351\224\201\345\256\232ROI", Q_NULLPTR));
        label_mousePos->setText(QApplication::translate("CMvColorImagesCut", "TextLabel", Q_NULLPTR));
        label_funcName_2->setText(QApplication::translate("CMvColorImagesCut", "\346\243\200\346\265\213\345\231\250\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        label_roiCreat_2->setText(QApplication::translate("CMvColorImagesCut", "ROI\346\235\245\346\272\220\357\274\232", Q_NULLPTR));
        checkBox_enableFunc_2->setText(QApplication::translate("CMvColorImagesCut", "\345\220\257\347\224\250\346\243\200\346\265\213\345\231\250", Q_NULLPTR));
        checkBox_roiCreat_2->setText(QApplication::translate("CMvColorImagesCut", "\350\207\252\345\267\261\345\210\233\345\273\272", Q_NULLPTR));
        comboBox_imageSource_3->clear();
        comboBox_imageSource_3->insertItems(0, QStringList()
         << QApplication::translate("CMvColorImagesCut", "\346\255\243\346\226\271\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvColorImagesCut", "\345\234\206\345\275\242", Q_NULLPTR)
         << QApplication::translate("CMvColorImagesCut", "\345\244\232\350\276\271\345\275\242", Q_NULLPTR)
        );
        QTableWidgetItem *___qtablewidgetitem = tableWidget_input->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CMvColorImagesCut", "\350\276\223\345\205\245\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_input->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CMvColorImagesCut", "\346\225\260\346\215\256\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_input->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("CMvColorImagesCut", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_input->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("CMvColorImagesCut", "2", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget_input->isSortingEnabled();
        tableWidget_input->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_input->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("CMvColorImagesCut", "\345\275\251\350\211\262\345\233\276\345\203\217", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_input->item(0, 1);
        ___qtablewidgetitem5->setText(QApplication::translate("CMvColorImagesCut", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_input->item(1, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("CMvColorImagesCut", "\345\235\220\346\240\207\347\263\273\350\276\223\345\205\245 ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_input->item(1, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("CMvColorImagesCut", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        tableWidget_input->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CMvColorImagesCut", "\350\276\223\345\205\245\350\256\276\347\275\256", Q_NULLPTR));
        label_penWidth_2->setText(QApplication::translate("CMvColorImagesCut", "\347\224\273\347\254\224\345\260\272\345\257\270\357\274\232", Q_NULLPTR));
        spinBox_lightTime_3->setSuffix(QApplication::translate("CMvColorImagesCut", "\345\203\217\347\264\240", Q_NULLPTR));
        pushButton_maskAll_2->setText(QApplication::translate("CMvColorImagesCut", "\346\216\251\347\233\226\346\211\200\346\234\211", Q_NULLPTR));
        pushButton_maskNull_2->setText(QApplication::translate("CMvColorImagesCut", "\346\270\205\347\251\272\346\216\251\350\206\234", Q_NULLPTR));
        pushButton_saveMask_2->setText(QApplication::translate("CMvColorImagesCut", "\344\277\235\345\255\230\344\277\256\346\224\271", Q_NULLPTR));
        label_lightOutputIo_10->setText(QApplication::translate("CMvColorImagesCut", "\347\274\226\350\276\221\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        comboBox_lightOutputIo_7->clear();
        comboBox_lightOutputIo_7->insertItems(0, QStringList()
         << QApplication::translate("CMvColorImagesCut", "\345\242\236\345\212\240\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvColorImagesCut", "\345\210\240\351\231\244\346\216\251\350\206\234", Q_NULLPTR)
        );
        label_dEtectionMask->setText(QApplication::translate("CMvColorImagesCut", "\346\243\200\346\265\213\345\214\272\345\237\237\347\232\204\346\216\251\350\206\234\357\274\232", Q_NULLPTR));
        comboBox_dEtectionMask->clear();
        comboBox_dEtectionMask->insertItems(0, QStringList()
         << QApplication::translate("CMvColorImagesCut", "\344\270\215\344\275\277\347\224\250\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvColorImagesCut", "\346\234\254\346\243\200\346\265\213\345\231\250ROI\345\206\205\346\216\251\350\206\234", Q_NULLPTR)
         << QApplication::translate("CMvColorImagesCut", "\345\205\266\344\273\226\347\256\227\346\263\225\347\232\204\346\216\251\350\206\234", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("CMvColorImagesCut", "\346\216\251\350\206\234\350\256\276\347\275\256", Q_NULLPTR));
        checkBox_valuTrig_4->setText(QApplication::translate("CMvColorImagesCut", "\345\220\257\347\224\250\347\273\230\345\210\266", Q_NULLPTR));
        pushbutton_cuttingPicture->setText(QApplication::translate("CMvColorImagesCut", "\346\230\276\347\244\272\350\243\201\345\211\252\345\233\276\345\203\217", Q_NULLPTR));
        label_cuttingPicture->setText(QApplication::translate("CMvColorImagesCut", "\350\243\201\345\211\252\345\233\276\345\203\217\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("CMvColorImagesCut", "\347\273\223\346\236\234\347\273\230\345\210\266", Q_NULLPTR));
        pushButton_ones->setText(QApplication::translate("CMvColorImagesCut", "\345\215\225\346\254\241", Q_NULLPTR));
        pushButton_affirm->setText(QApplication::translate("CMvColorImagesCut", "\347\241\256\345\256\232", Q_NULLPTR));
        pbPrev_cancel->setText(QApplication::translate("CMvColorImagesCut", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMvColorImagesCut: public Ui_CMvColorImagesCut {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMVCOLORIMAGESCUT_H
