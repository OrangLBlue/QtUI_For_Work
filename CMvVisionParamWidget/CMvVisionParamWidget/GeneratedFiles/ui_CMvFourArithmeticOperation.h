/********************************************************************************
** Form generated from reading UI file 'CMvFourArithmeticOperation.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMVFOURARITHMETICOPERATION_H
#define UI_CMVFOURARITHMETICOPERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMvFourArithmeticOperation
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget_input;

    void setupUi(QWidget *CMvFourArithmeticOperation)
    {
        if (CMvFourArithmeticOperation->objectName().isEmpty())
            CMvFourArithmeticOperation->setObjectName(QStringLiteral("CMvFourArithmeticOperation"));
        CMvFourArithmeticOperation->resize(540, 682);
        CMvFourArithmeticOperation->setMinimumSize(QSize(321, 149));
        CMvFourArithmeticOperation->setMaximumSize(QSize(10000000, 10000000));
        CMvFourArithmeticOperation->setFocusPolicy(Qt::NoFocus);
        verticalLayout = new QVBoxLayout(CMvFourArithmeticOperation);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget_input = new QTableWidget(CMvFourArithmeticOperation);
        if (tableWidget_input->columnCount() < 3)
            tableWidget_input->setColumnCount(3);
        QFont font;
        font.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget_input->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_input->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_input->rowCount() < 1)
            tableWidget_input->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_input->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget_input->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget_input->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget_input->setItem(0, 2, __qtablewidgetitem6);
        tableWidget_input->setObjectName(QStringLiteral("tableWidget_input"));
        tableWidget_input->setFocusPolicy(Qt::StrongFocus);
        tableWidget_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_input->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_input->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableWidget_input->setShowGrid(false);
        tableWidget_input->setGridStyle(Qt::NoPen);
        tableWidget_input->horizontalHeader()->setVisible(true);
        tableWidget_input->horizontalHeader()->setHighlightSections(true);
        tableWidget_input->horizontalHeader()->setStretchLastSection(true);
        tableWidget_input->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget_input);


        retranslateUi(CMvFourArithmeticOperation);

        QMetaObject::connectSlotsByName(CMvFourArithmeticOperation);
    } // setupUi

    void retranslateUi(QWidget *CMvFourArithmeticOperation)
    {
        CMvFourArithmeticOperation->setWindowTitle(QApplication::translate("CMvFourArithmeticOperation", "\345\233\233\345\210\231\350\277\220\347\256\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_input->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CMvFourArithmeticOperation", "\350\276\223\345\205\245\346\225\260\345\200\274\344\270\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_input->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CMvFourArithmeticOperation", "\350\277\220\347\256\227\346\263\225\345\210\231", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_input->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CMvFourArithmeticOperation", "\350\276\223\345\205\245\346\225\260\345\200\274\344\272\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_input->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("CMvFourArithmeticOperation", "1", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget_input->isSortingEnabled();
        tableWidget_input->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_input->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("CMvFourArithmeticOperation", "\347\202\271\345\207\273\350\276\223\345\205\245\347\256\227\346\263\225", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_input->item(0, 2);
        ___qtablewidgetitem5->setText(QApplication::translate("CMvFourArithmeticOperation", "\347\202\271\345\207\273\350\276\223\345\205\245\347\256\227\346\263\225", Q_NULLPTR));
        tableWidget_input->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class CMvFourArithmeticOperation: public Ui_CMvFourArithmeticOperation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMVFOURARITHMETICOPERATION_H
