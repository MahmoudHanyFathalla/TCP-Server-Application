#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a TCP server
    tcpServer = new QTcpServer(this);

    // Start listening to incoming connections on port 1234
    if (!tcpServer->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Error: Unable to start the server";
        return;
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::newConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    // A new connection is available
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    if (!clientSocket) {
        qDebug() << "Error: Unable to accept incoming connection";
        return;
    }

    // Handle the new connection
    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::readData);
}

void MainWindow::readData()
{
    // Read data from the client socket
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) {
        qDebug() << "Error: Unable to read data from client";
        return;
    }

    // Read the data from the socket
    QByteArray data = clientSocket->readAll();
    qDebug() << "Received data:" << data;

    // Here you can process the received data or respond to the client
}
