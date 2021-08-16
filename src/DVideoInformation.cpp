#include "DVideoInformation.h"
#include <QFileInfo>
#include "DPlatform.h"
#include <QHostInfo>
#include <objbase.h>

const char* newGUID()
{
	static char buf[64] = { 0 };
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buf, sizeof(buf)
			, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
			, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
			, guid.Data4[6], guid.Data4[7]
		);
	}
	return buf;
}

QString newUniquenessID()
{
	QString strMac = QHostInfo::localHostName();
	QString strGuiID = newGUID();
	QString strTime = QTime::currentTime().toString("hh:mm:ss.zzz");
	QString strUniquenessID =  strTime + "_" + strMac + "_" + strGuiID;

	return strUniquenessID;
}

DVideoInformation::DVideoInformation(QObject* parent /*= nullptr*/)
	: QObject(parent)
	, m_eItemType(DPublicDef::VideoListType_UnKonw)
{
    connect(platform(), &DPlatform::signalDownLoadFinished, this, &DVideoInformation::onDownLoadFinished);

	m_strID = newUniquenessID();
}

DVideoInformation::~DVideoInformation()
{

}

void DVideoInformation::setVideoFilePath(const QString &path)
{
	if (m_strVideoFilePath != path)
	{
		m_strVideoFilePath = path;
		emit signalVideoPathChanged(m_strVideoFilePath);
	}
}

QString DVideoInformation::getVideoFilePath() const
{
	return m_strVideoFilePath;
}

void DVideoInformation::setPixmapFilePath(const QString &path)
{
	if (m_strPixmapFilePath != path)
	{
		m_strPixmapFilePath = path;

		if (QFileInfo(m_strPixmapFilePath).exists())
		{
			m_pixmap = QPixmap(m_strPixmapFilePath);
		}
		emit signalPixmapPathChanged(path);
	}
}

QString DVideoInformation::getPixmapFilePath() const
{
	return m_strPixmapFilePath;
}

void DVideoInformation::setVideoId(const QString & strId)
{
    if (m_strID != strId)
    {
        m_strID = strId;
        platform()->DownLoadFile(strId);
    }
}

QPixmap DVideoInformation::getPixmap() const
{
	return m_pixmap;
}

void DVideoInformation::onDownLoadFinished(const QString& strId, const QString &strPath)
{
    if (strId != m_strID)
    {
        return;
    }
}
