#pragma once

#include <QObject>
#include <qnetworkrequest.h>
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qeventloop.h>
#include <QNetworkReply>
#include <qthread.h>
#include <QTimer>
#include "DNetworkDef.h"

class DNetworkRequest : public QObject
 {
	Q_OBJECT

public:
	DNetworkRequest(QObject *parent = NULL);
	~DNetworkRequest();

	// 请求地址
	void SetRequestUrl(const QString &strUrl);
	// 操作类型
	void SetRequestType(QNetworkAccessManager::Operation type);
	// 参数
	void SetRequestParamter(QJsonObject param);
	// 事件类型
	void SetRequestOperator(Login_RequestOperator oper);

	//  获得请求类型
	Login_RequestOperator GetRequestOperator();
	// 是否进入线程执行
	void MoveToThread(bool enable);
	// 发送请求
	void SendRequest(QNetworkAccessManager *manager);
	// 同步请求
	QNetworkReply *SendRequest_(QNetworkAccessManager *manager, QNetworkAccessManager::Operation type, QString qsUrl = nullptr);
	void InitTime(int ms = 5000);

signals:
	// 请求完成
	void requestFinished(const QByteArray &array);
	// 请求失败
	void requestError(QNetworkReply::NetworkError error);
	// 请求超时 
	void requestTimeOut(Login_RequestOperator oper);
	// 开始计时
	void startTimer();

protected slots:
	void onRequest();
	void onError(QNetworkReply::NetworkError error);

private:
	QString                             m_strUrl;                        // 请求地址
	QNetworkAccessManager::Operation    m_type;                          // 请求类型
	QJsonObject                         m_requestParameter;              // 请求参数
	QNetworkRequest                     m_networkRequest;                // 请求对象
	Login_RequestOperator               m_operator;                      // 请求事件类型
	QNetworkReply*                      m_pReply;                        // 请求回执
	QThread                             m_thread;                        // 请求线程
	QTimer*                             m_pTimer;                        // 计时器
};
