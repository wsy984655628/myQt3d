#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQmlAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QQmlContext>
#include <QWindow>
#include <QScreen>
#include <QString>
#include <QOpenGLContext>

class View3D: public QWindow
{
public:
    View3D(QScreen* targetScreen = Q_NULLPTR):QWindow(targetScreen)
    {
        setSurfaceType(QSurface::OpenGLSurface);
        QSurfaceFormat format;
        if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
            format.setVersion(4, 3);
            format.setProfile(QSurfaceFormat::CoreProfile);
        }
        format.setDepthBufferSize( 24 );
        format.setSamples( 4 );
        format.setStencilBufferSize(8);
        setFormat(format);
        create();
    }
};

Settings::Settings(QObject *parent):QObject(parent)
{
    pitch = 0.0;
}
void Settings::setPitch(float Pitch)
{
    if(pitch == Pitch) return;
    pitch = Pitch;
    emit PitchChanged();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    using namespace Qt3D;
    using namespace Qt3D::Quick;

    View3D* view3D = new View3D;
    //View3D view3D;
    QQmlAspectEngine* engine = new QQmlAspectEngine(this);
    engine->aspectEngine()->registerAspect(new QRenderAspect);
    engine->aspectEngine()->registerAspect(new QInputAspect);

    QVariantMap data;
    data.insert(QStringLiteral("surface"),
                QVariant::fromValue(static_cast<QSurface*>(view3D)));
    data.insert(QStringLiteral("eventSource"),
                QVariant::fromValue(view3D));
    engine->aspectEngine()->setData(data);

    engine->qmlEngine()->rootContext()->setContextProperty("_settings",&m_settings);

    engine->aspectEngine()->initialize();
    engine->setSource(QUrl("qrc:/qml/main.qml"));

    QVBoxLayout* l = qobject_cast<QVBoxLayout*>( ui->centralwidget->layout( ) );
    l->insertWidget(0,QWidget::createWindowContainer(view3D));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalScrollBar_sliderMoved(int position)
{
    m_settings.setPitch(position);
}
