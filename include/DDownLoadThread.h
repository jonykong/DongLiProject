#pragma once
#include <QThread>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QVariant>

enum REQUESTOPERATE
{
	requestStart = 0,
};
Q_DECLARE_METATYPE(REQUESTOPERATE);

class DDownLoadThread : public QObject
{
	Q_OBJECT
public:
	DDownLoadThread(QObject *parent = nullptr);
	~DDownLoadThread();

    void setDownLoadPath(const QString & strPath);
	void startDown(const QString &strId, const QString& qsPath);
    void stopDown();

signals:
	void sigProgressUpdate(const QString& strId,int value);
    void sigDownLoadFinished(const QString& strId, const QString &strPath);
	void sigDownLoadError(const QString& strId, const QString &errorMsg);

	void requestStart();
    void requestStop();

protected slots:
	void onRequestStart();
    void onRequestStop();
	void onDownLoadFinished();
	void onReadyRead();
	void onError(QNetworkReply::NetworkError error);
	void onDownLoadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
	void init();
	void initDownLoadFile(QUrl strUrl);
	void downLoadFile(QUrl strUrl);
	bool createUpdateDir(const QString &strDir);
	bool createFileInDir();
	QString createMultDir(const QString &strPath);
	void removeDir(const QString &strDir);
    void update();

protected:
    QNetworkAccessManager			*m_pNetManager;			    // 网络对象管理
    QNetworkReply					*m_pReplay;				    // 请求回执对象
    QFile							*m_File;				    // 文件对象
    QThread							 m_Thread;				    // 线程
	QString							 m_Path;					// 下载目录
	int								 m_Progress;                // 进度
    QString                          m_strId;                   // 文件名
    QString                          m_strUrl;                  // URL
    QString                          m_strFilePath;             // 下载的目录
    bool                             m_bRunning;                // 是否在运行中
    QList<QString>                   m_strIdList;               // 下载列表
}; 
