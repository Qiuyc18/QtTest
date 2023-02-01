#include "QtTest.h"

QtTest::QtTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	 //设置区域TabWidget标签为水平
	//setTabWidgetForAreaSetting();

	ui.TabWidgetAIErrArea->setTabEnabled(1, false);
}

QtTest::~QtTest()
{}

