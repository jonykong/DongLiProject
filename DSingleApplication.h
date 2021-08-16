#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H
#include <QObject>
#include <QApplication>
#include <QWidget>

class QLocalServer;
class DSingleApplication : public QApplication
{
    Q_OBJECT

public:
	DSingleApplication(int &argc, char **argv);

    bool isRunning();                //是否存在实例在运行中
    QWidget *w;                      // MainWindow指针
    QString getPath();
	// 初始化本地连接
	void initLocalConnection();
	void setServerNameType(bool isAudio);

private slots:
    // 有新连接时触发
    void newLocalConnection();

private:
    // 创建服务端
    void newLocalServer();
    // 激活窗口
    void activateWindow();
    bool event(QEvent *event);

private:
    bool                    m_bRunning;        // 是否有实例在运行
    QLocalServer           *m_pLocalServer;     // 本地socket Server
    QString                 m_qsServerName;    // 服务名称
    QString                 m_strPath = nullptr;
};

#endif
