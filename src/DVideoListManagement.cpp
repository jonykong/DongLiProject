#include "DVideoListManagement.h"
#include "DPublicDef.h"
#include <QJsonArray>

#ifdef _MSC_VER
#		if _MSC_VER >= 1600
#			pragma execution_character_set("utf-8")
#		endif
#endif

static DPublicDef::VideoListType getVideoListType(const QString &strType)
{
    if (strType == QString("歌曲"))
    {
        return DPublicDef::VideoListType_Song;
    }
    else if (strType == QString("舞蹈"))
    {
        return DPublicDef::VideoListType_Dance;
    }
    else if (strType == QString("健身"))
    {
        return DPublicDef::VideoListType_Fitness;
    }
    else if (strType == QString("曲艺"))
    {
        return DPublicDef::VideoListType_Quyi;
    }
    else if (strType == QString("U盘"))
    {
        return DPublicDef::VideoListType_USB;
    }
    else if (strType == QString("网络"))
    {
        return DPublicDef::VideoListType_Online;
    }

    return DPublicDef::VideoListType_Song;
}

static QString getVideoName(DPublicDef::VideoListType listType)
{
	switch (listType)
	{
	case DPublicDef::VideoListType_Song:
		return QString("歌曲");
	case DPublicDef::VideoListType_Dance:
		return QString("舞蹈");
	case DPublicDef::VideoListType_Fitness:
		return QString("健身");
	case DPublicDef::VideoListType_Quyi:
		return QString("曲艺");
	case DPublicDef::VideoListType_USB:
		return QString("U盘");
	case DPublicDef::VideoListType_Online:
		return QString("其他");
	default:
		break;
	}
	return QString("未知");
}


DVideoListManagement* DVideoListManagement::instance()
{
	static DVideoListManagement m_instance;
	return &m_instance;
}

void DVideoListManagement::AddVideoList(QJsonObject obj)
{
	if (obj.isEmpty())
	{
		return;
	}
	QString strName = obj.value("name").toString();
	DPublicDef::VideoListType eType = getVideoListType(strName);

	if (m_mVideoList.contains(eType))
	{
		m_mVideoList[eType]->AddVideoInforMation(obj);
	}
}

void DVideoListManagement::DelVideoList(DPublicDef::VideoListType eType)
{
	if (m_mVideoList.contains(eType))
	{
		DVideoList* list = m_mVideoList[eType];

		emit signalVideoListDel(list);

        delete list;
        list = nullptr;
        m_mVideoList.remove(eType);
	}
}

DVideoListManagement::DVideoListManagement(QObject *parent)
	: QObject(parent)
{

}

DVideoListManagement::~DVideoListManagement()
{
	for (int i = DPublicDef::VideoListType_Song; i < DPublicDef::VideoListType_Online; ++i)
	{
		DelVideoList((DPublicDef::VideoListType)i);
	}
}

void DVideoListManagement::InitVideoList()
{
	for (int i = DPublicDef::VideoListType_Song; i <= DPublicDef::VideoListType_Online; ++i)
	{
		DVideoList* list = new DVideoList("", (DPublicDef::VideoListType)i);
		list->m_strName = getVideoName((DPublicDef::VideoListType)i);

		m_mVideoList[DPublicDef::VideoListType(i)] = list;

		emit signalVideoListAdd(list);

		if (i == DPublicDef::VideoListType_Online)
		{
			list->InitOtherItem();
		}
	}
}

void DVideoListManagement::AddUSBFile(const QStringList &strListFile, DPublicDef::VideoListType eType )
{
    m_mVideoList[eType]->AddUSBFile(strListFile);
}

void DVideoListManagement::RemoveUSBFile()
{
	if (m_mVideoList.contains(DPublicDef::VideoListType::VideoListType_USB))
	{
		m_mVideoList[DPublicDef::VideoListType::VideoListType_USB]->RemoveUSBFile();
	}
}
