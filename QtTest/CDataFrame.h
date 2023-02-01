#pragma once
#pragma execution_character_set("utf-8")

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/hashed_index.hpp>

#include <QDebug>
#include <QVector>
#include <QWidget>

#include <algorithm>
#include <numeric>

#define MIN_VALUE 1e-8
#define IS_DOUBLE_ZERO(d)  (abs(d) < MIN_VALUE)

using boost::multi_index_container;
using namespace boost;
using namespace boost::multi_index;
using namespace std;

struct AiResInfoContent
{
	unsigned int id = -1; // 图片编号
	QString image_path = ""; // 图片路径
	QString model = "false"; // 模型名称(cls还是ins && false 代表假点)
	QString cls_name = "false"; // 缺陷类型名
	double cls_conf = 0.00; // 缺陷置信度
	QString area_type = "false"; // 缺陷区域类型（eg: 普通 or vcut or hanpan）
	int area_size = -1; // 缺陷面积大小
	double area_ratio = 0.0; // 缺陷区域的特殊参数（eg: pad_ratio or vcut_ratio）
	int color = -1; // 颜色
	int X1 = -1; // 缺陷目标位置参数(左上, x)
	int X2 = -1; // 缺陷目标位置参数(左上, y)
	int Y1 = -1; // 缺陷目标位置参数(右下, x)
	int Y2 = -1; // 缺陷目标位置参数(右下, y)

	/**
	 * \brief 插入一些待解析的值
	 */
	void insert(QString key, QVariant value)
	{
		if (key == "id")
		{
			id = value.toInt();
		}
		else if (key == "image_path")
		{
			image_path = value.toString();
		}
		else if (key == "model")
		{
			model = value.toString();
		}
		else if (key == "cls_name")
		{
			cls_name = value.toString();
		}
		else if (key == "cls_conf")
		{
			cls_conf = value.toDouble();
		}
		else if (key == "area_type")
		{
			area_type = value.toString();
		}
		else if (key == "area_size" || key == "area")
		{
			area_size = value.toInt();
		}
		else if (key == "area_ratio" || key.contains("ratio"))
		{
			area_ratio = value.toDouble();
		}
		else if (key == "color" || key == "hsv" || key.contains("color"))
		{
			color = key.toInt();
		}
		else if (key == "X1" || key == "x1")
		{
			X1 = value.toInt();
		}
		else if (key == "Y1" || key == "y1")
		{
			Y1 = value.toInt();
		}
		else if (key == "X2" || key == "x2")
		{
			X2 = value.toInt();
		}
		else if (key == "Y2" || key == "y2")
		{
			Y2 = value.toInt();
		}
	}

	bool isValid()
	{
		if (!image_path.isEmpty())
		{
			return true;
		}

		return false;
	}
};

class AiResInfo
{
public:
	QString id; // 内容组合编码

	QString image_path = "";; // 图片路径
	QString model = "false";; // 模型名称(cls还是ins)
	QString cls_name = "false";; // 缺陷类型名
	double cls_conf = 0.00; // 缺陷置信度
	QString area_type = "false"; // 缺陷区域类型（eg: 普通 or VCUT-0）
	int area_size = -1; // 缺陷面积大小
	double area_ratio = -1; // 焊盘面积比
	int color = -1; // 颜色
	int X1 = -1; // 缺陷目标位置参数(左上, x)
	int X2 = -1; // 缺陷目标位置参数(左上, y)
	int Y1 = -1; // 缺陷目标位置参数(右下, x)
	int Y2 = -1; // 缺陷目标位置参数(右下, y)

	size_t hash; // 该记录的字符串哈希值

	AiResInfo(QString image_path, QString model,
		QString cls_name, double cls_conf, QString area_type, int area_size,
		double area_ratio, int color, int X1, int X2, int Y1, int Y2) :
		image_path(image_path), model(model),
		cls_name(cls_name), cls_conf(cls_conf), area_type(area_type), area_size(area_size),
		area_ratio(area_ratio), color(color), X1(X1), X2(X2), Y1(Y1), Y2(Y2)
	{
		if (IS_DOUBLE_ZERO(area_ratio))
			area_ratio = -0.1;
		identity();
	}

	AiResInfo(AiResInfoContent content) :
		image_path(content.image_path), model(content.model),
		cls_name(content.cls_name), cls_conf(content.cls_conf),
		area_type(content.area_type), area_size(content.area_size),
		area_ratio(content.area_ratio), color(content.color), X1(content.X1), X2(content.X2), Y1(content.Y1),
		Y2(content.Y2)
	{
		if (IS_DOUBLE_ZERO(area_ratio))
			area_ratio = -0.1;
		identity();
	}

	AiResInfoContent getContent() const
	{
		AiResInfoContent res;
		res.image_path = image_path;
		res.model = model;
		res.cls_name = cls_name;
		res.cls_conf = cls_conf;
		res.area_type = area_type;
		res.area_size = area_size;
		res.area_ratio = area_ratio;
		res.X1 = X1;
		res.X2 = X2;
		res.Y1 = Y1;
		res.Y2 = Y2;

		return res;
	}

	void print() const
	{
		QString res = QString(
			"model: %1, image_path: %2, cls_name: %3, cls_conf: %4, "
			"area_type: %5, area_size: %6, pos_1: (%7, %8), pos_2:(%9, %10), area_ratio: %11"
		).arg(model).arg(image_path).arg(cls_name).arg(cls_conf)
			.arg(area_type).arg(area_size).arg(X1).arg(Y1).arg(X2).arg(Y2).arg(area_ratio);
		qDebug() << res;
	}

