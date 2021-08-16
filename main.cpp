#include "MainWindow.h"
#include <QApplication>
#include "DSingleApplication.h"
#include <QDir>
#include <QFile>
#include "windows.h"

#define QSSDIR_PATH ":/icon/resource/"

int main(int argc, char *argv[])
{
    DSingleApplication a(argc, argv);
    if (a.isRunning())
    {
        return 0;
    }
	QCoreApplication::setOrganizationName("DongLiProject");
	QCoreApplication::setApplicationName("DongLiProject");

	// 加载qss文件
	QDir dir(QSSDIR_PATH);
	QString styleSheet;
	QStringList fileList = dir.entryList(QStringList() << "*.qss");
	foreach(const QString & fileName, fileList)
	{
		QFile file(QSSDIR_PATH + fileName);
		if (file.open(QIODevice::ReadOnly))
		{
			styleSheet.append(file.readAll());
			file.close();
		}
	}
	a.setStyleSheet(styleSheet);
	// 加载语言包 todo

    MainWindow w;
    w.show();

    return a.exec();
}
