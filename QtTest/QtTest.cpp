#include "QtTest.h"

QtTest::QtTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	 //��������TabWidget��ǩΪˮƽ
	//setTabWidgetForAreaSetting();

	ui.TabWidgetAIErrArea->setTabEnabled(1, false);
}

QtTest::~QtTest()
{}

