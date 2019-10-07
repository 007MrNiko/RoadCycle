#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/Pictures/Data/Pictures/ProgramIcon.png"));

    setWindowTitle("RoadCycle");

    mkdir("Data"); //create directory for files
    fill_table_from_txt();
    ui->RoadData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // make table look nice)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fill_table_from_txt()
{
    string road_name, road_type, road_pavement, road_divider, temp_line;
    double road_length;
    int road_lines;
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

            auto road_length_converted = new QTableWidgetItem; // conversion special for sorting data is not string!
            road_length_converted->setData(Qt::EditRole,road_length);
            ui->RoadData->setItem(current_row,2,road_length_converted);

            auto road_lines_converted = new QTableWidgetItem;
            road_lines_converted->setData(Qt::EditRole,road_lines);
            ui->RoadData->setItem(current_row,3,road_lines_converted);

            ui->RoadData->setItem(current_row,4,new QTableWidgetItem(QString::fromStdString(road_pavement)));
            ui->RoadData->setItem(current_row,5,new QTableWidgetItem(QString::fromStdString(road_divider)));
            current_row++;
        }
        fileIn.close();
    }
    fileIn_to_count.close();
}


void MainWindow::on_actionResetTable_triggered() //reseting data from vector
{
    QApplication::beep();
    QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this,"Відновити дані","Ви дійсно бажаєте відновити дані до початкових?", QMessageBox::No | QMessageBox::Yes);

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
    QMessageBox::StandardButton delete_data;
    delete_data = QMessageBox::critical(this,"Видалити рядок","Ви дійсно бажаєте безповоротно видалити цей рядок?", QMessageBox::No | QMessageBox::Yes);

    if(delete_data == QMessageBox::Yes){

        QTableWidgetItem* theItem = ui->RoadData->item(ui->RoadData->currentRow(), 0);

        string road_name_to_delete = theItem->text().toUtf8().constData(); //take our road name to delete right line from txt

        ifstream roads("Data/DataBase.txt");
        ofstream temp("Data/Temp.txt");

        string road_name, road_type, road_length, road_lines, road_pavement, road_divider;

        while(roads >> road_name >> road_type >> road_length >> road_lines >> road_pavement>> road_divider)
            {
                if(road_name_to_delete!=road_name){ // write data to Temp.txt our without delete line
                    temp << road_name << " "
                         << road_type << " "
                         << road_length << " "
                         << road_lines << " "
                         << road_pavement << " "
                         << road_divider << "\n";
                    }
            }

        roads.close();
        temp.close();
        remove("Data/DataBase.txt");
        rename("Data/Temp.txt","Data/DataBase.txt");

        fill_table_from_txt();
        //ui->RoadData->removeRow(ui->RoadData->currentRow());
    }
}

void MainWindow::on_actionAscendingSortColumn_triggered()
{
    ui->RoadData->sortItems(ui->RoadData->currentColumn(), Qt::AscendingOrder);
}

void MainWindow::on_actionDescendingSortColumn_triggered()
{
    ui->RoadData->sortItems(ui->RoadData->currentColumn(), Qt::DescendingOrder);
}

void MainWindow::on_actionAddElement_triggered()
{
    int result{};
    DialogAddItem addItem(this);    //creating dialog window
    addItem.setWindowTitle("Додати дорогу");
    result = addItem.exec();

    string road_name = addItem.road_name().toUtf8().constData();
    string road_type = addItem.road_type().toUtf8().constData();
    double road_length = addItem.road_length();
    string road_lines = addItem.road_lines().toUtf8().constData();
    string road_pavement = addItem.road_pavement().toUtf8().constData();
    string road_divider = addItem.road_divider().toUtf8().constData();

    if (result == QDialog::Accepted){
        ofstream fileout ("Data/DataBase.txt",ios::app); //adding data to our txt

        fileout << road_name << " "
                << road_type << " "
                << road_length << " "
                << road_lines << " "
                << road_pavement << " "
                << road_divider << "\n";

        fileout.close();
    }

    fill_table_from_txt(); //fill our table
}

void MainWindow::on_actionDeleteAllElement_triggered()
{
    QApplication::beep();
    QMessageBox::StandardButton delete_data;
    delete_data = QMessageBox::critical(this,"Обнулити таблицю","Ви дійсно бажаєте безповоротно видалити таблицю?", QMessageBox::No | QMessageBox::Yes);

    if(delete_data == QMessageBox::Yes){
        ofstream reset_file;
        reset_file.open("Data/DataBase.txt", ios::trunc); //small cheat to clean file :)
        reset_file.close();
        fill_table_from_txt();
    }
}

void MainWindow::on_actionOpenNewFile_triggered()
{
    QApplication::beep();
    QMessageBox::StandardButton rewrite_data;
    rewrite_data = QMessageBox::warning(this,"Перезаписати таблицю","Ви дійсно бажаєте перезаписати таблицю?\nВаші теперешні дані буде втрачено", QMessageBox::No | QMessageBox::Yes);

    if(rewrite_data == QMessageBox::Yes){
        QString filter = "All File (*.*) ;; Text File (*.txt)";
        QString opened_file = QFileDialog::getOpenFileName(this,"Open a file", QDir::homePath(), filter);

        if(opened_file == ""){
            return;
        }

        ofstream our_data_base;
        ifstream chosen_data_base;

        our_data_base.open("Data/DataBase.txt", ios::trunc); //cleaning our
        chosen_data_base.open(opened_file.toUtf8().constData());

        string road_name, road_type, road_length, road_lines, road_pavement, road_divider;

        while(chosen_data_base >> road_name >> road_type >> road_length >> road_lines >> road_pavement>> road_divider)
            {
                our_data_base << road_name << " "
                              << road_type << " "
                              << road_length << " "
                              << road_lines << " "
                              << road_pavement << " "
                              << road_divider << "\n";

            }

        our_data_base.close();
        chosen_data_base.close();

    }

    fill_table_from_txt();
}

void MainWindow::on_actionFirstTask_triggered()
{
    taskOutput outputTask(this);    //creating dialog window
    outputTask.setWindowTitle("Перше завдання");
    outputTask.output_task_1();
    outputTask.exec();
}

void MainWindow::on_actionSecondTask_triggered()
{
    taskOutput outputTask(this);    //creating dialog window
    outputTask.setWindowTitle("Друге завдання");
    outputTask.output_task_2();
    outputTask.exec();
}

void MainWindow::on_actionThirdTask_triggered()
{
    taskOutput outputTask(this);    //creating dialog window
    outputTask.setWindowTitle("Третє завдання");
    outputTask.output_task_3();
    outputTask.exec();
}

void MainWindow::on_actionFourthTask_triggered()
{
    taskOutput outputTask(this);    //creating dialog window
    outputTask.setWindowTitle("Четверте завдання");
    outputTask.output_task_4();
    outputTask.exec();
}
