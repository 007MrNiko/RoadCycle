#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mkdir("Data"); //create directory for files
    fill_table_from_txt();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::fill_table_from_txt()
{
    string road_name, road_type, road_length, road_lines, road_pavement, road_divider, temp_line;
    int amount_of_lines{0}, current_row{0};

    ifstream fileIn ("Data/DataBase.txt");
    ifstream fileIn_to_count ("Data/DataBase.txt");

    while (getline(fileIn_to_count, temp_line)){
            amount_of_lines++;
    }

    ui->RoadData->setRowCount(amount_of_lines);

    if(fileIn.is_open()){
        while(fileIn >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            ui->RoadData->setItem(current_row,0,new QTableWidgetItem(QString::fromStdString(road_name))); // row, column, item
            ui->RoadData->setItem(current_row,1,new QTableWidgetItem(QString::fromStdString(road_type)));
            ui->RoadData->setItem(current_row,2,new QTableWidgetItem(QString::fromStdString(road_length)));
            ui->RoadData->setItem(current_row,3,new QTableWidgetItem(QString::fromStdString(road_lines)));
            ui->RoadData->setItem(current_row,4,new QTableWidgetItem(QString::fromStdString(road_pavement)));
            ui->RoadData->setItem(current_row,5,new QTableWidgetItem(QString::fromStdString(road_divider)));
            current_row++;
        }
        fileIn.close();
    }
}


void MainWindow::on_actionResetTable_triggered() //reseting data from vector
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this,"Reset data","You really want to reset all data?", QMessageBox::No | QMessageBox::Yes);

        if(reply == QMessageBox::Yes){
            ofstream fileOut;
            fileOut.open("Data/DataBase.txt");

            for (int i{0}; i < int(roads_data.size()); i++) {
                for (int j{0}; j<6; j++) {
                    fileOut << roads_data[i][j] << " ";
                }
                fileOut << "\n";
            }

            fileOut.close();
        }

        //set our table
        fill_table_from_txt();
}

void MainWindow::on_actionDeleteElement_triggered()
{
    ui->RoadData->removeRow(ui->RoadData->currentRow());
}
