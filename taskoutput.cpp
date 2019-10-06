#include "taskoutput.h"
#include "ui_taskoutput.h"

taskOutput::taskOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskOutput)
{
    ui->setupUi(this);
}

taskOutput::~taskOutput()
{
    delete ui;
}

void taskOutput::output_task_1(){

    ui->labelTask->setText("Найкоротша дорога, де найбільша кількість смуг");

    string road_name, road_type, road_pavement, road_divider, temp_line;
    double road_length;
    int road_lines;
    vector<double> min_element_vector{};

    ifstream fileIn ("Data/DataBase.txt");
    ifstream fileIn_to_count ("Data/DataBase.txt");

    if(fileIn_to_count.is_open()){
        while(fileIn_to_count >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_lines == 6){
                min_element_vector.push_back(road_length);
            }
        }
        fileIn_to_count.close();
    }

    ui->RoadData->setRowCount(1);

    double min_length = *min_element(min_element_vector.begin(), min_element_vector.end());

    if(fileIn.is_open()){
        while(fileIn >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_lines == 6 && road_length == min_length){
                ui->RoadData->setItem(0,0,new QTableWidgetItem(QString::fromStdString(road_name))); // row, column, item
                ui->RoadData->setItem(0,1,new QTableWidgetItem(QString::fromStdString(road_type)));

                auto road_length_converted = new QTableWidgetItem; // conversion special for sorting data is not string!
                road_length_converted->setData(Qt::EditRole,road_length);
                ui->RoadData->setItem(0,2,road_length_converted);

                auto road_lines_converted = new QTableWidgetItem;
                road_lines_converted->setData(Qt::EditRole,road_lines);
                ui->RoadData->setItem(0,3,road_lines_converted);

                ui->RoadData->setItem(0,4,new QTableWidgetItem(QString::fromStdString(road_pavement)));
                ui->RoadData->setItem(0,5,new QTableWidgetItem(QString::fromStdString(road_divider)));
            }
        }
        fileIn.close();
    }
}
void taskOutput::output_task_2(){
    ui->labelTask->setText("Всі дороги, в яких наявні розділювачі посередині,\nкількість смуг > 2 та згрупувати за типом");

    string road_name, road_type, road_pavement, road_divider, temp_line;
    double road_length;
    int road_lines;
    int amount_of_lines{0}, current_row{0};

    ifstream fileIn ("Data/DataBase.txt");
    ifstream fileIn_to_count ("Data/DataBase.txt");

    if(fileIn_to_count.is_open()){
        while(fileIn_to_count >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_lines > 2 && (road_divider == "так" || road_divider == "yes")){
                amount_of_lines++;
            }
        }
        fileIn_to_count.close();
    }

    ui->RoadData->setRowCount(amount_of_lines);


    if(fileIn.is_open()){
        while(fileIn >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_lines > 2 && (road_divider == "так" || road_divider == "yes")){
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
        }
        fileIn.close();
    }
    ui->RoadData->sortItems(1, Qt::AscendingOrder);
}
void taskOutput::output_task_3(){
    ui->labelTask->setText("Типи автомобільних доріг, з найбільшою протяжністю\nта наявністю пішохідних доріжок");

    string road_name, road_type, road_pavement, road_divider, temp_line;
    double road_length;
    int road_lines;
    int current_row{0};

    vector<double> max_element_vector{};
    vector<string> road_type_vector{};

    ifstream fileIn ("Data/DataBase.txt");
    ifstream fileIn_to_count ("Data/DataBase.txt");

    if(fileIn_to_count.is_open()){
        while(fileIn_to_count >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_pavement == "так" || road_pavement == "yes"){
                max_element_vector.push_back(road_length);
            }
        }
        fileIn_to_count.close();
    }



    double max_length = *max_element(max_element_vector.begin(), max_element_vector.end());


    if(fileIn.is_open()){
        while(fileIn >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_length == max_length && (road_pavement == "так" || road_pavement == "yes")){

                if(std::find(road_type_vector.begin(), road_type_vector.end(), road_type) == road_type_vector.end()){ //check if road type is in vector
                    road_type_vector.push_back(road_type);
                }

                ui->RoadData->insertRow(ui->RoadData->rowCount()); //append row

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
        }
        fileIn.close();
    }
    ui->RoadData->sortItems(1, Qt::AscendingOrder);

    ui->labelTypes->setText("Типи доріг: ");

    for(auto element: road_type_vector){
        string temp = element + " ";
        ui->labelTypes->setText(ui->labelTypes->text() + QString::fromStdString(temp));
    }

}
void taskOutput::output_task_4(){
    ui->labelTask->setText("Автомобільні дороги з найбільшою кількістю смуг\nта наявними пішохідними доріжками,\nякі належать до регіональних");

    string road_name, road_type, road_pavement, road_divider, temp_line;
    double road_length;
    int road_lines;
    int amount_of_lines{0}, current_row{0};

    ifstream fileIn ("Data/DataBase.txt");
    ifstream fileIn_to_count ("Data/DataBase.txt");

    if(fileIn_to_count.is_open()){
        while(fileIn_to_count >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_lines == 6 && (road_type == "регіональна" || road_type == "regional") && (road_pavement == "так" || road_pavement == "yes")){
                amount_of_lines++;
            }
        }
        fileIn_to_count.close();
    }

    ui->RoadData->setRowCount(amount_of_lines);


    if(fileIn.is_open()){
        while(fileIn >> road_name >> road_type >> road_length >> road_lines >> road_pavement >> road_divider){
            if(road_lines == 6 && (road_type == "регіональна" || road_type == "regional") && (road_pavement == "так" || road_pavement == "yes")){
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
        }
        fileIn.close();
    }
    ui->RoadData->sortItems(2, Qt::AscendingOrder);
}

