#include "DNetworkRequestWorker.h"
#include <qnetworkrequest.h>
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qeventloop.h>
#include "DNetworkRequest.h"
						
DNetworkRequestWorker::DNetworkRequestWorker(QObject *parent)
	: QObject(parent)
{
	m_pNetWorker = new QNetworkAccessManager(this);
	connect(this, &DNetworkRequestWorker::requestSend, this, &DNetworkRequestWorker::onRequestSend);
}

DNetworkRequestWorker::~DNetworkRequestWorker()
{

}

void DNetworkRequestWorker::DownLoadForUrl(const QString &strId, const QString &strUrl)
{

}

void DNetworkRequestWorker::onRequestSend(DNetworkRequest* request)
{
	connect(request, &DNetworkRequest::requestFinished, this, &DNetworkRequestWorker::onRequestFinished);
	connect(request, &DNetworkRequest::requestError, this, &DNetworkRequestWorker::onRequestError);
	connect(request, &DNetworkRequest::requestTimeOut, this, &DNetworkRequestWorker::requestTimeOut);
	request->SendRequest(m_pNetWorker);
}

void DNetworkRequestWorker::onRequestFinished(const QByteArray & array)
{
	DNetworkRequest *request = dynamic_cast<DNetworkRequest*>(sender());
	emit requestFinished(request->GetRequestOperator(), array);
}

void DNetworkRequestWorker::onRequestError(QNetworkReply::NetworkError error)
{
	DNetworkRequest *request = dynamic_cast<DNetworkRequest*>(sender());
	emit requestError(request->GetRequestOperator(),error);
}
