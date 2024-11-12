#include <QGuiApplication>
#include <QQuickView>
#include <QOgreItem.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QOgreItem>("OgreComponents", 1, 0, "QOgreItem");

    const QUrl url("qrc:/main.qml");
    QQuickView *view = new QQuickView();
    view->setSource(url);
    view->show();

    return app.exec();
}
