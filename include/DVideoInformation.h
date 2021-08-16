#pragma once

#include <QObject>
#include <QPixmap>
#include "DPublicDef.h"

class DVideoInformation : public QObject
{
	Q_OBJECT
public:
	explicit DVideoInformation(QObject* parent = nullptr);
	~DVideoInformation();

	// 设置视频路径
	void setVideoFilePath(const QString &path);
	QString getVideoFilePath() const;

	// 设置缩略图路径
	void setPixmapFilePath(const QString &path);
	QString getPixmapFilePath() const;

    void setVideoId(const QString & strId);

	// 获取缩略图
	QPixmap getPixmap() const;

signals:
	void signalVideoPathChanged(const QString &path);
	void signalPixmapPathChanged(const QString &path);

protected slots:
    void onDownLoadFinished(const QString& strId, const QString &strPath);

	// 创建需要初始化的
public:
	DPublicDef::VideoListType			m_eType;
	QString								m_strID;				// 唯一标识符号
	QString								m_strVideoUrl;			// 网络地址或链接
	QString								m_strDescribe;			// 描述
	QString								m_strPixmapUrl;			// 缩略图网络路径
	QString								m_strName;				// 名称
	DPublicDef::VideoListItemType       m_eItemType;

	// 下载后才能得到的
	QString								m_strVideoFilePath;		// 本地视频路径
	QPixmap								m_pixmap;				// 缩略图
	QString								m_strPixmapFilePath;	// 本地缩略图路径
};