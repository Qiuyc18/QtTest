#include "CustomTabWidget.h"

#include <qtabbar.h>

VerticalTabBar::VerticalTabBar(QWidget* parent) : QTabBar(parent)
{
}

void VerticalTabBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QTextOption textOption;
	textOption.setAlignment(Qt::AlignCenter);
	painter.rotate(-90);

	for (int i = 0; i < count(); i++)
	{
		QString text = tabText(i);
		QRect rect = tabRect(i);

		QPoint center = rect.center();

		painter.save();
		painter.translate(center);
		painter.rotate(-90);
		painter.drawText(rect, text, textOption);
		painter.restore();
	}
}

QSize VerticalTabBar::tabSizeHint(int index) const
{
	QSize size = QTabBar::tabSizeHint(index);
	size.transpose();
	size.rwidth() = 65; // 设置每个tabBar中item的大小
	size.rheight() = 32;
	return size;
}

VerticalTabWidget::VerticalTabWidget(QWidget* parent) : QTabWidget(parent)
{
	this->setTabBar(new VerticalTabBar);
}

void VerticalTabWidget::paintEvent(QPaintEvent* event)
{
	// 使用QPainter绘制tab
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	auto* tabBar = this->tabBar();
	// 绘制基本属性——禁用状态or正常状态
	int nTabCount = tabBar->count();
	int currentIndex = this->currentIndex();
	int offset = 4;

	m_tabRects.clear();
	for (int i = 0; i < nTabCount; i++)
	{
		painter.save();
		QString text = tabBar->tabText(i);
		QRect tabRect = tabBar->tabRect(i);
		tabRect.adjust(0, offset, 0, offset); // 加上偏移量

		if (!tabRect.isValid())
		{
			continue;
		}
		m_tabRects[i] = tabRect;

		QFont font;
		font.setFamily("Microsoft YaHei");

		QTextOption textOption;
		textOption.setAlignment(Qt::AlignCenter);

		if (this->isTabEnabled(i))
		{// 如果是正常状态
			if(i == currentIndex)
			{// 如果选中了
				painter.setPen(QPen(TABCOLOR_BORDER_ENABLED_SELECTED, 3));
				painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED_SELECTED));
				drawTabBorder(painter, tabRect);

				painter.setPen(TABCOLOR_FONT_ENABLED_SELECTED);
				font.setBold(true);
			}
			else if (tabBar->tabAt(mapFromGlobal(QCursor::pos())) == i)
			{// 如果未选中，但是鼠标hover
				painter.setPen(QPen(TABCOLOR_BACKGROUND_ENABLED_HOVER, 2));
				painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED));
				drawTabBorder(painter, tabRect);

				painter.setPen(TABCOLOR_FONT_ENABLED);
				font.setBold(true);
			}
			else
			{// 如果未选中
				painter.setPen(TABCOLOR_BORDER_ENABLED);
				painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED));
				drawTabBorder(painter, tabRect);

				painter.setPen(TABCOLOR_FONT_ENABLED);
				font.setBold(false);
			}
		}
		else
		{// 如果是禁用状态
			painter.setPen(TABCOLOR_BORDER_DISABLED);
			painter.setBrush(QBrush(TABCOLOR_BACKGROUND_DISABLED));
			drawTabBorder(painter, tabRect);

			painter.setPen(TABCOLOR_FONT_DISABLED);
			painter.setBrush(QBrush(TABCOLOR_BACKGROUND_DISABLED));
		}
		painter.setFont(font);
		painter.drawText(tabRect, text, textOption);
		painter.restore();
	}

}

void VerticalTabWidget::drawTabBorder(QPainter& painter, QRect rect)
{
	// 绘制tab边框
	QPainterPath path;
	qreal radius = 8; //设置圆角半径
	path.moveTo(rect.left() + radius, rect.top());
	path.arcTo(rect.left(), rect.top(), radius * 2, radius * 2, 90, 90);
	path.lineTo(rect.left(), rect.bottom() - radius * 2);
	path.arcTo(rect.left(), rect.bottom() - radius * 2, radius * 2, radius * 2, 180, 90);
	path.lineTo(rect.right(), rect.bottom());
	path.lineTo(rect.topRight());
	path.lineTo(rect.left() + radius, rect.top());
	painter.drawPath(path);
}


HorizontalTabBar::HorizontalTabBar(QWidget* parent) : QTabBar(parent)
{
}

void HorizontalTabBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QTextOption textOption;
	textOption.setAlignment(Qt::AlignCenter);
	painter.rotate(-90);

	for (int i = 0; i < count(); i++)
	{
		QString text = tabText(i);
		QRect rect = tabRect(i);

		QPoint center = rect.center();

		painter.save();
		painter.drawText(rect, text, textOption);
		painter.restore();
	}
}

