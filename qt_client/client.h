#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private:
    Ui::client *ui;
private slots:
    void connection();
    void send();
    void read_data();
private:
    QTcpSocket *Socket;
};
#endif // CLIENT_H
