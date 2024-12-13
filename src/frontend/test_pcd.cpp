#include <ImGuiItem.h>
#include <OverlayDrawer.h>
#include <PointCloudItem.h>
#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImGuiItem>("DimenvueComponents", 1, 0, "ImGuiItem");
    qmlRegisterType<PointCloudItem>("DimenvueComponents", 1, 0, "OpenGLItem");

    const QUrl url("qrc:/qml/testpcd/main.qml");
    QQuickView *view = new QQuickView();
    view->setSource(url);
    view->setResizeMode(QQuickView::SizeRootObjectToView); // Ensures root object resizes with the view
    auto overlayItem = view->rootObject()->findChild<ImGuiItem *>();
    auto overlay = new OverlayDrawer(overlayItem);
    view->show();

    app.exec();
}