/********************************************************************************
** Form generated from reading UI file 'VideoFrame.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOFRAME_H
#define UI_VIDEOFRAME_H

#include <DListWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VideoFrame
{
public:
    QVBoxLayout *verticalLayout_3;
    QFrame *listFrame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_logo1;
    QToolButton *toolButton_logo2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_more;
    QToolButton *toolButton;
    DListWidget *listWidget;

    void setupUi(QFrame *VideoFrame)
    {
        if (VideoFrame->objectName().isEmpty())
            VideoFrame->setObjectName(QStringLiteral("VideoFrame"));
        VideoFrame->resize(1080, 621);
        VideoFrame->setFrameShape(QFrame::StyledPanel);
        VideoFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(VideoFrame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(40, -1, -1, -1);
        listFrame = new QFrame(VideoFrame);
        listFrame->setObjectName(QStringLiteral("listFrame"));
        listFrame->setStyleSheet(QStringLiteral(""));
        listFrame->setFrameShape(QFrame::StyledPanel);
        listFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(listFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(listFrame);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 5, 6, 5);
        toolButton_logo1 = new QToolButton(frame);
        toolButton_logo1->setObjectName(QStringLiteral("toolButton_logo1"));
        toolButton_logo1->setMinimumSize(QSize(30, 27));
        toolButton_logo1->setMaximumSize(QSize(33, 27));
        toolButton_logo1->setStyleSheet(QLatin1String("background-image: url(:/icon/resource/button.png);\n"
"font-size: 16px;"));
        toolButton_logo1->setIconSize(QSize(30, 27));
        toolButton_logo1->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_logo1);

        toolButton_logo2 = new QToolButton(frame);
        toolButton_logo2->setObjectName(QStringLiteral("toolButton_logo2"));
        toolButton_logo2->setMinimumSize(QSize(30, 27));
        toolButton_logo2->setMaximumSize(QSize(33, 27));
        toolButton_logo2->setLayoutDirection(Qt::LeftToRight);
        toolButton_logo2->setStyleSheet(QLatin1String("background-image: url(:/icon/resource/button.png);\n"
"font-size: 16px;"));
        toolButton_logo2->setIconSize(QSize(30, 27));
        toolButton_logo2->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton_logo2->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_logo2);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("font-size: 14px;\n"
"font-family: Adobe Heiti Std;\n"
"font-weight: normal;\n"
"color: #8E3122;"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_more = new QLabel(frame);
        label_more->setObjectName(QStringLiteral("label_more"));
        label_more->setStyleSheet(QLatin1String("font-size: 14px;\n"
"font-family: Adobe Heiti Std;\n"
"font-weight: normal;"));

        horizontalLayout->addWidget(label_more);

        toolButton = new QToolButton(frame);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setMinimumSize(QSize(16, 16));
        toolButton->setMaximumSize(QSize(15, 16));
        toolButton->setStyleSheet(QStringLiteral("background-image: url(:/icon/resource/more.png);"));
        toolButton->setIconSize(QSize(15, 16));
        toolButton->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(frame);

        listWidget = new DListWidget(listFrame);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QStringLiteral("border-image: url(:/icon/resource/listItem.png);"));
        listWidget->setIconSize(QSize(30, 27));

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addWidget(listFrame);


        retranslateUi(VideoFrame);

        QMetaObject::connectSlotsByName(VideoFrame);
    } // setupUi

    void retranslateUi(QFrame *VideoFrame)
    {
        VideoFrame->setWindowTitle(QApplication::translate("VideoFrame", "Frame", Q_NULLPTR));
        toolButton_logo1->setText(QString());
        toolButton_logo2->setText(QString());
        label->setText(QApplication::translate("VideoFrame", "  \344\275\234\345\223\201\345\261\225\347\244\272", Q_NULLPTR));
        label_more->setText(QApplication::translate("VideoFrame", "\346\237\245\347\234\213\346\233\264\345\244\232", Q_NULLPTR));
        toolButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoFrame: public Ui_VideoFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOFRAME_H
