#pragma once
#pragma execution_character_set("utf-8")

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QProxyStyle>
#include <QSettings>
#include <QTextCodec>

#include <iostream>

#include "CDataFrame.h"
#include "ui_PostSettingWin.h"

class CustomTabStyle : public QProxyStyle
{
public:
	QSize sizeFromContents(ContentsType type, const QStyleOption *option,
		const QSize &size, const QWidget *widget) const
	{
		QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
		if (type == QStyle::CT_TabBarTab) {
			s.transpose();
			s.rwidth() = 65; // 设置每个tabBar中item的大小
			s.rheight() = 28;
		}
		return s;
	}

	void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
	{
		if (element == CE_TabBarTabLabel) {
			if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
				QRect allRect = tab->rect;
				QFont font;
				font.setFamily("Microsoft YaHei");

				QTextOption textOption;
				textOption.setAlignment(Qt::AlignCenter);

				painter->save();
				painter->setPen(QColor(0, 0, 0));
				if (tab->state & QStyle::State_Selected && tab->state & QStyle::State_Enabled)
				{// 如果是选中状态，且tab可用
					painter->setPen(QPen(QColor(70, 184, 70), 2));
				}
				else if (tab->state & QStyle::State_MouseOver && tab->state & QStyle::State_Enabled)
				{// 如果是hover状态，且tab可用
					painter->setPen(QColor(70, 184, 70));
				}
				else if (!tab->state & QStyle::State_Enabled)
				{// 如果是tab禁用状态
					painter->setPen(QColor(240, 240, 240));
					painter->setBrush(QBrush(QColor(240, 240, 240)));
				}
				else 
				{// 如果是未选中状态，且tab可用
					painter->setPen(QColor(70, 184, 70));
				}

				// 绘制tab边框
				QPainterPath path;
				qreal radius = 8; //设置圆角半径
				path.moveTo(allRect.left() + radius, allRect.top());
				path.arcTo(allRect.left(), allRect.top(), radius * 2, radius * 2, 90, 90);
				path.lineTo(allRect.left(), allRect.bottom() - radius * 2);
				path.arcTo(allRect.left(), allRect.bottom() - radius * 2, radius * 2, radius * 2, 180, 90);
				path.lineTo(allRect.right(), allRect.bottom());
				path.lineTo(allRect.topRight());
				path.lineTo(allRect.left() + radius, allRect.top());
				painter->drawPath(path);

				// 显示汉字
				painter->setPen(QColor(0, 0, 0));
				if (tab->state & QStyle::State_Selected && tab->state & QStyle::State_Enabled)
				{// 如果是选中状态，且tab可用
					font.setBold(true);
				}
				else if (tab->state & QStyle::State_MouseOver && tab->state & QStyle::State_Enabled)
				{// 如果是hover状态，且tab可用
					font.setBold(true);
				}
				else if (!tab->state & QStyle::State_Enabled)
				{// 如果是tab禁用状态
					painter->setPen(QColor(240, 240, 240));
					painter->setBrush(QBrush(QColor(240, 240, 240)));
				}
				else
				{// 如果是未选中状态，且tab可用
					font.setBold(false);
				}
				painter->setFont(font);
				painter->drawText(allRect, tab->text, textOption);
				painter->restore();
			}
		}
		else if (element == CE_TabBarTab)
		{
			QProxyStyle::drawControl(element, option, painter, widget);
		}
	}
};

class QtTest : public QMainWindow
{
	Q_OBJECT

public:
	QtTest(QWidget* parent = nullptr);
	~QtTest() override;

private:
	Ui::PostSettingWinClass ui;
	CDataFrame m_dfAiResInfo;
	QStringList m_ListAreaType = {};

	void setTabWidgetForAreaSetting()
	{
		//设置区域TabWidget标签为水平
		QTabWidget *tabw = ui.TabWidgetAIErrArea;
		QTabBar *tabbar = tabw->tabBar();

		ui.TabWidgetAIErrArea->tabBar()->setStyle(new CustomTabStyle);
	}
};
