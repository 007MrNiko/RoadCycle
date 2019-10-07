#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>
#include <QStyleFactory>
#include <QTableView>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // resolution adaptation

    QApplication a(argc, argv);

    // setup dark theme)))
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",QSettings::NativeFormat);
        if(settings.value("AppsUseLightTheme")==0){
            qApp->setStyle(QStyleFactory::create("Fusion"));
            QPalette darkPalette;
            QColor darkColor = QColor(45,45,45);
            QColor disabledColor = QColor(127,127,127);
            darkPalette.setColor(QPalette::Window, darkColor);
            darkPalette.setColor(QPalette::WindowText, Qt::white);
            darkPalette.setColor(QPalette::Base, QColor(18,18,18));
            darkPalette.setColor(QPalette::AlternateBase, darkColor);
            darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
            darkPalette.setColor(QPalette::ToolTipText, Qt::white);
            darkPalette.setColor(QPalette::Text, Qt::white);
            darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
            darkPalette.setColor(QPalette::Button, darkColor);
            darkPalette.setColor(QPalette::ButtonText, Qt::white);
            darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
            darkPalette.setColor(QPalette::BrightText, Qt::red);
            darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

            darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::HighlightedText, Qt::black);
            darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

            qApp->setPalette(darkPalette);

            qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
        }

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
