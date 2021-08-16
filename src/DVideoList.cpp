#include "DVideoList.h"
#include <QJsonArray>
#include "DPublicDef.h"
#include <QFileInfo>
#include <QApplication>

#ifdef _MSC_VER
#		if _MSC_VER >= 1600
#			pragma execution_character_set("utf-8")
#		endif
#endif


static QString getVideoItemName(DPublicDef::VideoListItemType itemType)
{
	switch (itemType)
	{
	case DPublicDef::VideoListType_Tencent:
		return QString("腾讯视频");
	case DPublicDef::VideoListType_AQY:
		return QString("爱奇艺");
	case DPublicDef::VideoListType_YouKu:
		return QString("优酷");
	case DPublicDef::VideoListType_Baidu:
		return QString("百度视频");
	case DPublicDef::VideoListType_Mangguo:
		return QString("芒果TV");
	case DPublicDef::VideoListType_BliBli:
		return QString("哔哩哔哩");
	default:
		break;
	}
	return QString("未知");
}

DVideoList::DVideoList(const QString strID, DPublicDef::VideoListType eType, QObject *parent /*= nullptr*/)
	: QObject(parent)
	, m_eType(eType)
	, m_strID(strID)
{

}

DVideoList::~DVideoList()
{
    ClearVideoInfo();
}

void DVideoList::ClearVideoInfo()
{
    while (!m_mVideoInfo.empty())
    {
        QMap<QString, DVideoInformation*>::Iterator iter = m_mVideoInfo.begin();

        DVideoInformation* info = iter.value();
        emit signalVideoDel(info->m_eType, info);

        m_mVideoInfo.remove(info->m_strID);

        delete info;
        info = nullptr;
    }
}

void DVideoList::InitOtherItem()
{
	for (int i = DPublicDef::VideoListType_Tencent; i <= DPublicDef::VideoListType_BliBli; ++i)
	{
		DVideoInformation* info = new DVideoInformation(this);
		info->m_strName = getVideoItemName(DPublicDef::VideoListItemType(i));;
		info->m_eItemType = DPublicDef::VideoListItemType(i);
		m_mVideoInfo.insert(info->m_strID, info);

		emit signalVideoAdd(m_eType, info);
	}
}

void DVideoList::AddUSBFile(const QStringList &strFileList)
{
    for (int i = 0; i < strFileList.size(); ++i)
    {
        QFileInfo fileInfo(strFileList.at(i));

        DVideoInformation* info = new DVideoInformation(this);
		info->m_eType = DPublicDef::VideoListType_USB;
        info->m_strName = fileInfo.fileName();
        info->m_strVideoFilePath = strFileList.at(i);
		m_mVideoInfo.insert(info->m_strID, info);
        emit signalVideoAdd(m_eType, info);
        QApplication::processEvents();
    }
}

void DVideoList::RemoveUSBFile()
{
	for (QMap<QString, DVideoInformation*>::iterator iterator = m_mVideoInfo.begin(); !m_mVideoInfo.empty(); )
	{
		QString strID = iterator.key();
		DVideoInformation* info = iterator.value();

		emit signalVideoDel(info->m_eType, info);

		iterator = m_mVideoInfo.erase(iterator);

		delete info;
		info = nullptr;
	}
}

void DVideoList::AddVideoInforMation(QJsonObject obj)
{
    if (obj.isEmpty())
    {
        return;
    }

    QJsonArray videoArry = obj.value("videoWithTypeList").toArray();
    for (int i = 0; i < videoArry.size(); ++i)
    {
        QJsonObject videoObj = videoArry.at(i).toObject();
        if (!videoObj.isEmpty())
        {
            QString strName = videoObj.value("name").toString();
            QString strId = videoObj.value("id").toString();

            DVideoInformation* info = new DVideoInformation(this);
            info->setVideoId(strId);
            info->m_strName = strName;
			m_mVideoInfo.insert(info->m_strID, info);
            emit signalVideoAdd(m_eType, info);

        }
    }
}

void DVideoList::DelVideoInforMation(const QString& strID)
{
    if (m_mVideoInfo.contains(strID))
    {
        DVideoInformation* info = m_mVideoInfo[strID];
        emit signalVideoDel(info->m_eType, info);

        m_mVideoInfo.remove(info->m_strID);

        delete info;
        info = nullptr;
    }
}
