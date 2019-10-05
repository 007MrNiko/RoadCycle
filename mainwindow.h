#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include <fstream>
#include <vector>
#include <string>
#include <dir.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;

    void fill_table_from_txt();

    /*
    state - державні
    regional - регіональна
    province - обласні
    local - місцева
    */

    vector<vector<string>> //name type length(km) lines pavement divider
    roads_data{
        {"M10","state","86.7","2","no","no"},
        {"T1414","province","5","2","yes","no"},
        {"P02","regional","171.7","2","no","no"},
        {"A2","state","486","6","no","yes"},
        {"E27","regional","328","4","no","yes"},
        {"S7","province","264.2","2","yes","no"},

     };

};
#endif // MAINWINDOW_H
