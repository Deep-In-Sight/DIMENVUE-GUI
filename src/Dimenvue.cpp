#include "Dimenvue.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QScreen>
#include <QFontDatabase>
#include <QTranslator>
#include "DimenvueDB.h"
#include "Hangul.h"
#include "SpaceDataModel.h"
#include "SpaceDataSortProxyModel.h"
#include "LanguageTranslationModel.h"
#include "BackendMonitor.h"
#include <QDateTime>

//=============================================================================
//  P R I V A T E
//=============================================================================
class DimenvuePrivate
{
public:
    Dimenvue* q;

    DimenvuePrivate(Dimenvue* q)
        : q(q)
        , db(new DimenvueDB)
        , model(new SpaceDataModel)
        , proxyModel(new SpaceDataSortProxyModel)
        , translator(new QTranslator)
        , stringModel(new LanguageTranslationModel)
        , hangul(new Automata::Hangul)
    {}

    const int SCREEN_WIDTH = 2270;// 2560;
    const int SCREEN_HEIGHT = 1420;//1600;

    int windowWidth = SCREEN_WIDTH;
    int windowHeight = SCREEN_HEIGHT;
    float scale = 1.0f;
    float bgOpacity = 0.6f;
    bool fullscreen = true;
    bool hasKeyboardDevice = false;
    bool debugMode = false;
    int devation = 1;

    QQmlApplicationEngine engine;
    QScopedPointer<DimenvueDB> db;
    QScopedPointer<SpaceDataModel> model;
    QScopedPointer<SpaceDataSortProxyModel> proxyModel;
    QScopedPointer<QTranslator> translator;
    QScopedPointer<LanguageTranslationModel> stringModel;
    QObject* qmlKeyboard = nullptr;
    QObject* qmlRoot = nullptr;
    QScopedPointer<Automata::Hangul> hangul;

