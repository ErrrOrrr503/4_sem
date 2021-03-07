#include "ogl_out.h"

oGL_out::oGL_out(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat ogl_format;
    QSurfaceFormat::setDefaultFormat(ogl_format);
    setFormat(ogl_format);
}

oGL_out::~oGL_out()
{

}

void oGL_out::self_cursor()
{

}

void oGL_out::initializeGL()
{
    context = QOpenGLContext::currentContext();
    f = context->functions();
    f->initializeOpenGLFunctions();
    f30 = context->versionFunctions<QOpenGLFunctions_3_0>();
    f30->initializeOpenGLFunctions();
    f30->glMatrixMode(GL_PROJECTION);
    std::string console;
    emit print_console("ogl init");
}

void oGL_out::resizeGL(int nWidth, int nHeight)
{
    f30->glMatrixMode(GL_PROJECTION);
    std::string console = "ogl resize:";
    console += " new x = " + std::to_string(nWidth);
    console += " new y = " + std::to_string(nHeight);
    emit print_console(console);
}

void oGL_out::paintGL()
{
    f30->glClearColor(0.0, 1.0, 0.0, 0.0);
    f30->glColor3f(1.0, 0.0, 1.0);
    f30->glLineWidth(2);
    f30->glBegin(GL_TRIANGLES);
    f30->glVertex2f(0.5, 0.5);
    f30->glVertex2f(0.5, -0.5);
    f30->glVertex2f(-0.5, 0.5);
    f30->glVertex2f(-0.5, -0.5);
    f30->glVertex2f(0.5, -0.5);
    f30->glVertex2f(-0.5, 0.5);
    f30->glEnd();
    context->swapBuffers(context->surface());
}

void oGL_out::keyPressEvent(QKeyEvent *ke)
{

}

void oGL_out::mouseMoveEvent(QMouseEvent *me)
{

}

void oGL_out::mousePressEvent(QMouseEvent *me)
{

}

void oGL_out::mouseReleaseEvent(QMouseEvent *me)
{

}
