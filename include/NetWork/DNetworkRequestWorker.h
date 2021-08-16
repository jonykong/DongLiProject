#pragma once

#include <QObject>
#include <qnetworkaccessmanager.h>
#include <QNetworkReply>
#include "DNetworkDef.h"

class DNetworkRequest;
class DNetworkRequestWorker : public QObject
{
	Q_OBJECT

public:
    DNetworkRequestWorker(QObject *parent);
	~DNetworkRequestWorker();

    void DownLoadForUrl(const QString &strId, const QString &strUrl);
	
protected slots:
	void onRequestSend(DNetworkRequest* request);
	void onRequestFinished(const QByteArray &array);
	void onRequestError(QNetworkReply::NetworkError error);

signals:
	void requestSend(DNetworkRequest* request);
	void requestFinished(Login_RequestOperator oper, const QByteArray &array);
	void requestError(Login_RequestOperator oper, QNetworkReply::NetworkError error);
	/** 请求超时 */
	void requestTimeOut(Login_RequestOperator oper);

private:
	QNetworkAccessManager *m_pNetWorker;
};
