#include "server.h"
#include "ui_server.h"
#include <QMessageBox>


server::server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::server)
{
    ui->setupUi(this);
    ui->Port->setText("2770");
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Listen()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(send()));

}

server::~server()
{
    delete ui;
}

void server::Listen(){
        Server = new QTcpServer();
        //int port = ui->Port->text().toInt();
        if(!Server->listen(QHostAddress::Any, 2770))
        {
            QMessageBox::information(this, "QT网络通信", "服务器端监听失败！");
            return;
        }
        else
        {
            QMessageBox::information(this, "QT网络通信", "服务器监听成功！");
        }
        connect(Server, SIGNAL(newConnection()), this, SLOT(newConnect()));
}
void server::send(){
        qint64 writes=Socket->write(ui->textEdit->toPlainText().toLatin1());
        bool Bool=Socket->flush();
        if(writes==-1&&Bool!=1)
        {
            QMessageBox::warning(this, "QT网络通信", "发送数据失败，请重新发送！");
            return;
        }
        ui->listWidget->addItem(QString(ui->textEdit->toPlainText()).toLocal8Bit());
        ui->textEdit->clear();
}
void server::Read_data(){
    QByteArray array;
    array.resize(Socket->bytesAvailable());//根据可读数据来设置空间大小
    array=Socket->readLine();
    ui->listWidget->addItem("【客户端】："+array);
}
void server::newConnect(){
    Socket=Server->nextPendingConnection();
    if(!Socket){
        QMessageBox::warning(this, "warning", "未正确获取客户端连！");
               return;
           }
           else
           {
               QMessageBox::information(this, "QT网络通信", "成功接受客户端的连接");
           connect(Socket, SIGNAL(readyRead()), this, SLOT(Read_data()));
               connect(Socket, SIGNAL(disconnected()), this, SLOT(DisConnect()));

    }
}
void server::DisConnect(){
    QMessageBox::information(this, "QT网络通信", "与客户端的连接断开");
        return;
}
