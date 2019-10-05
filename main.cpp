#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // resolution adaptation

    QApplication a(argc, argv);

    //creating loading screen
    QSplashScreen *loading_screen = new QSplashScreen;
    loading_screen->setPixmap(QPixmap(":/Pictures/Data/Pictures/LoadingScreen.png"));
    //loading_screen->setPixmap(QPixmap("./Data/Picture/LoadingScreen.png"));

    loading_screen->show();

    MainWindow w;

    QTimer::singleShot(2500,loading_screen,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

    return a.exec();
}
