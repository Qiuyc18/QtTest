#pragma once

#include <QMap>
#include <QPainter>
#include <QTabBar>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class HorizTabWidgetClass; };
QT_END_NAMESPACE

#define TABCOLOR_BORDER_ENABLED QColor(0, 0, 0)
#define TABCOLOR_BORDER_ENABLED_SELECTED QColor(55, 145, 215)
#define TABCOLOR_BORDER_DISABLED QColor(240, 240, 240)
#define TABCOLOR_BACKGROUND_ENABLED QColor(255, 255, 255)
#define TABCOLOR_BACKGROUND_ENABLED_SELECTED QColor(115, 186, 241)
#define TABCOLOR_BACKGROUND_ENABLED_HOVER QColor(115, 186, 241)
#define TABCOLOR_BACKGROUND_DISABLED QColor(240, 240, 240)
#define TABCOLOR_FONT_ENABLED QColor(0, 0, 0)
#define TABCOLOR_FONT_ENABLED_SELECTED QColor(255, 255, 255)
#define TABCOLOR_FONT_DISABLED QColor(240, 240, 240)

class VerticalTabBar : public QTabBar
{
	Q_OBJECT
public:
	VerticalTabBar(QWidget *parent = nullptr);
	~VerticalTabBar()
	{
	}

protected:
	void paintEvent(QPaintEvent* event) override;
	QSize tabSizeHint(int index) const override;
};


class VerticalTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	VerticalTabWidget(QWidget *parent = nullptr);
	~VerticalTabWidget()
	{
	}

private:
	QMap<int, QRect> m_tabRects;

protected:
	void paintEvent(QPaintEvent* event) override;
	void drawTabBorder(QPainter& painter, QRect rect);
};


class HorizontalTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	HorizontalTabWidget(QWidget *parent = nullptr);
	~HorizontalTabWidget()
	{
	}

private:
	QMap<int, QRect> m_tabRects;

protected:
	void paintEvent(QPaintEvent* event) override;
	void drawTabBorder(QPainter& painter, QRect tabRect);
	void drawWidgetBorder(QPainter& painter, QRect tabRect, QRect widgetRect);
};

class HorizontalTabBar : public QTabBar
{
	Q_OBJECT
public:
	HorizontalTabBar(QWidget *parent = nullptr);
	~HorizontalTabBar()
	{
	}

protected:
	void paintEvent(QPaintEvent* event) override;
	QSize tabSizeHint(int index) const override;
};