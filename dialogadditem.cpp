#include "dialogadditem.h"
#include "ui_dialogadditem.h"

DialogAddItem::DialogAddItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddItem)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Pictures/Data/Pictures/AddButton.png"));
}

DialogAddItem::~DialogAddItem()
{
    delete ui;
}

void DialogAddItem::on_enterButton_clicked()
{
    if(ui->roadName->text().isEmpty()==true){
        QApplication::beep();
        QMessageBox::warning(this,"Увага!","Дорога повинна містити назву!");
    }
    else if(ui->roadLength->value() == 0.0){
        QApplication::beep();
        QMessageBox::warning(this,"Увага!","Дорога повнна мати відстань!");
    }
    else {
       accept();
    }
}

QString DialogAddItem::road_name() const{
    return ui->roadName->text();
}
QString DialogAddItem::road_type() const{
    return ui->roadType->currentText();
}
double DialogAddItem::road_length() const{
    return  ui->roadLength->value();
}
QString DialogAddItem::road_lines() const{
    return ui->roadLines->currentText();
}
QString DialogAddItem::road_pavement() const{
    return ui->roadPavement->currentText();
}
QString DialogAddItem::road_divider() const{
    return ui->roadDivider->currentText();
}
