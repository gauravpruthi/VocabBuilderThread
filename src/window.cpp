#include "headers/window.h"


Window::Window()
{
    createMessageGroupBox();

    head = "";
    body = "";
    createActions();
    createTrayIcon();

    connect(showMessageButton, &QAbstractButton::clicked, this, &Window::showMessage);
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &Window::messageClicked);
    //connect(trayIcon, &QSystemTrayIcon::activated, this, &Window::iconActivated);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);

    trayIcon->show();

    setWindowTitle(tr("Systray"));
    resize(400, 300);

    worker = new Worker();

    //std::thread t(&Window::mainThread);



}

void Window::mainThread()
{

    while(true)
    {

        worker->extractAndUpdate();
        //BaseData *instance = BaseData::getInstance();

        head.append(BaseData::getInstance()->getWord());
        head.append("\n\n");
        body.append("Meaning : ");
        body.append(BaseData::getInstance()->getMeaning());
        body.append("\n\n");
        body.append("Example : ");
        body.append(BaseData::getInstance()->getExample());
        showMessage();
        // Clear the data after use...it will be filled later after the next call..
        QThread::sleep(1500);
    }
}

void Window::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

//void Window::setIcon(int index)
//{
//    QIcon icon = iconComboBox->itemIcon(index);
//    trayIcon->setIcon(icon);
//    setWindowIcon(icon);

//    trayIcon->setToolTip(iconComboBox->itemText(index));
//}

//void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
//{
//    switch (reason) {
//    case QSystemTrayIcon::Trigger:
//    case QSystemTrayIcon::DoubleClick:
//        iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
//        break;
//    default:
//        ;
//    }
//}

void Window::showMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(0);
    trayIcon->showMessage(head, body, icon,
                          15000);
}

void Window::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void Window::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox(tr("Balloon Message"));
    showMessageButton = new QPushButton(tr("Show Message"));
    showMessageButton->setDefault(true);

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(showMessageButton, 0, 0);
    messageGroupBox->setLayout(messageLayout);
}

void Window::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    //quitAction = new QAction(tr("&Quit"), this);
    //connect(quitAction, &QAction::triggered, this, &QApplication::quit);
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    //trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

