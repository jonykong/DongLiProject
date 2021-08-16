#include "DNetworkRequest.h"

DNetworkRequest::DNetworkRequest(QObject *parent)
	: QObject(parent)
{
	m_pReply = NULL;
	m_type = QNetworkAccessManager::PostOperation;
	m_operator = Request_NONE;
	m_pTimer = new QTimer();
	m_pTimer->setSingleShot(true);
	m_pTimer->setInterval(5000);
	connect(m_pTimer, &QTimer::timeout, this, [this]() {
		emit requestTimeOut(m_operator);
	});
	connect(this, &DNetworkRequest::startTimer, this, [this]() {
		if (m_pTimer->isActive())
		{
			m_pTimer->stop();
		}
		m_pTimer->start();
	});
	qRegisterMetaType<Login_RequestOperator>("Login_RequestOperator");

// 	QSslConfiguration config;
// 	QSslConfiguration conf = m_networkRequest.sslConfiguration();
// 	conf.setPeerVerifyMode(QSslSocket::VerifyNone);
// 	conf.setProtocol(QSsl::TlsV1SslV3);
// 	m_networkRequest.setSslConfiguration(conf);
}

DNetworkRequest::~DNetworkRequest()
{
	m_thread.exit();
}

void DNetworkRequest::SetRequestUrl(const QString & strUrl)
{
	m_strUrl = strUrl;
}

void DNetworkRequest::SetRequestType(QNetworkAccessManager::Operation type)
{
	m_type = type;
}

void DNetworkRequest::SetRequestParamter(QJsonObject param)
{
	m_requestParameter = param;
}

void DNetworkRequest::SetRequestOperator(Login_RequestOperator oper)
{
	m_operator = oper;
}

Login_RequestOperator DNetworkRequest::GetRequestOperator()
{
	return m_operator;
}

void DNetworkRequest::MoveToThread(bool enable)
{
	if (enable) 
	{
		m_pTimer->moveToThread(&m_thread);
		moveToThread(&m_thread);
		m_thread.start();
	}
}

void DNetworkRequest::SendRequest(QNetworkAccessManager * manager)
{
	m_networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	switch (m_type)
	{
	case QNetworkAccessManager::GetOperation:
	{
		if (m_requestParameter.size() > 0)
		{
			m_strUrl += "?";
		}
		for (QString key : m_requestParameter.keys())
		{
			m_strUrl += m_requestParameter.value(key).toString();
		}
		m_networkRequest.setUrl(m_strUrl);
		m_pReply = manager->get(m_networkRequest);
		break;
	}
	case QNetworkAccessManager::PutOperation:
		break;
	case QNetworkAccessManager::PostOperation:
	{
		m_networkRequest.setUrl(m_strUrl);
		m_pReply = manager->post(m_networkRequest, QJsonDocument(m_requestParameter).toJson(QJsonDocument::Compact));
		break;
	}
	case QNetworkAccessManager::HeadOperation:
		break;
	case QNetworkAccessManager::DeleteOperation:
		break;
	case QNetworkAccessManager::CustomOperation:
		break;
	default:
		break;
	}
	if (m_pReply)
	{
		connect(m_pReply, &QNetworkReply::finished, this, [this] { emit requestFinished(m_pReply->readAll()); m_pReply->deleteLater(); m_pReply = nullptr; m_pTimer->stop(); });
		connect(m_pReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &DNetworkRequest::onError);
		emit startTimer();
	}

}

QNetworkReply * DNetworkRequest::SendRequest_(QNetworkAccessManager *manager, QNetworkAccessManager::Operation type, QString qsUrl)
{
	if (qsUrl == nullptr)
	{
		qsUrl = m_strUrl;
	}
	m_networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	switch (type)
	{
	case QNetworkAccessManager::GetOperation:
	{
		if (m_requestParameter.size() > 0)
		{
			qsUrl += "?";
		}
		for (QString key : m_requestParameter.keys())
		{
			qsUrl += m_requestParameter.value(key).toString();
		}
		m_networkRequest.setUrl(qsUrl);
		return manager->get(m_networkRequest);
		break;
	}
	case QNetworkAccessManager::PutOperation:
		break;
	case QNetworkAccessManager::PostOperation:
	{
		m_networkRequest.setUrl(qsUrl);
		return manager->post(m_networkRequest, QJsonDocument(m_requestParameter).toJson(QJsonDocument::Compact));
		break;
	}
	case QNetworkAccessManager::HeadOperation:
		break;
	case QNetworkAccessManager::DeleteOperation:
		break;
	case QNetworkAccessManager::CustomOperation:
		break;
	default:
		break;
	}

	return nullptr;
}

void DNetworkRequest::InitTime(int ms)
{
	m_pTimer->setInterval(ms);
}

void DNetworkRequest::onRequest()
{
	if (m_pReply)
	{
		emit requestFinished(m_pReply->readAll());
		if (m_pTimer->isActive())
		{
			m_pTimer->stop();
		}
		m_pReply->deleteLater();
		m_pReply = NULL;
	}
}

void DNetworkRequest::onError(QNetworkReply::NetworkError error)
{
	emit requestError(error);
	if (m_pTimer->isActive())
	{
		m_pTimer->stop();
	}
}
