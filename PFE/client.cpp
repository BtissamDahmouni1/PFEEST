#include "client.h"
#include <QDebug>

Client::Client(QObject *parent)
    : QObject(parent)
{}
/*
void Client::connect() {
    socket = new QTcpSocket(this);

    // Établir une connexion
    socket->connectToHost("localhost", 1234);

    // Tester la connexion (pendant 3 secondes)
    if (socket->waitForConnected(3000)) {
        qDebug() << "Connected......";

        // Envoyer des données
        socket->write("hello server\n");
        socket->waitForBytesWritten(1000);

        // Lire la réponse du serveur
        if(socket->waitForReadyRead(3000)) {
            qDebug() << "Reading";
            qDebug() << socket->readAll();
        } else {
            qDebug() << "Error: No response from server.";
        }

        socket->close();
    } else {
        qDebug() << "Not connected";
    }
}
*/
void  Client::teste(){
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    //pour savoir si il ya une information prete a lire
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64 bytes)),this,SLOT(bytesWritten(qint64 bytes)));
    qDebug() << "Connecting";
    socket->connectToHost("localhost", 1234);
    if (!socket->waitForConnected(3000)) {
        qDebug() << "Error: "<<socket->errorString();
    }
}

void  Client::connected(){
    qDebug() << "connected..";
    socket->write("hello server\n");
}
void  Client:: disconnected(){
    qDebug() << "disconnected..";
}
void  Client:: bytesWritten(qint64 bytes)//apeler lorsque les donne sont  ecris sur le socket
{
    qDebug() << "we wrote . "<<bytes;
}
void  Client:: readyRead(){
    qDebug() << "reading ....";
    qDebug() << socket->readAll();
}