	bool operator<(const AiResInfo& info) const
	{
		return image_path < info.image_path;
	}

	void identity()
	{
		QString key = QString(
			"%1#%2#%3#%4#%5#%6#%7#%8#%9#%10#%11"
		).arg(model).arg(image_path).arg(cls_name).arg(cls_conf)
			.arg(area_type).arg(area_size).arg(area_ratio).arg(X1).arg(Y1).arg(X2).arg(Y2);

		id = key;
	}
};

struct id
{
};

struct image_path
{
};

struct model
{
};

struct cls_name
{
};

struct cls_conf
{
};

struct area_type
{
};

struct area_size
{
};

struct area_ratio
{
};

struct color
{
};

struct X1
{
};

struct X2
{
};

struct Y1
{
};

struct Y2
{
};

using MyContainer = multi_index_container <
	AiResInfo,
	indexed_by <
	ordered_non_unique<
	boost::multi_index::identity<AiResInfo>>,
	ordered_non_unique<
	tag<id>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, QString, AiResInfo::id)>,
	ordered_non_unique<
	tag<image_path>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, QString, image_path)>,
	ordered_non_unique<
	tag<model>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, QString, model)>,
	ordered_non_unique<
	tag<cls_name>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, QString, cls_name)>,
	ordered_non_unique<
	tag<cls_conf>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, double, cls_conf)>,
	ordered_non_unique<
	tag<area_type>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, QString, area_type)>,
	ordered_non_unique<
	tag<area_size>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, int, area_size)>,
	ordered_non_unique<
	tag<area_ratio>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, double, area_ratio)>,
	ordered_non_unique<
	tag<color>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, int, color)>,
	ordered_non_unique<
	tag<X1>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, int, X1)>,
	ordered_non_unique<
	tag<X2>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, int, X2)>,
	ordered_non_unique<
	tag<Y1>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, int, Y1)>,
	ordered_non_unique<
	tag<Y2>,
	BOOST_MULTI_INDEX_MEMBER(AiResInfo, int, Y2)>
	>
	> ;

class CDataFrame : public MyContainer
{
public:
	void push(QString image_path, QString model,
		QString cls_name, double cls_conf, QString area_type, int area_size,
		double area_ratio, int color, int X1, int X2, int Y1, int Y2)
	{
		m_container.insert(
			AiResInfo(
				image_path, model, cls_name, cls_conf,
				area_type, area_size, area_ratio,
				color, X1, X2, Y1, Y2
			));
	}

	void push(AiResInfoContent content)
	{
		m_container.insert(AiResInfo(content));
	}

	void push(AiResInfo info)
	{
		m_container.insert(info);
	}

	void head(int rows = 5)
	{
		auto& indexOfId = m_container.get<1>();
		int i = 0;
		for (auto it = indexOfId.begin(); it != indexOfId.end(); it++)
		{
			if (i >= rows)
			{
				break;
			}
			it->print();
			i++;
		}
	}

	CDataFrame append(CDataFrame df, bool bInplace = false)
	{
		CDataFrame res;
		res.m_container = m_container;

		auto& indexOfId = df.m_container.get<1>();
		for (auto it = indexOfId.begin(); it != indexOfId.end(); it++)
		{
			res.push(it->getContent());
		}
		if (bInplace)
		{
			m_container = res.m_container;
		}

		return res;
	}

	CDataFrame unique(bool bPrint = false, bool bInplace = true)
	{
		auto& indexOfId = m_container.get<id>();

		CDataFrame res;
		for (auto it = indexOfId.begin(); it != indexOfId.end();)
		{
			if (bPrint)
			{
				it->print();
			}
			res.push(it->getContent());
			it = indexOfId.upper_bound(it->id);
		}

		if (bInplace)
		{
			m_container = res.m_container;
		}
		return res;
	}

	MyContainer m_container;

	//static AiResInfoContent getContentByIndex(CDataFrame df, int index, bool bPrint = false);
	//static AiResInfoContent getContentByIndex_first(CDataFrame df, bool bPrint = false);
	//static AiResInfoContent getContentByIndex_last(CDataFrame df, bool bPrint = false);

	static CDataFrame getDfByImagePath(CDataFrame df, QString sImagePath, bool bPrint = false);
	static CDataFrame getDfByClsName(CDataFrame df, QString sClsName, bool bPrint = false);

	static CDataFrame getDfByAreaType(CDataFrame df, QString sAreaType, bool bPrint = false);
	static CDataFrame getDfByAreaType(CDataFrame df, QStringList lstAreaType, bool bPrint = false);

	static CDataFrame sortDfByClsName(CDataFrame df, bool bPrint = false);
	static CDataFrame sortDfByContent(CDataFrame df, bool bPrint = false);

	static CDataFrame filterDfByThresh_Conf(CDataFrame df, double dConfThresh, bool bPrint = false);
	static CDataFrame filterDfByThresh_AreaSize(CDataFrame df, int nThreshAreaSize, bool bUpperBound = false,
		bool bPrint = false);
	static CDataFrame filterDfByThresh_AreaRatio(CDataFrame df, double dPadRatio, bool bUpperBound = false,
		bool bPrint = false);
	static CDataFrame filterDfByThresh_Color(CDataFrame df, int nThreshColor, bool bUpperBound = false,
		bool bPrint = false);
	template <typename T>
	static CDataFrame filterDfByTag(CDataFrame df, const T& t, QVariant Thresh, bool bUpperBound = false,
		bool bPrint = false);

	static void printContent(AiResInfoContent content);
	static int calcuAreaSizeTotal(CDataFrame df, QString sImagePath, QString sClsName, bool bPrint = false);
};


