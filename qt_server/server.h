#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class server; }
QT_END_NAMESPACE

class server : public QMainWindow
{
    Q_OBJECT

public:
    server(QWidget *parent = nullptr);
    ~server();

private:
    Ui::server *ui;
    QTcpServer *Server;
    QTcpSocket *Socket;
private slots:
    void Listen();
    void send();
    void newConnect();
    void Read_data();
    void DisConnect();

};
#endif // SERVER_H
