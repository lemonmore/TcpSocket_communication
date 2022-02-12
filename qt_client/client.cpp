#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QtNetwork>
#include <QThread>


client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{

    ui->setupUi(this);
    ui->Ip->setText("127.0.0.1");
    ui->Port->setText("2770");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(connection()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(send()));
}

client::~client()
{
    delete ui;
}
void client::connection(){
    Socket = new QTcpSocket(this);
        QString ip = ui->Ip->text();
      //  int port = ui->Port->text().toInt();
        Socket->connectToHost(QHostAddress("127.0.0.1"), 2770);
        if(!Socket->waitForConnected(30000))
        {
            QMessageBox::warning(this, "warning", "连接服务端失败！");
            return;
        }
        QMessageBox::information(this,"Qt","success!");
         connect(Socket, SIGNAL(readyRead()), this, SLOT(read_data()));
}
void client::send(){
    //获取TextEdit控件中的内容
       QString data=ui->send->toPlainText().toUtf8();
       QByteArray ba=data.toLocal8Bit();
       int sendRe = Socket->write(ba);
       bool bools=Socket->flush();
       if(sendRe == -1&&bools!=1)
       {
            QMessageBox::information(this, "QT网络通信", "向服务端发送数据失败！");
            return;
       }
       ui->listWidget->addItem(QString(ui->send->toPlainText()).toLocal8Bit());
       ui->send->clear();


}
void client::read_data(){
            QByteArray array;
            array.resize(Socket->bytesAvailable());//根据可读数据来设置空间大小
            array=Socket->readLine();
            ui->listWidget->addItem("【服务端】："+array);


}
