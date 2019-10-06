#ifndef TASKOUTPUT_H
#define TASKOUTPUT_H

#include <QDialog>
#include <QTextStream>
#include <QTableWidget>
#include <QtQuick/QQuickItem>

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Ui {
class taskOutput;
}

class taskOutput : public QDialog
{
    Q_OBJECT

public:
    explicit taskOutput(QWidget *parent = nullptr);
    ~taskOutput();

    void output_task_1();
    void output_task_2();
    void output_task_3();
    void output_task_4();

private:
    Ui::taskOutput *ui;
};

#endif // TASKOUTPUT_H
