#include "DPlatform.h"
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include "DPublicDef.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "DNetworkManager.h"
#include "DDownLoadThread.h"
#include "DVideoListManagement.h"
#include <QWebSocket>
#include <iostream>
#include <QApplication>
#include <QQueue>
#include <QDir>
#include "PlayDialog.h"
#include "Player.h"
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QCoreApplication>

static MaterialType getMaterialType(QString strFilePath)
{
    QFileInfo fileInfo;
    fileInfo.setFile(strFilePath);

    if (fileInfo.isDir())
    {
        return MaterialType_folder;
    }

    QString strSuffix = fileInfo.suffix();
    if (strSuffix.compare("avi", Qt::CaseInsensitive) == 0 || strSuffix.compare("wmv", Qt::CaseInsensitive) == 0 || strSuffix.compare("rmvb", Qt::CaseInsensitive) == 0 || strSuffix.compare("rm", Qt::CaseInsensitive) == 0
        || strSuffix.compare("mp4", Qt::CaseInsensitive) == 0 || strSuffix.compare("mid", Qt::CaseInsensitive) == 0 || strSuffix.compare("3gp", Qt::CaseInsensitive) == 0 || strSuffix.compare("mpg", Qt::CaseInsensitive) == 0 || strSuffix.compare("mkv", Qt::CaseInsensitive) == 0
        || strSuffix.compare("mov", Qt::CaseInsensitive) == 0 || strSuffix.compare("mpeg", Qt::CaseInsensitive) == 0 || strSuffix.compare("m2v", Qt::CaseInsensitive) == 0
        || strSuffix.compare("ts", Qt::CaseInsensitive) == 0 || strSuffix.compare("mts", Qt::CaseInsensitive) == 0 || strSuffix.compare("m2t", Qt::CaseInsensitive) == 0
        || strSuffix.compare("m2ts", Qt::CaseInsensitive) == 0 || strSuffix.compare("flv", Qt::CaseInsensitive) == 0 || strSuffix.compare("f4v", Qt::CaseInsensitive) == 0
        || strSuffix.compare("m4v", Qt::CaseInsensitive) == 0 || strSuffix.compare("dat", Qt::CaseInsensitive) == 0 || strSuffix.compare("vob", Qt::CaseInsensitive) == 0
        || strSuffix.compare("webm", Qt::CaseInsensitive) == 0
        )
    {
        return MaterialType_video;
    }
    else if (strSuffix.compare("bmp", Qt::CaseInsensitive) == 0 || strSuffix.compare("jpg", Qt::CaseInsensitive) == 0 || strSuffix.compare("jpeg", Qt::CaseInsensitive) == 0
        || strSuffix.compare("png", Qt::CaseInsensitive) == 0 || strSuffix.compare("ico", Qt::CaseInsensitive) == 0 || strSuffix.compare("cur", Qt::CaseInsensitive) == 0
        || strSuffix.compare("tiff", Qt::CaseInsensitive) == 0 || strSuffix.compare("tif", Qt::CaseInsensitive) == 0 || strSuffix.compare("tga", Qt::CaseInsensitive) == 0)
    {
        return MaterialType_picture;
    }
    else if (strSuffix.compare("mp3", Qt::CaseInsensitive) == 0 || strSuffix.compare("wav", Qt::CaseInsensitive) == 0 || strSuffix.compare("wma", Qt::CaseInsensitive) == 0
        || strSuffix.compare("ape", Qt::CaseInsensitive) == 0 || strSuffix.compare("aac", Qt::CaseInsensitive) == 0 || strSuffix.compare("amr", Qt::CaseInsensitive) == 0
        || strSuffix.compare("ogg", Qt::CaseInsensitive) == 0 || strSuffix.compare("m4a", Qt::CaseInsensitive) == 0 || strSuffix.compare("flac", Qt::CaseInsensitive) == 0)
    {
        return MaterialType_audio;
    }
    return MaterialType_error;
}

static QString createDir(const QString & strPath)
{
	QDir dir(strPath);
	if (dir.exists(strPath))
	{
		return strPath;
	}
	QString parentDir = createDir(strPath.mid(0, strPath.lastIndexOf('/')));
	QString dirname = strPath.mid(strPath.lastIndexOf('/') + 1);
	QDir parentPath(parentDir);
	if (!dirname.isEmpty())
		if (!parentPath.mkpath(dirname))
			return "";
	return parentDir + "/" + dirname;
}

DPlatform *DPlatform::instance()
{
	static DPlatform m_platform;
	return &m_platform;
}

