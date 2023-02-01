#include "CDataFrame.h"

CDataFrame CDataFrame::getDfByImagePath(CDataFrame df, QString sImagePath, bool bPrint)
{
	CDataFrame::index<image_path>::type& indexOfImagePath = df.m_container.get<image_path>();
	auto itL = indexOfImagePath.lower_bound(sImagePath);
	auto itU = indexOfImagePath.upper_bound(sImagePath);

	CDataFrame res;
	while (itL != itU)
	{
		if (bPrint)
		{
			itL->print();
		}
		AiResInfoContent content = itL->getContent();
		res.push(AiResInfo(content));
		++itL;
	}

	return res;
}

CDataFrame CDataFrame::getDfByClsName(CDataFrame df, QString sClsName, bool bPrint)
{
	CDataFrame::index<cls_name>::type& indexOfClsName = df.m_container.get<cls_name>();
	auto itL = indexOfClsName.lower_bound(sClsName);
	auto itU = indexOfClsName.upper_bound(sClsName);

	CDataFrame res;
	while (itL != itU)
	{
		if (bPrint)
		{
			itL->print();
		}
		AiResInfoContent content = itL->getContent();
		res.push(AiResInfo(content));
		++itL;
	}

	return res;
}

CDataFrame CDataFrame::getDfByAreaType(CDataFrame df, QString sAreaType, bool bPrint)
{
	CDataFrame::index<area_type>::type& indexOfAreaType = df.m_container.get<area_type>();
	auto itL = indexOfAreaType.lower_bound(sAreaType);
	auto itU = indexOfAreaType.upper_bound(sAreaType);

	CDataFrame res;
	while (itL != itU)
	{
		if (bPrint)
		{
			itL->print();
		}
		AiResInfoContent content = itL->getContent();
		res.push(AiResInfo(content));
		++itL;
	}

	return res;
}

CDataFrame CDataFrame::getDfByAreaType(CDataFrame df, QStringList lstAreaType, bool bPrint)
{
	CDataFrame res;
	foreach(auto sAreaType, lstAreaType)
	{
		CDataFrame::index<area_type>::type& indexOfAreaType = df.m_container.get<area_type>();
		auto itL = indexOfAreaType.lower_bound(sAreaType);
		auto itU = indexOfAreaType.upper_bound(sAreaType);

		while (itL != itU)
		{
			if (bPrint)
			{
				itL->print();
			}
			AiResInfoContent content = itL->getContent();
			res.push(AiResInfo(content));
			++itL;
		}
	}
	return res;
}

CDataFrame CDataFrame::sortDfByClsName(CDataFrame df, bool bPrint)
{
	CDataFrame::index<cls_name>::type& indexOfClsName = df.m_container.get<cls_name>();
	auto it = indexOfClsName.begin();

	CDataFrame res;
	while (it != indexOfClsName.end())
	{
		if (bPrint)
		{
			it->print();
		}
		AiResInfoContent content = it->getContent();
		res.push(AiResInfo(content));
		++it;
	}

	return res;
}

CDataFrame CDataFrame::sortDfByContent(CDataFrame df, bool bPrint)
{
	CDataFrame::nth_index<1>::type& indexOfId = df.m_container.get<1>();
	auto it = indexOfId.begin();

	CDataFrame res;
	while (it != indexOfId.end())
	{
		if (bPrint)
		{
			it->print();
		}
		AiResInfoContent content = it->getContent();
		res.push(AiResInfo(content));
		++it;
	}

	return res;
}

CDataFrame CDataFrame::filterDfByThresh_Conf(CDataFrame df, double dConfThresh = .0, bool bPrint)
{
	CDataFrame::index<cls_conf>::type& indexOfConf = df.m_container.get<cls_conf>();
	auto itL_conf = indexOfConf.lower_bound(dConfThresh);
	auto itU_conf = indexOfConf.upper_bound(1.0);

	CDataFrame res;
	while (itL_conf != itU_conf)
	{
		if (bPrint)
		{
			itL_conf->print();
		}
		AiResInfoContent content = itL_conf->getContent();
		res.push(AiResInfo(content));
		++itL_conf;
	}

	return res;
}

CDataFrame CDataFrame::filterDfByThresh_AreaSize(CDataFrame df, int nThreshAreaSize = 0, bool bUpperBound, bool bPrint)
{
	CDataFrame::index<area_size>::type& indexOfAreaSize = df.m_container.get<area_size>();
	auto itL_conf = indexOfAreaSize.lower_bound(nThreshAreaSize);
	auto itU_conf = indexOfAreaSize.upper_bound(300 * 300);

	CDataFrame res;
	while (itL_conf != itU_conf)
	{
		if (bPrint)
		{
			itL_conf->print();
		}
		AiResInfoContent content = itL_conf->getContent();
		res.push(AiResInfo(content));
		++itL_conf;
	}

	return res;
}

