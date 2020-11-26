#pragma once

#include <QtWidgets/QWidget>
#include "ui_CMvFindRoundParamWidget.h"

class CMvFindRoundParamWidget : public QWidget
{
    Q_OBJECT

public:
    CMvFindRoundParamWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::CMvFindRoundParamWidgetClass ui;
};
