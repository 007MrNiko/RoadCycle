#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include <QtQuick/QQuickItem>
#include <QFileDialog>
#include <QDir>

#include <fstream>
#include <vector>
#include <string>
#include <dir.h>
#include <bits/stdc++.h>

#include "dialogadditem.h"

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
    void on_actionResetTable_triggered();

    void on_actionDeleteElement_triggered();

    void on_actionAscendingSortColumn_triggered();

    void on_actionDescendingSortColumn_triggered();

    void on_actionAddElement_triggered();

    void on_actionDeleteAllElement_triggered();

    void on_actionOpenNewFile_triggered();

private:
    Ui::MainWindow *ui;

    void fill_table_from_txt();

    /*
    state - державна
    regional - регіональна
    province - обласна
    local - місцева
    */

    vector<vector<string>> //name type length(km) lines pavement divider
    roads_data{
        {"M10","державна","86.7","2","так","ні"},
        {"T1414","місцева","5","2","так","ні"},
        {"P02","регіональна","171.7","2","ні","ні"},
        {"A2","державна","486","6","ні","так"},
        {"E27","регіональна","328","4","ні","так"},
        {"S7","обласна","264.2","2","так","ні"},
        {"P48","регіональна","159.9","2","ні","ні"},
        {"H22","місцева","155.9","2","ні","ні"},
        {"M06","обласна","888.8","3","ні","ні"},
        {"E40","регіональна","8500 ","6","так","так"}
     };

};
#endif // MAINWINDOW_H