CDataFrame CDataFrame::filterDfByThresh_AreaRatio(CDataFrame df, double dPadRatio = .0, bool bUpperBound, bool bPrint)
{
	CDataFrame res;
	CDataFrame::index<area_ratio>::type& indexOfAreaRatio = df.m_container.get<area_ratio>();
	if (!bUpperBound)
	{
		auto itL_conf = indexOfAreaRatio.lower_bound(dPadRatio);
		auto itU_conf = indexOfAreaRatio.upper_bound(1);

		while (itL_conf != itU_conf)
		{
			if (bPrint)
			{
				itL_conf->print();
			}
			AiResInfoContent content = itL_conf->getContent();
			res.push(AiResInfo(content));
			++itL_conf;
		}
	}
	else
	{
		auto itL_conf = indexOfAreaRatio.upper_bound(dPadRatio);
		auto itU_conf = indexOfAreaRatio.lower_bound(0.0);

		while (itU_conf != itL_conf)
		{
			if (bPrint)
			{
				itU_conf->print();
			}
			AiResInfoContent content = itU_conf->getContent();
			res.push(AiResInfo(content));
			--itU_conf;
		}
	}

	return res;
}

CDataFrame CDataFrame::filterDfByThresh_Color(CDataFrame df, int nThreshColor, bool bUpperBound, bool bPrint)
{
	CDataFrame res;
	CDataFrame::index<color>::type& indexOfAreaRatio = df.m_container.get<color>();
	if (!bUpperBound)
	{
		auto itL_conf = indexOfAreaRatio.lower_bound(nThreshColor);
		auto itU_conf = indexOfAreaRatio.upper_bound(1);

		while (itL_conf != itU_conf)
		{
			if (bPrint)
			{
				itL_conf->print();
			}
			AiResInfoContent content = itL_conf->getContent();
			res.push(AiResInfo(content));
			++itL_conf;
		}
	}
	else
	{
		auto itL_conf = indexOfAreaRatio.upper_bound(nThreshColor);
		auto itU_conf = indexOfAreaRatio.lower_bound(0.0);

		while (itU_conf != itL_conf)
		{
			if (bPrint)
			{
				itU_conf->print();
			}
			AiResInfoContent content = itU_conf->getContent();
			res.push(AiResInfo(content));
			--itU_conf;
		}
	}

	return res;
}

void CDataFrame::printContent(AiResInfoContent content)
{
	QString res = QString(
		"id: %1, model: %2, image_path: %3, cls_name: %4, cls_conf: %5, "
		"area_type: %6, area_size: %7, pos_1: (%8, %9), pos_2:(%10, %11)"
	).arg(content.id).arg(content.model).arg(content.image_path)
		.arg(content.cls_name).arg(content.cls_conf)
		.arg(content.area_type).arg(content.area_size)
		.arg(content.X1).arg(content.Y1).arg(content.X2).arg(content.Y2);
	qDebug() << res;
}

int CDataFrame::calcuAreaSizeTotal(CDataFrame df, QString sImagePath, QString sClsName, bool bPrint)
{
	auto df_filtered = getDfByImagePath(df, sImagePath);
	df_filtered = getDfByClsName(df_filtered, sClsName);
	int res = 0;

	CDataFrame::index<area_size>::type& indexOfAreaSize = df_filtered.get<area_size>();
	auto it = indexOfAreaSize.begin();
	while (it != indexOfAreaSize.end())
	{
		res += it->getContent().area_size;
		++it;
	}

	if (bPrint)
	{
		qDebug() << "Total area size of image " << sImagePath << " is " << res;
	}
	return res;
}

template <typename T>
CDataFrame CDataFrame::filterDfByTag(CDataFrame df, const T& t, QVariant Thresh, bool bUpperBound, bool bPrint)
{
	CDataFrame res;
	auto index = df.m_container.get<t>();

	double dThresh_main = Thresh.toDouble();
	double dThresh_sub = Thresh.toDouble();
	if (typeid(t) == typeid(cls_conf) || typeid(t) == typeid(area_ratio))
	{
		dThresh_sub = !bUpperBound ? 1 : 0;
	}
	else if (typeid(t) == typeid(area_size) || typeid(t) == typeid(color))
	{
		dThresh_sub = !bUpperBound ? 90000.0 : 0.0;
	}

	if (!bUpperBound)
	{
		double dThresh_lower = dThresh_main;
		double dThresh_upper = dThresh_sub;

		auto itL_conf = index.lower_bound(dThresh_lower);
		auto itU_conf = index.upper_bound(dThresh_upper);

		while (itL_conf != itU_conf)
		{
			if (bPrint)
			{
				itL_conf->print();
			}
			AiResInfoContent content = itL_conf->getContent();
			res.push(AiResInfo(content));
			++itL_conf;
		}
	}

	else
	{
		double dThresh_lower = dThresh_sub;
		double dThresh_upper = dThresh_main;

		auto itL_conf = index.lower_bound(dThresh_lower);
		auto itU_conf = index.upper_bound(dThresh_upper);

		while (itU_conf != itL_conf)
		{
			if (bPrint)
			{
				itU_conf->print();
			}
			AiResInfoContent content = itU_conf->getContent();
			res.push(AiResInfo(content));
			--itU_conf;
		}
	}

	return res;
}