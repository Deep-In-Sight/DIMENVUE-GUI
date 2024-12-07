#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include "Dimenvue.h"

//-window:1024x640 -debug

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Dimenvue app(argc, argv);

    Q_UNUSED(app.initialize());

    return app.exec();
}
