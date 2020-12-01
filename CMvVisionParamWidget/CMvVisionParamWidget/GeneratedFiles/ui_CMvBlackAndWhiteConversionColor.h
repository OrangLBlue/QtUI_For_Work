/********************************************************************************
** Form generated from reading UI file 'CMvBlackAndWhiteConversionColor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMVBLACKANDWHITECONVERSIONCOLOR_H
#define UI_CMVBLACKANDWHITECONVERSIONCOLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMvBlackAndWhiteConversionColor
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_funcName_2;
    QCheckBox *checkBox_enableFunc_2;
    QPlainTextEdit *plainTextEdit_funcName_2;
    QTableWidget *tableWidget_input;
    QWidget *tab_4;
    QCheckBox *checkBox_valuTrig_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_ones;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_affirm;
    QPushButton *pbPrev_cancel;

    void setupUi(QWidget *CMvBlackAndWhiteConversionColor)
    {
        if (CMvBlackAndWhiteConversionColor->objectName().isEmpty())
            CMvBlackAndWhiteConversionColor->setObjectName(QStringLiteral("CMvBlackAndWhiteConversionColor"));
        CMvBlackAndWhiteConversionColor->resize(382, 644);
        verticalLayout = new QVBoxLayout(CMvBlackAndWhiteConversionColor);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(CMvBlackAndWhiteConversionColor);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(382, 602));
        tabWidget->setMaximumSize(QSize(380, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_funcName_2 = new QLabel(tab);
        label_funcName_2->setObjectName(QStringLiteral("label_funcName_2"));
        label_funcName_2->setGeometry(QRect(20, 30, 81, 16));
        checkBox_enableFunc_2 = new QCheckBox(tab);
        checkBox_enableFunc_2->setObjectName(QStringLiteral("checkBox_enableFunc_2"));
        checkBox_enableFunc_2->setGeometry(QRect(270, 20, 101, 31));
        checkBox_enableFunc_2->setMinimumSize(QSize(101, 31));
        checkBox_enableFunc_2->setChecked(true);
        plainTextEdit_funcName_2 = new QPlainTextEdit(tab);
        plainTextEdit_funcName_2->setObjectName(QStringLiteral("plainTextEdit_funcName_2"));
        plainTextEdit_funcName_2->setGeometry(QRect(130, 20, 131, 31));
        plainTextEdit_funcName_2->setMinimumSize(QSize(131, 31));
        plainTextEdit_funcName_2->setMaximumSize(QSize(131, 31));
        plainTextEdit_funcName_2->setOverwriteMode(false);
        tableWidget_input = new QTableWidget(tab);
        if (tableWidget_input->columnCount() < 2)
            tableWidget_input->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget_input->rowCount() < 1)
            tableWidget_input->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_input->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_input->setItem(0, 1, __qtablewidgetitem4);
        tableWidget_input->setObjectName(QStringLiteral("tableWidget_input"));
        tableWidget_input->setGeometry(QRect(20, 100, 331, 311));
        tableWidget_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_input->setShowGrid(false);
        tableWidget_input->setGridStyle(Qt::SolidLine);
        tableWidget_input->horizontalHeader()->setStretchLastSection(true);
        tableWidget_input->verticalHeader()->setVisible(false);
        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        checkBox_valuTrig_4 = new QCheckBox(tab_4);
        checkBox_valuTrig_4->setObjectName(QStringLiteral("checkBox_valuTrig_4"));
        checkBox_valuTrig_4->setGeometry(QRect(30, 20, 101, 31));
        checkBox_valuTrig_4->setChecked(true);
        tabWidget->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        pushButton_ones = new QPushButton(CMvBlackAndWhiteConversionColor);
        pushButton_ones->setObjectName(QStringLiteral("pushButton_ones"));
        pushButton_ones->setMinimumSize(QSize(80, 40));
        pushButton_ones->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButton_ones);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_affirm = new QPushButton(CMvBlackAndWhiteConversionColor);
        pushButton_affirm->setObjectName(QStringLiteral("pushButton_affirm"));
        pushButton_affirm->setMinimumSize(QSize(80, 40));
        pushButton_affirm->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButton_affirm);

        pbPrev_cancel = new QPushButton(CMvBlackAndWhiteConversionColor);
        pbPrev_cancel->setObjectName(QStringLiteral("pbPrev_cancel"));
        pbPrev_cancel->setMinimumSize(QSize(80, 40));
        pbPrev_cancel->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pbPrev_cancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CMvBlackAndWhiteConversionColor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CMvBlackAndWhiteConversionColor);
    } // setupUi

    void retranslateUi(QWidget *CMvBlackAndWhiteConversionColor)
    {
        CMvBlackAndWhiteConversionColor->setWindowTitle(QApplication::translate("CMvBlackAndWhiteConversionColor", "\351\273\221\347\231\275\350\275\254\345\275\251\350\211\262", Q_NULLPTR));
        label_funcName_2->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\346\243\200\346\265\213\345\231\250\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        checkBox_enableFunc_2->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\345\220\257\347\224\250\346\243\200\346\265\213\345\231\250", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_input->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\350\276\223\345\205\245\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_input->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\350\276\223\345\205\245\346\235\245\346\272\220", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_input->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "1", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget_input->isSortingEnabled();
        tableWidget_input->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_input->item(0, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\351\273\221\347\231\275\345\233\276\345\203\217", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_input->item(0, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\346\237\220\344\270\252\346\243\200\346\265\213\345\231\250\347\232\204\350\276\223\345\207\272", Q_NULLPTR));
        tableWidget_input->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CMvBlackAndWhiteConversionColor", "\350\276\223\345\205\245\350\256\276\347\275\256", Q_NULLPTR));
        checkBox_valuTrig_4->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\345\220\257\347\224\250\347\273\230\345\210\266", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("CMvBlackAndWhiteConversionColor", "\347\273\223\346\236\234\347\273\230\345\210\266", Q_NULLPTR));
        pushButton_ones->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\345\215\225\346\254\241", Q_NULLPTR));
        pushButton_affirm->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\347\241\256\345\256\232", Q_NULLPTR));
        pbPrev_cancel->setText(QApplication::translate("CMvBlackAndWhiteConversionColor", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMvBlackAndWhiteConversionColor: public Ui_CMvBlackAndWhiteConversionColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMVBLACKANDWHITECONVERSIONCOLOR_H