    bool parseWindowOption(int argc, char** argv)
    {
        if (1 < argc) {
            for (int i=1; i<argc; i++) {
                auto param = QString{argv[i]};
                if (param.startsWith("-window:")) {
                    auto sl = param.split(":");
                    if (1 < sl.size()) {
                        auto sizes = sl[1].split("x");
                        if (1 < sizes.size()) {
                            bool ok;
                            auto w = sizes[0].toInt(&ok);
                            auto h = sizes[1].toInt(&ok);
                            if (w && h) {
                                windowWidth = w;
                                windowHeight = h;
                                fullscreen = false;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    bool parseDebugOption(int argc, char** argv) {
        for (auto i=1; i<argc; i++) {
            auto param = QString{argv[i]};
            if (param.startsWith("-debug")) {
                debugMode = true;
                return true;
            }
        }
        return false;
    }
    bool startEngine()
    {
        const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         q, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        proxyModel->setSourceModel(model.data());

        auto* rootContext = engine.rootContext();
        rootContext->setContextProperty("db", db.get());
        rootContext->setContextProperty("monitor", QVariant::fromValue(db->monitorObject()));
        rootContext->setContextProperty("app", QVariant::fromValue(q));
        rootContext->setContextProperty("spaceModel", QVariant::fromValue(model.get()));
        rootContext->setContextProperty("proxyModel", QVariant::fromValue(proxyModel.data()));
        rootContext->setContextProperty("debugMode", debugMode);
        rootContext->setContextProperty("blurDevation", devation);
        rootContext->setContextProperty("STRING", QVariant::fromValue(stringModel.data()));

        q->changeLanguage(-1);

        if (debugMode) {

            //pre update for testing.
            db->updateModelData(model.get());
        }

        return true;
    }
    bool updateContext()
    {
        auto roots = engine.rootObjects();
        if (roots.size()) {
            auto* window = engine.rootObjects().first();
            window->setProperty("width", windowWidth);
            window->setProperty("height", windowHeight);
            qDebug() << "window: " << windowWidth << "x" << windowHeight;

            float basicRatio = float(SCREEN_HEIGHT) / float(SCREEN_WIDTH);// 9.0/16.0;
            float ratio = windowHeight / float(windowWidth);
            float scale = 1.0;
            if (basicRatio < ratio) {
                scale = windowWidth / float(SCREEN_WIDTH);
            } else {
                scale = windowHeight / float(SCREEN_HEIGHT);
            }
            this->scale = scale;

            auto* root = window->findChild<QObject*>("root");
            if (root) {
                root->setProperty("scale", scale);
                qDebug() << "scale: " << scale;
                root->setProperty("fullscreen", fullscreen);
                root->setProperty("screenWidth", SCREEN_WIDTH);
                root->setProperty("screenHeight", SCREEN_HEIGHT);

                qmlRoot = root;
            } else {
                qDebug() << "[Error] can't find root !!!";
            }

            if (fullscreen) {
                qDebug() << "invoke window.showFullScreen()";
                QMetaObject::invokeMethod(window, "showFullScreen");
            }
        }

        return true;
    }
    void startApp() {
        qDebug() << "invoke root.start()";
        auto roots = engine.rootObjects();
        if (roots.size()) {
            auto* window = engine.rootObjects().first();
            auto* root = window->findChild<QObject*>("root");
            if (root) {
                QMetaObject::invokeMethod(root, "loadDimenvue");

                qmlKeyboard = root->findChild<QObject*>("keyboard");
                if (qmlKeyboard != nullptr) {
                    qDebug() << "[C++] find keyboard Object";
                }
            }
        }
    }
    bool initFonts() {
        auto fonts = QStringList {
            "Black",
            "Bold",
            "ExtraBold",
            "ExtraLight",
            "Light",
            "Medium",
            "Regular",
            "SemiBold",
            "Thin"
        };
        for (auto font : fonts) {
            auto fontPath = QString{"fonts/Pretendard-%1.otf"}.arg(font);
            auto ret = QFontDatabase::addApplicationFont(fontPath);
            if (-1 == ret) {
                qDebug() << fontPath << " load failed.";
                return false;
            }
        }
        qDebug() << fonts.size() << " fonts loaded successfully.";
        return true;
    }
    bool initModel() {
        SpaceDataModel::registToQml();

#ifdef QT_DEBUG
        auto date = QDate{2024, 11, 11};
        auto time = QTime{10, 0, 0};
        auto url = QUrl{"qrc:/resources/images/rectangle_108.png"};
        constexpr int TEST_DATA_COUNT = 10;

        srand(0);

        for (auto i=0; i<TEST_DATA_COUNT; i++) {
            auto index = rand() % 1000;
            auto area = float(rand() % 10000) / 100.0f;
            auto atime = time.addSecs(60*(rand() % 1000));

            auto name = QString{"Name%1"}.arg(index);            
            //model->append(i, name, url, area, QDateTime(date, atime));
        }
#endif
        return true;
    }

    void removeChecked() {
        auto list = model->checkedItems();

        db->remove(list);

        //model->removeChecked();
    }
};

//=============================================================================
//  PUBLIC
//=============================================================================
Dimenvue::Dimenvue(int& argc, char** argv)
    : QGuiApplication(argc, argv)
    , d(new DimenvuePrivate(this))
{
    auto* screen = screens().first();

    if (!d->parseWindowOption(argc, argv)) {
        if (screen) {
            auto geom = screen->geometry();
            d->windowWidth = geom.width();
            d->windowHeight = geom.height();
            d->fullscreen = true;
        }
    }
    d->parseDebugOption(argc, argv);
}

Dimenvue::~Dimenvue()
{}

bool Dimenvue::initialize()
{
    d->initFonts();
    d->initModel();
    d->startEngine();
    d->updateContext();

    d->startApp();

    return true;
}

void Dimenvue::showKeyboard()
{
    if (!d->hasKeyboardDevice) {
        if (nullptr == d->qmlKeyboard) {

        }
        d->qmlKeyboard->setProperty("visible", true);
    }
}

void Dimenvue::hideKeyboard()
{
    if (d->qmlKeyboard) {
        d->qmlKeyboard->setProperty("visible", false);
    }
}

void Dimenvue::inputHangulKey(QString s)
{
    if (d->hangul) {
        QChar ch = s.at(0);
        char c = ch.toLatin1();
        d->hangul->Input(c);
        auto text = d->hangul->getText();
        qDebug() << "[Hangul] " << c << " -> " << text;

        emit keyboardTextUpdated(text);
    }
}

void Dimenvue::inputNoHangulKey(QString s)
{
    if (d->hangul) {
        QChar ch = s.at(0);
        char c = ch.toLatin1();
        d->hangul->InputNoKorea(c);
        auto text = d->hangul->getText();
        qDebug() << "[No Hangul] " << c << text;

        emit keyboardTextUpdated(text);
    }
}

void Dimenvue::inputBackspace()
{
    if (d->hangul) {
        d->hangul->BackKeyProc();
        auto text = d->hangul->getText();
        qDebug() << "[ <- ] " << text;

        emit keyboardTextUpdated(text);
    }
}

void Dimenvue::inputInit(const QString& text)
{
    if (d->hangul) {
        d->hangul->setText(text);
    }
}

void Dimenvue::changeLanguage(int lang)
{
    QString path = ":/resources/localization/";
    if (0 == lang) {
        path += "Dimenvue_ko.qm";
    } else {
        path += "Dimenvue_en-us.qm";
    }
    if (d->translator->load(path)) {
        installTranslator(d->translator.data());

        if (d->stringModel) {
            qDebug() << "[C++] STRING.languageChanged";

            QMetaObject::invokeMethod(d->stringModel.data(), "languageChanged");
        }
    } else {
        qDebug() << path << " load failed!";
    }
    d->db->setLanguage(lang);
    d->db->updateTime();
}

void Dimenvue::setSortRole(int role, int order)
{
    d->proxyModel->setSortRole(role);
    d->proxyModel->sort(0, Qt::SortOrder(order));
}

void Dimenvue::removeChecked()
{
    d->removeChecked();
}

void Dimenvue::uploadChecked()
{
    auto list = d->model->checkedItems();

    d->db->uploadCheckedView(list);
}

void Dimenvue::loadScanComplete()
{
    auto roots = d->engine.rootObjects();
    if (roots.size()) {
        auto* window = d->engine.rootObjects().first();
        auto* scanMain = window->findChild<QObject*>("scanMain");
        if (scanMain) {
            QMetaObject::invokeMethod(scanMain, "load", Q_ARG(QVariant, QUrl("qrc:/qml/scan/ScanComplete.qml")));
        }
    }
}

void Dimenvue::openMap(int index)
{
    auto scanView = d->model->getView(index);
    if (scanView) {
        d->db->setCurrentView(scanView);
    }
}

float Dimenvue::globalScale() const
{
    float value = d->scale;

    qDebug() << "Dimenvue::scale(): " << value;

    return value;
}
