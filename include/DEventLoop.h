#pragma once
#include <QEventLoop>
#include <QTimer>

class DEventLoop : public QEventLoop
{
	Q_OBJECT
public:
	explicit DEventLoop(QObject *parent = nullptr);
	~DEventLoop();
	void start(int msec = 3000);

public slots:
	void TimeOut();

private:
	QTimer			*m_timer;
};