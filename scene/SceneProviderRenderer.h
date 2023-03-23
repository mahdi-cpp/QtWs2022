#pragma once

#include "service/ResourceService.h"

#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QQuickWindow>

//!
//! \brief The BackgroundRenderRenderer class
//! This class does the actual rendering directed by SceneProvider on the render thread
//!
class SceneProviderRenderer : public QObject, public QOpenGLFunctions {
    Q_OBJECT
public:
    explicit SceneProviderRenderer(QObject* parent = nullptr);
    ~SceneProviderRenderer();

    QOpenGLFramebufferObject* scene() const;

public slots:
    void init(QQuickWindow* window, const QSize& resolution);
    void setupRendering();
    void synchronize();
    void render();
    void cleanup();

private:
    // Here we will store all the rendered framebuffers, for this demo, we will just store one
    // But BackgroundRenderRender can be easily extended to render many scenes
    QOpenGLFramebufferObject* m_scene = nullptr;

    // Necessary OpenGL objects for rendering scene
    QOpenGLVertexArrayObject* m_vao = nullptr;
    QOpenGLBuffer* m_vertexBuffer   = nullptr;
    QOpenGLBuffer* m_elementBuffer  = nullptr;
    QOpenGLShaderProgram* m_program = nullptr;
    QOpenGLTexture* m_texture       = nullptr;
    QMatrix4x4 m_matrixModel;
    QMatrix4x4 m_matrixView;
    QMatrix4x4 m_matrixProjection;
    bool m_init = false;

    QQuickWindow* m_window = nullptr;

    ResourceService* m_resourceService = nullptr;
};
