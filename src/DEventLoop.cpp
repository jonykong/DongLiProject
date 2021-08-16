#include "DEventLoop.h"

DEventLoop::DEventLoop(QObject *parent /*= nullptr*/)
	: QEventLoop(parent)
	, m_timer(new QTimer)
{
	connect(m_timer, &QTimer::timeout, this, &DEventLoop::TimeOut);
}

DEventLoop::~DEventLoop()
{
	m_timer->stop();
	delete m_timer;
}

void DEventLoop::start(int msec)
{
	m_timer->start(msec);
}

void DEventLoop::TimeOut()
{
	m_timer->stop();
	this->quit();
}
