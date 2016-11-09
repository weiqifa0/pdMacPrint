/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QWidget *widget_main;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *textEdit_2;
    QLineEdit *textEdit_3;
    QLineEdit *textEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *rencode_view;
    QLabel *rencode_view_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *rencode_lineEdit;
    QLineEdit *rencode_lineEdit_2;
    QPushButton *print_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(762, 499);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget_main = new QWidget(centralwidget);
        widget_main->setObjectName(QStringLiteral("widget_main"));
        widget_main->setStyleSheet(QStringLiteral(""));
        verticalLayout_9 = new QVBoxLayout(widget_main);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        groupBox_3 = new QGroupBox(widget_main);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        widget = new QWidget(groupBox_3);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(230, 16777215));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(50, 0));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 16, 5, 5);
        checkBox = new QCheckBox(groupBox_4);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy2);
        checkBox->setChecked(true);

        gridLayout->addWidget(checkBox, 3, 1, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupBox_4);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setEnabled(true);

        gridLayout->addWidget(plainTextEdit, 4, 1, 1, 2);

        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy3);
        groupBox_5->setMinimumSize(QSize(0, 97));
        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 54, 12));
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 31, 16));
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 70, 31, 16));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 70, 16, 16));
        textEdit_2 = new QLineEdit(groupBox_5);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(40, 69, 51, 21));
        textEdit_3 = new QLineEdit(groupBox_5);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(120, 69, 61, 21));
        textEdit = new QLineEdit(groupBox_5);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(60, 20, 141, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        textEdit->setFont(font);

        gridLayout->addWidget(groupBox_5, 0, 1, 3, 1);


        verticalLayout_4->addWidget(groupBox_4);


        horizontalLayout_5->addWidget(widget);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rencode_view = new QLabel(groupBox);
        rencode_view->setObjectName(QStringLiteral("rencode_view"));
        rencode_view->setEnabled(true);
        sizePolicy1.setHeightForWidth(rencode_view->sizePolicy().hasHeightForWidth());
        rencode_view->setSizePolicy(sizePolicy1);
        rencode_view->setScaledContents(false);
        rencode_view->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(rencode_view);

        rencode_view_2 = new QLabel(groupBox);
        rencode_view_2->setObjectName(QStringLiteral("rencode_view_2"));
        sizePolicy1.setHeightForWidth(rencode_view_2->sizePolicy().hasHeightForWidth());
        rencode_view_2->setSizePolicy(sizePolicy1);
        rencode_view_2->setTextFormat(Qt::RichText);
        rencode_view_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(rencode_view_2);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rencode_lineEdit = new QLineEdit(groupBox);
        rencode_lineEdit->setObjectName(QStringLiteral("rencode_lineEdit"));
        rencode_lineEdit->setEnabled(false);

        horizontalLayout_2->addWidget(rencode_lineEdit);

        rencode_lineEdit_2 = new QLineEdit(groupBox);
        rencode_lineEdit_2->setObjectName(QStringLiteral("rencode_lineEdit_2"));
        rencode_lineEdit_2->setEnabled(false);
        sizePolicy.setHeightForWidth(rencode_lineEdit_2->sizePolicy().hasHeightForWidth());
        rencode_lineEdit_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(rencode_lineEdit_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        print_button = new QPushButton(groupBox);
        print_button->setObjectName(QStringLiteral("print_button"));
        print_button->setMinimumSize(QSize(0, 40));

        verticalLayout_5->addWidget(print_button);


        horizontalLayout_5->addWidget(groupBox);


        verticalLayout_9->addWidget(groupBox_3);


        gridLayout_2->addWidget(widget_main, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_3->setTitle(QString());
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\350\260\203\350\257\225\344\277\241\346\201\257", 0));
        checkBox->setText(QApplication::translate("MainWindow", "\345\220\214\346\227\266\346\211\223\345\215\260\344\270\244\345\274\240\344\272\214\347\273\264\347\240\201", 0));
        groupBox_5->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\346\225\260\345\255\227", 0));
        label_2->setText(QApplication::translate("MainWindow", "\351\227\264\351\232\224", 0));
        label_3->setText(QApplication::translate("MainWindow", "\346\211\223\345\215\260", 0));
        label_4->setText(QApplication::translate("MainWindow", "\344\273\275", 0));
        textEdit_2->setText(QApplication::translate("MainWindow", "1", 0));
        textEdit_3->setText(QApplication::translate("MainWindow", "1", 0));
        textEdit->setText(QApplication::translate("MainWindow", "DD5411300001", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\344\272\214\347\273\264\347\240\201\346\230\276\347\244\272", 0));
        rencode_view->setText(QApplication::translate("MainWindow", " QR Code", 0));
        rencode_view_2->setText(QApplication::translate("MainWindow", " QR Code", 0));
        print_button->setText(QApplication::translate("MainWindow", "\346\211\223\345\215\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
