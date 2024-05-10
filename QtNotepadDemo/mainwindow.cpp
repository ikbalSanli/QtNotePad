#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream> //başlık dosyası
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrinter>
#include <QPrintDialog>
//kaydet diyince dosya yolunu bulamıyor ve arka plan rengi değişmiyor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);//kenardaki boşlukları falan aldık
}

MainWindow::~MainWindow()
{
    delete ui;
}
//.h ta tanımlıyoruz
void MainWindow::on_actionNew_triggered()
{
    file_path =" ";//boş diziye ayarlancak biri yeni bir dosya olusturunca veya new e tıklyınca//dosya yolu kesilcek ve yazdıgım metni sıfırlıyoruz
    ui->textEdit->setText(" ");


}
void MainWindow::on_actionOpen_triggered()
{
    QString file_name =QFileDialog::getOpenFileName(this,"open this file");//parent,baslık,varsayılan konum,filtre
    QFile file(file_name);//nesneyi çağırdık
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream in (&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "file not open " );
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}



void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();

}


void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString about_text;
    about_text="Auther:somebody\n";
    about_text+="Date:26/04/2024\n";
    about_text+="(C) Notepad (R)\n";

    QMessageBox::about(this,"About Notepad (R)",about_text);
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name =QFileDialog::getSaveFileName(this,"open this file");//Dosya adını kaydettik//parent,baslık,varsayılan konum,filtre
    QFile file(file_name);//nesneyi çağırdık
    file_path=file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out (&file);
    QString text=ui->textEdit->toPlainText();//akıştan metini almak yerine metinden metni alcaz
    out<<text;
    file.flush();//temizle
    file.close();//kapat
}


void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font =QFontDialog::getFont(&ok,this);
    if(ok){
        ui->textEdit->setFont(font);
    }else return ;
}


void MainWindow::on_actionColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"choose Color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}


void MainWindow::on_actionBackgroundcolor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"choose Color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void MainWindow::on_actionBackgrouncolor_Edit_Text_triggered()
    {
    QColor color=QColorDialog::getColor(Qt::white,this,"choose Color");
    if(color.isValid()){
        ui->textEdit->setPalette(QPalette(color));
    }

    }


    void MainWindow::on_actionPrint_triggered()//proya eklemek gerek
    {
        QPrinter printer;
        printer.setPrinterName(" Printer name:Brother HL-110");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()==QDialog::Rejected)return;//reddedilirse return etsin
        ui->textEdit->print(&printer);
    }