void DPlatform::InitVideoList()
{
	// 请求文件,判断服务器文件 和版本号是否需要更新
	m_strDownLoadPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

	m_pDownLoad = new DDownLoadThread();
	m_pDownLoad->setDownLoadPath(m_strDownLoadPath);

	connect(m_pDownLoad, &DDownLoadThread::sigProgressUpdate, this, &DPlatform::signalProgressUpdate);
	connect(m_pDownLoad, &DDownLoadThread::sigDownLoadFinished, this, &DPlatform::signalDownLoadFinished);
	connect(m_pDownLoad, &DDownLoadThread::sigDownLoadError, this, &DPlatform::signalDownLoadError);

	videoManagement()->InitVideoList();
	registerLogin()->RequestMediaList();
}

void DPlatform::DownLoadFile(const QString& strId)
{
    QString strFile = m_strDownLoadPath + strId + ".mp4";
    if (QFileInfo(strFile).exists())
    {
        emit signalDownLoadFinished(strId, strFile);
    }
    else
    {
        m_pDownLoad->startDown(strId, VIDEO_PATH);
    }

}

void DPlatform::CheckUsbDiskFile(const QString& strPath)
{
	if (m_usbFile.contains(strPath))
	{
		return;
	}
    m_mediaFile->start(strPath);
}

void DPlatform::RemoveUSBFile()
{
	if (!m_mediaFile->isRunning())
	{
		m_usbFile.clear();
		videoManagement()->RemoveUSBFile();
	}
}

QString DPlatform::getSenderId() const
{
    return m_strSenderId;
}

QString DPlatform::getReceiverId() const
{
    return m_strReiverId;
}

QString DPlatform::getURL() const
{
	return m_strUrl;
}

QString DPlatform::getVideoUrl() const
{
	return m_strVideoUrl;
}

Player* DPlatform::getPlayer()
{
	return m_player;
}

void DPlatform::sendMessage(const QString& strMsg)
{
	m_pWebSocket->sendTextMessage(strMsg);
}

void DPlatform::onDownLoadFinished(const QString& strId, const QString &strPath)
{
    emit signalDownLoadFinished(strId, strPath);
}

void DPlatform::onConnected()
{
	std::cout << "onConnected" << std::endl;

	QJsonObject obj;
	obj.insert("senderId", "venue-33-afc84bc3-4359-2c83-376a-f73956500a94");
	QJsonObject obj2;
	obj2.insert("action", 1);
	obj2.insert("chatMsg", obj);
	QString jons = QJsonDocument(obj2).toJson();
	//QString josnString = "{\"action\": 1,\"chatMsg\" : {\"senderId\": \"venue-33-afc84bc3-4359-2c83-376a-f73956500a94\"}}";

	sendMessage(jons);
	sendMessage(readFile());

}

void DPlatform::onDisconnected()
{
	std::cout << "disconnected" << std::endl;
}

void DPlatform::onTextMessageReceived(const QString &message)
{
	std::cout << message.toStdString() << std::endl;
}

void DPlatform::onBinaryMessageReceived(const QByteArray &message)
{
	std::cout << message.toStdString() << std::endl;
}

void DPlatform::onUpdateFile(const QString &strDir, const QStringList &strFileList)
{
    m_usbFile.insert(strDir, strFileList);
    videoManagement()->AddUSBFile(strFileList);
}

void DPlatform::init()
{
	m_strWriteDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
	m_pSettings = new QSettings(QSettings::NativeFormat, QSettings::UserScope,
		QCoreApplication::organizationName(), QCoreApplication::applicationName());

	m_pWebSocket = new QWebSocket;
	connect(m_pWebSocket, &QWebSocket::connected, this, &DPlatform::onConnected);
	connect(m_pWebSocket, &QWebSocket::disconnected, this, &DPlatform::onDisconnected);
	connect(m_pWebSocket, &QWebSocket::textMessageReceived, this, &DPlatform::onTextMessageReceived);
	connect(m_pWebSocket, &QWebSocket::binaryMessageReceived, this, &DPlatform::onBinaryMessageReceived);
	connect(m_pWebSocket, &QWebSocket::stateChanged, this, [this](QAbstractSocket::SocketState state)
	{
		std::cout << (int)state << std::endl;
	});

    m_mediaFile = new QSearchMeidaFile(this);
    connect(m_mediaFile, &QSearchMeidaFile::signalUpdateFile, this, &DPlatform::onUpdateFile);


	QString strXML = readFile();
	QJsonDocument jsonDocument = QJsonDocument::fromJson(strXML.toLocal8Bit().data());
	if (jsonDocument.isNull())
	{
		return;
	}
	QJsonObject jsonObject = jsonDocument.object();
	if (jsonObject.contains("chatMsg"))
	{
		QJsonObject jsonObject2 = jsonObject.value("chatMsg").toObject();
		if (jsonObject2.contains("senderId"))
		{
			m_strSenderId = jsonObject2.value("senderId").toString();
		}
		if (jsonObject2.contains("receiverId"))
		{
			m_strReiverId = jsonObject2.value("receiverId").toString();
		}
	}
	if (jsonObject.contains("URL"))
	{
		m_strUrl = jsonObject.value("URL").toString();
	}
	if (jsonObject.contains("video_url"))
	{
		m_strVideoUrl = jsonObject.value("video_url").toString();
	}
}

