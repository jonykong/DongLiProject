#ifndef DPLATFORM_H
#define DPLATFORM_H

#include <QObject>
#include <QMap>
#include "DPublicDef.h"
#include "DVideoInformation.h"
#include <QSettings>
#include <QWebSocket>
#include <QThread>
#include <QStringList>

enum MaterialType
{
    MaterialType_error = -1,
    MaterialType_folder = 0,
    MaterialType_video,
    MaterialType_picture,
    MaterialType_audio,
};

class QSearchMeidaFile : public QThread
{
    Q_OBJECT
public:
    QSearchMeidaFile(QObject *parent = nullptr);
    ~QSearchMeidaFile();

public:
    void start(const QString &strDir);
    void stop();
    void run();

signals:
    void signalUpdateFile(const QString &strDir, const QStringList &strFileList);
    void signalUpdate();

public:
    QString       m_strDir;
    bool          m_bRunning;
    QStringList   m_strFileList;

};


/*
* 业务逻辑层，管理数据，和请求
*/
class DDownLoadThread;
class Player;
class DPlatform :public QObject
{
    Q_OBJECT
public:
    static DPlatform* instance();
	// 初始化列表
	void InitVideoList();
    void DownLoadFile(const QString& strId);
    void CheckUsbDiskFile(const QString& strPath);
	void RemoveUSBFile();
    QString getSenderId() const ;
    QString getReceiverId() const;
	QString getURL() const; 
	QString getVideoUrl() const;

	Player* getPlayer();

public:
	void sendMessage(const QString& strMsg);

signals:
	void signalVideoAdd();
	void signalVideoDel();

    void signalProgressUpdate(const QString& strId, int value);
    void signalDownLoadFinished(const QString& strId, const QString &strPath);
    void signalDownLoadError(const QString& strId, const QString &errorMsg);

protected slots:
    void onDownLoadFinished(const QString& strId, const QString &strPath);
	void onConnected();
	void onDisconnected();
	void onTextMessageReceived(const QString &message);
	void onBinaryMessageReceived(const QByteArray &message);
    void onUpdateFile(const QString &strDir, const QStringList &strFileList);

protected:
	void init();
	void addLocalVideo();
	void addLocalVideo(QJsonObject obj);
	QString readFile();
    QStringList searchMeidaFile(QString strPath);


private:
    DPlatform(QObject *parent = nullptr);
	~DPlatform();

private:
	QString		                        m_strWriteDir;
	QSettings*                          m_pSettings;
    DDownLoadThread*                    m_pDownLoad;
    QString                             m_strDownLoadPath;
	QMap<DPublicDef::VideoListType, QList<DVideoInformation> > m_mVideoInformation;
	QWebSocket*						    m_pWebSocket;
    QSearchMeidaFile*                   m_mediaFile;
    QMap<QString, QStringList>          m_usbFile;
    QString                             m_strSenderId;
    QString                             m_strReiverId;;
	QString								m_strUrl;
	QString								m_strVideoUrl;
	Player*							    m_player;
};

inline DPlatform* platform()
{
	return DPlatform::instance();
}

#endif // DPLATFORM_H
