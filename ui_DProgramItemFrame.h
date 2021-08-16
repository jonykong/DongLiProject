/********************************************************************************
** Form generated from reading UI file 'DProgramItemFrame.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DPROGRAMITEMFRAME_H
#define UI_DPROGRAMITEMFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DProgramItemFrame
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QLabel *label;

    void setupUi(QFrame *DProgramItemFrame)
    {
        if (DProgramItemFrame->objectName().isEmpty())
            DProgramItemFrame->setObjectName(QStringLiteral("DProgramItemFrame"));
        DProgramItemFrame->resize(148, 108);
        DProgramItemFrame->setStyleSheet(QStringLiteral(""));
        DProgramItemFrame->setFrameShape(QFrame::StyledPanel);
        DProgramItemFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(DProgramItemFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 0);
        widget = new QWidget(DProgramItemFrame);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(142, 86));
        widget->setMaximumSize(QSize(142, 86));
        widget->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame = new QFrame(widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);


        verticalLayout->addWidget(widget);

        label = new QLabel(DProgramItemFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("font-size: 10px;\n"
"font-family: PingFang SC;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalLayout->setStretch(0, 1);

        retranslateUi(DProgramItemFrame);

        QMetaObject::connectSlotsByName(DProgramItemFrame);
    } // setupUi

    void retranslateUi(QFrame *DProgramItemFrame)
    {
        DProgramItemFrame->setWindowTitle(QApplication::translate("DProgramItemFrame", "Frame", Q_NULLPTR));
        label->setText(QApplication::translate("DProgramItemFrame", "name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DProgramItemFrame: public Ui_DProgramItemFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DPROGRAMITEMFRAME_H
