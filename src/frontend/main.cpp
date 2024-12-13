#include "Dimenvue.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//-window:1024x640 -debug

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Dimenvue app(argc, argv);

    Q_UNUSED(app.initialize());

    return app.exec();
}
