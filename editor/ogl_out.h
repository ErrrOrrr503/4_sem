#ifndef OGL_OUT_H
#define OGL_OUT_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_2_1>

class oGL_out : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit oGL_out(QWidget *parent = nullptr);
    ~oGL_out();
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

private:
    void self_cursor();

private slots:
    void keyPressEvent(QKeyEvent *ke);
    void mouseMoveEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);

signals:
    void print_console (const std::string &s);

private:
    QOpenGLFunctions *f;
    QOpenGLFunctions_3_0 *f30;
    QOpenGLContext *context;
};

#endif // OGL_OUT_H
