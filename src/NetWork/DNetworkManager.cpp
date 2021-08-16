#include "DNetworkManager.h"
#include "DNetworkRequest.h"
#include "DEventLoop.h"
#include "DPublicDef.h"
#include <QJsonArray>
#include "DVideoListManagement.h"
#include "DPlatform.h"

DNetworkManager::DNetworkManager(QObject *parent)
    :QObject(parent)
{
    m_pRequestWorker = new DNetworkRequestWorker(this);
    connect(m_pRequestWorker, &DNetworkRequestWorker::requestFinished, this, &DNetworkManager::onRequestFinished);
    connect(m_pRequestWorker, &DNetworkRequestWorker::requestError, this, &DNetworkManager::onRequestError);
    connect(m_pRequestWorker, &DNetworkRequestWorker::requestTimeOut, this, &DNetworkManager::requestTimeOut);
}

DNetworkManager::~DNetworkManager()
{

}

bool DNetworkManager::RequestMediaList()
{
	DNetworkRequest request;
	QString strUrL = VIDEO_HOME.arg(platform()->getVideoUrl());
	request.SetRequestUrl(strUrL);

	DEventLoop loop;
	QNetworkAccessManager magr;
	QNetworkReply* replay = request.SendRequest_(&magr, QNetworkAccessManager::GetOperation);
	connect(replay, &QNetworkReply::finished, &loop, &DEventLoop::TimeOut);
	loop.start();
	loop.exec();
	if (replay == nullptr || replay->error())
	{
		replay->deleteLater();
		replay = NULL;
		return false;
	}
	else
	{
		QByteArray arr = replay->readAll();
		replay->deleteLater();
		replay = NULL;

		QString strParam = QString::fromUtf8(arr);

		QJsonDocument jsonDocument = QJsonDocument::fromJson(arr);
		QJsonObject obj = jsonDocument.object();
		if (!obj.isEmpty())
		{
			if (obj.contains("code"))
			{
				int qsErrorCode = obj.value("code").toInt();
				if (qsErrorCode != 200)
				{
					return false;
				}

				if (obj.contains("data"))
				{
					QJsonArray dataArry = obj.value("data").toArray();
					for (int i = 0; i < dataArry.size(); ++i)
					{
						QJsonObject videoInfo = dataArry.at(i).toObject();
						if (!videoInfo.isEmpty())
						{
                            videoManagement()->AddVideoList(videoInfo);
						}
					}
					for (int i = 0; i < dataArry.size(); ++i)
					{
						QJsonObject videoInfo = dataArry.at(i).toObject();
						if (!videoInfo.isEmpty())
						{
							videoManagement()->AddVideoList(videoInfo);
						}
					}
				}
			}
		}
	}
	return true;
}

void DNetworkManager::DownLoadForUrl(const QString &strId, const QString &strUrl)
{
    m_pRequestWorker->DownLoadForUrl(strId, strUrl);
}

void DNetworkManager::onRequestFinished(Login_RequestOperator oper, const QByteArray &array)
{
    emit requestFinished(oper, array);
}

void DNetworkManager::onRequestError(Login_RequestOperator oper, QNetworkReply::NetworkError error)
{
    emit requestError(oper, error);
}

