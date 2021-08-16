#pragma once

#include <QObject>
#include <qmutex.h>
#include <QNetworkReply>
#include <QJsonObject>
#include "DNetworkDef.h"
#include "DNetworkRequestWorker.h"
#include "DSingleton.h"

class DNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit DNetworkManager(QObject *parent = nullptr);
    ~DNetworkManager();

    bool RequestMediaList();
    void DownLoadForUrl(const QString &strId, const QString &strUrl);


protected slots:
    void onRequestFinished(Login_RequestOperator oper, const QByteArray &array);
    void onRequestError(Login_RequestOperator oper, QNetworkReply::NetworkError error);

signals:
    void requestFinished(Login_RequestOperator oper, const QByteArray &array);
    void requestError(Login_RequestOperator oper, QNetworkReply::NetworkError error);
    void requestTimeOut(Login_RequestOperator oper);

private:
    DNetworkRequestWorker		 *m_pRequestWorker;
};

inline std::shared_ptr<DNetworkManager> registerLogin()
{
    return DSingleton<DNetworkManager>::GetInstance();
}