void DPlatform::addLocalVideo()
{

}

void DPlatform::addLocalVideo(QJsonObject obj)
{
	if (obj.isEmpty())
	{
		return;
	}

	// 获取类型
	DPublicDef::VideoListType eType = (DPublicDef::VideoListType)obj.value(VideoType).toInt();
	// 获取类型
	QString strName = (DPublicDef::VideoListType)obj.value(VideoName).toInt();

}

QString DPlatform::readFile()
{
	QString strContext;

	QFile file(QApplication::applicationDirPath() + "/ProjectSettings.xml");
	if (file.open(QFile::ReadOnly))
	{
		strContext = file.readAll();
		file.close();
	}
	return strContext;
}

QStringList DPlatform::searchMeidaFile(QString strPath)
{
    // 这里不适用递归算法,改为B树的 层次遍历
    QStringList VideoFilePath;
    
    QQueue<QString> quePath;
    quePath.push_back(strPath);

    while (!quePath.empty())
    {
        QString strFilePath = quePath.dequeue();

        MaterialType meidaType = getMaterialType(strFilePath);
        if (meidaType == MaterialType_video)
        {
            VideoFilePath.append(strFilePath);
        }
        else if (meidaType == MaterialType_folder)
        {
            QDir dir(strFilePath);
            for (int i = 0; i < dir.entryList().size(); i++)
            {
                QString filePath = dir.entryList().at(i);

                if (filePath == "." || filePath == "..")
                {
                    continue;
                }
                quePath.push_back(strFilePath + QDir::separator() + filePath);
            }
        }
    }
    return VideoFilePath;
}

DPlatform::DPlatform(QObject *parent /*= nullptr*/)
	: QObject(parent)
    , m_pDownLoad(nullptr)
    , m_strSenderId("")
    , m_strReiverId("")
	, m_strUrl("http://39.98.113.10:8888/")
	, m_strVideoUrl("http://39.98.113.10:8888/")
{
	init();
	m_player = new Player;
}

DPlatform::~DPlatform()
{
}

QSearchMeidaFile::QSearchMeidaFile(QObject *parent)
    : QThread(parent)
    , m_bRunning(false)
{
    connect(this, &QSearchMeidaFile::signalUpdate, this, [this]
    {
        emit signalUpdateFile(m_strDir, m_strFileList);
    });
}

QSearchMeidaFile::~QSearchMeidaFile()
{
    stop();
}

void QSearchMeidaFile::start(const QString &strDir)
{
    if (m_bRunning)
    {
        return;
    }
    m_strDir = strDir;
    QThread::start();
}

void QSearchMeidaFile::stop()
{
    m_bRunning = false;
    this->wait(1000);
}

void QSearchMeidaFile::run()
{
    m_bRunning = true;
    m_strFileList.clear();
    QQueue<QString> quePath;
    quePath.push_back(m_strDir);

    while (!quePath.empty())
    {
        if (!m_bRunning)
        {
            break;
        }
        QString strFilePath = quePath.dequeue();

        MaterialType meidaType = getMaterialType(strFilePath);
        if (meidaType == MaterialType_video)
        {
            m_strFileList.append(strFilePath);
        }
        else if (meidaType == MaterialType_folder)
        {
            QDir dir(strFilePath);
            for (int i = 0; i < dir.entryList().size(); i++)
            {
                QString filePath = dir.entryList().at(i);

                if (filePath == "." || filePath == "..")
                {
                    continue;
                }
                quePath.push_back(strFilePath + QDir::separator() + filePath);
            }
        }
#if _DEBUG
		if (m_strFileList.size() > 10)
		{
			break;
		}

#endif
    }
    m_bRunning = false;

    emit signalUpdate();
}