QSize HorizontalTabBar::tabSizeHint(int index) const
{
	QSize size = QTabBar::tabSizeHint(index);
	size.transpose();
	size.rwidth() = tabText(index).size() * 8 + 28; // 设置每个tabBar中item的大小
	size.rheight() = 20;
	return size;
}

HorizontalTabWidget::HorizontalTabWidget(QWidget* parent) : QTabWidget(parent)
{
	this->setTabBar(new HorizontalTabBar);
}

void HorizontalTabWidget::paintEvent(QPaintEvent* event)
{	// 使用QPainter绘制tab
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	auto* tabBar = this->tabBar();
	// 绘制基本属性——禁用状态or正常状态
	int nTabCount = tabBar->count();
	int currentIndex = this->currentIndex();

	m_tabRects.clear();
	// 绘制widget
	for (int i = 0; i < nTabCount; i++)
	{
		QString text = tabBar->tabText(i);
		QRect tabRect = tabBar->tabRect(i);
		QRect widgetRect = widget(i)->rect();
		painter.eraseRect(widgetRect);
		painter.save();
		painter.setPen(QColor(0, 0, 0));
		painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED));
		drawWidgetBorder(painter, tabRect, widgetRect);
		painter.restore();
	}

	// 绘制tab
	for (int i = 0; i < nTabCount; i++)
	{
		QString text = tabBar->tabText(i);
		QRect tabRect = tabBar->tabRect(i);
		QRect widgetRect = rect();

		if (!tabRect.isValid())
		{
			continue;
		}
		m_tabRects[i] = tabRect;

		QFont font;
		font.setFamily("Microsoft YaHei");

		QTextOption textOption;
		textOption.setAlignment(Qt::AlignCenter);
		painter.save();

		if (this->isTabEnabled(i))
		{// 如果是正常状态
			if (i == currentIndex)
			{// 如果选中了
				painter.setPen(QPen(TABCOLOR_BORDER_ENABLED_SELECTED, 3));
				painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED_SELECTED));
				drawTabBorder(painter, tabRect);

				painter.setPen(TABCOLOR_FONT_ENABLED_SELECTED);
				font.setBold(true);
			}
			else if (tabBar->tabAt(mapFromGlobal(QCursor::pos())) == i)
			{// 如果未选中，但是鼠标hover
				painter.setPen(QPen(TABCOLOR_BACKGROUND_ENABLED_HOVER, 2));
				painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED));
				drawTabBorder(painter, tabRect);

				painter.setPen(TABCOLOR_FONT_ENABLED);
				font.setBold(true);
			}
			else
			{// 如果未选中
				painter.setPen(TABCOLOR_BORDER_ENABLED);
				painter.setBrush(QBrush(TABCOLOR_BACKGROUND_ENABLED));
				drawTabBorder(painter, tabRect);

				painter.setPen(TABCOLOR_FONT_ENABLED);
				font.setBold(false);
			}
		}
		else
		{// 如果是禁用状态
			painter.setPen(TABCOLOR_BORDER_DISABLED);
			painter.setBrush(QBrush(TABCOLOR_BACKGROUND_DISABLED));
			drawTabBorder(painter, tabRect);

			painter.setPen(TABCOLOR_FONT_DISABLED);
			painter.setBrush(QBrush(TABCOLOR_BACKGROUND_DISABLED));
		}
		painter.setFont(font);
		painter.drawText(tabRect, text, textOption);
		painter.restore();
	}
}

void HorizontalTabWidget::drawTabBorder(QPainter& painter, QRect tabRect)
{
	// 绘制tab边框
	QPainterPath path;
	qreal radius = 8; //设置圆角半径
	path.moveTo(tabRect.left() + radius, tabRect.top());
	path.arcTo(tabRect.left(), tabRect.top(), radius * 2, radius * 2, 90, 90);
	path.lineTo(tabRect.left(), tabRect.bottom());
	path.lineTo(tabRect.right(), tabRect.bottom());
	path.lineTo(tabRect.right(), tabRect.top() + radius);
	path.arcTo(tabRect.right() - radius * 2, tabRect.top(), radius * 2, radius * 2, 0, 90);
	path.lineTo(tabRect.left() + radius, tabRect.top());
	painter.drawPath(path);
}

void HorizontalTabWidget::drawWidgetBorder(QPainter& painter, QRect tabRect, QRect widgetRect)
{
	// 绘制tab边框
	QPainterPath path;

	path.moveTo(widgetRect.left(), widgetRect.top() + tabRect.height());
	path.lineTo(widgetRect.left(), widgetRect.bottom() + tabRect.height());
	path.lineTo(widgetRect.right(), widgetRect.bottom() + tabRect.height());
	path.lineTo(widgetRect.right(), widgetRect.top() + tabRect.height());
	path.lineTo(widgetRect.left(), widgetRect.top() + tabRect.height());

	painter.drawPath(path);
}

