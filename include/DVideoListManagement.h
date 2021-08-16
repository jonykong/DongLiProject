#pragma once

#include "DVideoList.h"
#include <QMap>
#include <QJsonObject>

class DVideoListManagement : public QObject
{
	Q_OBJECT
public:
	static DVideoListManagement* instance();

public:
	void AddVideoList(QJsonObject obj);
	void DelVideoList(DPublicDef::VideoListType eType);
	void InitVideoList();

    void AddUSBFile(const QStringList &strListFile, DPublicDef::VideoListType eType = DPublicDef::VideoListType_USB);
	void RemoveUSBFile();

protected:
	explicit DVideoListManagement(QObject *parent = nullptr);
	~DVideoListManagement();

signals:
    void signalVideoListAdd(DVideoList* info);
    void signalVideoListDel(DVideoList* info);

private:
	QMap<DPublicDef::VideoListType, DVideoList*>				m_mVideoList;		// 视频列表
};

inline DVideoListManagement *videoManagement()
{
    return DVideoListManagement::instance();
}