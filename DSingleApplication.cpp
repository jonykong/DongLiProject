#include "DSingleApplication.h"
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>
#include <QLocalServer>
#include <QMessageBox>
#include <QIcon>
#include <QFileOpenEvent>

#define TIME_OUT                (500)    // 500ms

DSingleApplication::DSingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , w(NULL)
    , m_bRunning(false)
    , m_pLocalServer(NULL)
{
    m_qsServerName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
}

bool DSingleApplication::isRunning()
{
    return m_bRunning;
}

QString DSingleApplication::getPath()
{
    return m_strPath;
}

void DSingleApplication::newLocalConnection()
{
    QLocalSocket *socket = m_pLocalServer->nextPendingConnection();
    if (socket)
    {
        socket->waitForReadyRead(2 * TIME_OUT);
        delete socket;

        activateWindow();
    }
}

void DSingleApplication::initLocalConnection()
{
    m_bRunning = false;
    QLocalSocket socket;
    socket.connectToServer(m_qsServerName);
    if (socket.waitForConnected(TIME_OUT))
    {
        fprintf(stderr, "%s already running.\n", m_qsServerName.toLocal8Bit().constData());
        m_bRunning = true;
        return;
    }
    newLocalServer();
}

void DSingleApplication::setServerNameType(bool isAudio)
{
	if (isAudio)
	{
		m_qsServerName += "audio";
	}
	else
	{
		m_qsServerName += "video";
	}
	initLocalConnection();
}

void DSingleApplication::newLocalServer()
{
    m_pLocalServer = new QLocalServer(this);
    connect(m_pLocalServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if (!m_pLocalServer->listen(m_qsServerName))
    {
        if (m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            QLocalServer::removeServer(m_qsServerName);
            m_pLocalServer->listen(m_qsServerName);
        }
    }
}

void DSingleApplication::activateWindow()
{
    if (w)
    {
        w->show();
        w->raise();
        w->activateWindow();
    }
}

bool DSingleApplication::event(QEvent *event)
{
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
        m_strPath = openEvent->file();
    }

    return QApplication::event(event);
}
