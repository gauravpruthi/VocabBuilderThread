#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QApplication>
#include <QAction>
#include <QPushButton>
#include <iostream>
#include <QVBoxLayout>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <thread>
#include <QThread>
#include <QGroupBox>
#include "worker.h"
#include "basedata.h"

class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible) Q_DECL_OVERRIDE;

//protected:
//    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:

    void showMessage();
    void messageClicked();
    void mainThread();
    //void quit();

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();


    QLabel *iconLabel;
    QPushButton *showMessageButton;
    Worker *worker;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QString head;
    QString body;
    QGroupBox *messageGroupBox;
};

#endif // QT_NO_SYSTEMTRAYICON

