#include <ImGuiItem.h>
#include <OpenGLItem.h>
#include <OverlayDrawer.h>
#include <QGuiApplication>
// #include <QOgreItem.h>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // qmlRegisterType<QOgreItem>("OgreComponents", 1, 0, "QOgreItem");
    qmlRegisterType<ImGuiItem>("OgreComponents", 1, 0, "ImGuiItem");
    qmlRegisterType<OpenGLItem>("OgreComponents", 1, 0, "OpenGLItem");

    QSurfaceFormat format;
    format.setSwapInterval(0); // disable vsync
    QSurfaceFormat::setDefaultFormat(format);

    const QUrl url("qrc:/main.qml");
    QQuickView *view = new QQuickView();
    view->setSource(url);
    view->setResizeMode(QQuickView::SizeRootObjectToView); // Ensures root object resizes with the view
    auto overlayItem = view->rootObject()->findChild<ImGuiItem *>();
    auto overlay = new OverlayDrawer(overlayItem);
    view->show();

    return app.exec();
}
