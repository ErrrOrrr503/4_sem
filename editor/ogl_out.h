#ifndef OGL_OUT_H
#define OGL_OUT_H

#include <QMouseEvent>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLFunctions_1_2> // riva tnt2

#include "sphere.h"

enum cur_cursor_type {
    plain,
    none
    //enum forbids equal enumenators for different enums? strange, errors could be given on type resolving when ambigious
};

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

    float cur_cursor_x;
    float cur_cursor_y;
    float pressed_cursor_x_raw;
    float pressed_cursor_y_raw;
    float center_x;
    float center_y;
    float old_center_x;
    float old_center_y;
    const float def_near = 100;
    const float def_far = 1100;
    const float def_z = 1000;
    float x_angle;
    float y_angle;
    float z_angle;
    cur_cursor_type cursor;

    sphere *S;
};

#endif // OGL_OUT_H
