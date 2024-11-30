#include <QGuiApplication>
#include <QQuickView>
#include <QOgreItem.h>
#include <ImGuiItem.h>
#include <OverlayDrawer.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QOgreItem>("OgreComponents", 1, 0, "QOgreItem");
    qmlRegisterType<ImGuiItem>("OgreComponents", 1, 0, "ImGuiItem");

    const QUrl url("qrc:/main.qml");
    QQuickView *view = new QQuickView();
    view->setSource(url);
    view->setResizeMode(QQuickView::SizeRootObjectToView); // Ensures root object resizes with the view
    auto overlayItem = view->rootObject()->findChild<ImGuiItem *>();
    auto overlay = new OverlayDrawer(overlayItem);
    view->show();

    return app.exec();
}
