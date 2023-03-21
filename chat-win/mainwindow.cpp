#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QMessageBox>
#include <QHostAddress>
#include <QInputDialog>
#include <sstream>
#include <QPalette>
#include "../xpack/json.h"
using namespace std;
QString nick;
struct mes_socket
{
    string nick;
    string text;
    XPACK(O(nick,text));
}mes;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSocket=NULL;
    tcpSocket=new QTcpSocket(this);
    //连接完成槽函数
    connect(tcpSocket,&QTcpSocket::connected,[=]()
    {
        QMessageBox::about(0,"连接","已连接到服务器");
        //禁用连接按钮
        ui->actionconnect->setEnabled(false);
    }
    );

    //断开连接槽函数
    connect(tcpSocket,&QTcpSocket::disconnected,[=]()
    {
        ui->actionconnect->setEnabled(true);
        ui->textBrowser->clear();
        QMessageBox::about(0,"连接","已断开连接");
        //使连接按钮可用

    }
    );

    //收到信息槽函数
    connect(tcpSocket,&QTcpSocket::readyRead,[=]()
    {

        //json转c++结构体
        mes_socket buf;
        QString mes=tcpSocket->readAll();
        if (mes[0]=='{')
        {
             string buf_st=mes.toStdString();
             xpack::json::decode(buf_st,buf);
             ui->textBrowser->append("<font color=blue>"+QString::fromStdString(buf.nick)+
                                     "</font>"+":"+"<font color=black>"+
                                     QString::fromStdString(buf.text)+"</font>");
        }
    }
    );
}

MainWindow::~MainWindow()
{
    delete ui;

}
//发送消息
void MainWindow::on_pushButton_clicked()
{

    QString buf=ui->textBrowser_2->toPlainText();
    mes.text=buf.toStdString();
    mes.nick=nick.toStdString();
    string mes_json=xpack::json::encode(mes);
    tcpSocket->write(QString::fromStdString(mes_json).toUtf8().data());
    ui->textBrowser_2->clear();
}

void MainWindow::on_textBrowser_textChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}


//连接服务器槽函数
void MainWindow::on_actionconnect_triggered()
{
    tcpSocket->connectToHost(QHostAddress("81.68.123.231"),22516);
}

void MainWindow::on_actionunconnect_triggered()
{
    ui->textBrowser->clear();
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}



void MainWindow::on_actionnick_triggered()
{
    bool ok;
    nick=QInputDialog::getText(this,"昵称","设置昵称",QLineEdit::Normal,"坤坤",&ok);
    if(ok&&!nick.isEmpty())
    {
        ui->pushButton->setEnabled(true);
        ui->pushButton->setToolTip("");
    }
}

void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(0,"关于","版权所有：516\nQQ群:597256319");
}
