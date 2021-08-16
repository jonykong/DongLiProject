#include "DDownLoadThread.h"
#include <QDir>
#include "Dwmapi.h"
#include <QApplication>
#include <QProcess>
#include <QEventLoop>
#include <QStandardPaths>

DDownLoadThread::DDownLoadThread(QObject *parent)
    : QObject(parent)
    , m_bRunning(false)
{
	init();
	connect(this, &DDownLoadThread::requestStart, this, &DDownLoadThread::onRequestStart);
    connect(this, &DDownLoadThread::requestStop, this, &DDownLoadThread::onRequestStop);
	moveToThread(&m_Thread);
    m_Thread.start();

}

DDownLoadThread::~DDownLoadThread()
{
    m_Thread.quit();
    m_Thread.wait(3000);
}

void DDownLoadThread::startDown(const QString &strId, const QString& url)
{
    if (!m_bRunning)
    {
        m_strId = strId;
        m_strUrl = url;
        emit requestStart();
    }
    else
    {
        m_strIdList.append(strId);
    }
}

void DDownLoadThread::stopDown()
{
     emit requestStop();
}

void DDownLoadThread::onRequestStart()
{
    m_bRunning = true;
    if (!m_pReplay || !m_pReplay->isRunning())
    {
        QString url = m_strUrl + m_strId + QString(".mp4");
        initDownLoadFile(QUrl(QString(url)));
    }
}

void DDownLoadThread::onRequestStop()
{
    if(m_pReplay->isRunning())
    {
        disconnect(m_pReplay, 0, this , 0);
        m_pReplay->deleteLater();
        m_pReplay = nullptr;

        m_File->flush();
        m_File->close();
        m_bRunning = false;
        emit sigDownLoadError(m_strId, tr("网络超时"));
    }
}

void DDownLoadThread::onDownLoadFinished()
{
	disconnect(m_pReplay, 0, this, 0);
	m_File->flush();
    m_File->close();
	if (m_pReplay->error() != QNetworkReply::NoError)
	{
		QString errorMsg = m_pReplay->errorString();
        m_File->remove();
        m_File->deleteLater();
        m_File = nullptr;
        m_pReplay->deleteLater();
        m_pReplay = nullptr;
		emit sigDownLoadError(m_strId, errorMsg);
        m_bRunning = false;
		return;

	}
	else
    {
        m_bRunning = false;
        emit sigDownLoadFinished(m_strId, m_strFilePath);
	}
    update();
}

void DDownLoadThread::onReadyRead()
{
	if (m_File)
	{
        m_File->write(m_pReplay->readAll());
		emit sigProgressUpdate(m_strId ,m_Progress);
	}
}

void DDownLoadThread::onError(QNetworkReply::NetworkError error)
{
	disconnect(m_pReplay, 0, this, 0);
	emit sigDownLoadError(m_strId, m_pReplay->errorString());
	removeDir(m_Path);
    m_bRunning = false;
}

void DDownLoadThread::onDownLoadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (bytesTotal > 0)
	{
		m_Progress = bytesReceived * 100 / bytesTotal;
		emit sigProgressUpdate(m_strId, m_Progress);
	}
}

void DDownLoadThread::init()
{
    m_pNetManager = new QNetworkAccessManager(this);
	m_pReplay = nullptr;
	m_File = nullptr;
	m_Progress = 0;
}

void DDownLoadThread::setDownLoadPath(const QString& qsPath)
{
	if (m_Path != qsPath)
	{
        m_Path = qsPath;
		QDir dir(qsPath);
		if (!dir.exists())
		{
			dir.mkpath(m_Path);
		}
	}
}

void DDownLoadThread::initDownLoadFile(QUrl strUrl)
{
	QFileInfo fileInfo(strUrl.path());
	QString fileName = fileInfo.fileName();
	if (fileName.isEmpty())
	{
		return;
	}
    m_strFilePath = m_Path + QString("/") + fileName;
	if (QFile::exists(m_strFilePath))
	{
		//如果存在删除
		QFile::remove(m_strFilePath);
	}

	m_File = new QFile(m_strFilePath);
	if (!m_File->open(QIODevice::WriteOnly))
	{
		//打开失败
		m_File->deleteLater();
        m_File = NULL;
		return;
	}
	downLoadFile(strUrl);
}

void DDownLoadThread::downLoadFile(QUrl strUrl)
{
    if (m_pReplay)
    {
        delete m_pReplay;
        m_pReplay = nullptr;
    }
    QNetworkRequest request;
// 	QSslConfiguration m_sslConfig = QSslConfiguration::defaultConfiguration();
// 	m_sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
// 	m_sslConfig.setProtocol(QSsl::TlsV1SslV3);
// 	request.setSslConfiguration(m_sslConfig);
	request.setUrl(strUrl);
    m_Progress = 0;
    m_pReplay = m_pNetManager->get(request);

    connect(m_pReplay, &QNetworkReply::finished, this, &DDownLoadThread::onDownLoadFinished);
    connect(m_pReplay, &QNetworkReply::readyRead, this, &DDownLoadThread::onReadyRead);
    connect(m_pReplay, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &DDownLoadThread::onError);
    connect(m_pReplay, &QNetworkReply::downloadProgress, this, &DDownLoadThread::onDownLoadProgress);
}

bool DDownLoadThread::createUpdateDir(const QString &strDir)
{
	QDir dir;
	if (dir.mkpath(strDir))//先创建下载根目录文件夹
	{
		bool b = createFileInDir();//创建真正的子目录
		return b;
	}
	return false;
}

bool DDownLoadThread::createFileInDir()
{
	return false;
}

QString DDownLoadThread::createMultDir(const QString & strPath)
{
	return false;
}

void DDownLoadThread::removeDir(const QString &strDir)
{
	QDir dir(strDir);
	QString tmpdir = "";
	if (!dir.exists())
	{
		return;
	}

	QFileInfoList fileInfoList = dir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if (fileInfo.isDir()) {
			tmpdir = strDir + ("/") + fileInfo.fileName();
			removeDir(tmpdir);
			dir.rmdir(fileInfo.fileName()); /**< 移除子目录 */
		}
		else if (fileInfo.isFile()) {
			QFile tmpFile(fileInfo.fileName());
			dir.remove(tmpFile.fileName()); /**< 删除临时文件 */
		}
		else
		{
			;
		}
	}

	dir.cdUp(); //返回上级目录，因为只有返回上级目录，才可以删除这个目录
	if (dir.exists(strDir))
	{
		if (!dir.rmdir(strDir))
			return;
	}
	return;
}

void DDownLoadThread::update()
{
    if (!m_strIdList.isEmpty())
    {
       m_strId = m_strIdList.takeAt(0);
       onRequestStart();
    }
}
