#pragma once

#include <QObject>
#include "DPublicDef.h"
#include <QMap>
#include <QJsonObject>
#include "DVideoInformation.h"
#include <QStringList>

class DVideoList : public QObject
{
	Q_OBJECT
public:
	explicit DVideoList(const QString strID, DPublicDef::VideoListType eType, QObject *parent = nullptr);
	~DVideoList();

    void ClearVideoInfo();
	void InitOtherItem();

    void AddUSBFile(const QStringList &strFileList);
	void RemoveUSBFile();

public:
	void AddVideoInforMation(QJsonObject obj);
	void DelVideoInforMation(const QString& strID);

signals:
	void signalVideoAdd(DPublicDef::VideoListType eType, DVideoInformation* info);
	void signalVideoDel(DPublicDef::VideoListType eType, DVideoInformation* info);

public:
	QString											m_strID;			// ID 唯一标识符
	QString										    m_strName;			// 名称
	DPublicDef::VideoListType					    m_eType;			// 类型
	QMap<QString, DVideoInformation*>				m_mVideoInfo;		// 视频列表
};