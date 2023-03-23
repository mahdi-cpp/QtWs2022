#include "service/ResourceService.h"
#include "scene/Scene.h"
#include "scene/SceneProvider.h"
#include "service/ServiceManager.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QThread>

int main(int argc, char* argv[]) {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // Declare/Register all used custom QML elements
    SceneProvider::declareQml();
    Scene::declareQml();
    ResourceService::declareQml();

    QQmlApplicationEngine engine;

    ResourceService* resourceService = new ResourceService(&app);
    ServiceManager::getInstance().setResourceService(resourceService);            // Register service to our C++ singleton
    engine.rootContext()->setContextProperty("resourceService", resourceService); // Also set it to QML root context

    const QUrl url("/home/mahdi/CLionProjects/QtWs2022/qml/main.qml");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return QGuiApplication::exec();
}
