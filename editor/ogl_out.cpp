#include "ogl_out.h"

oGL_out::oGL_out(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat ogl_format;
    QSurfaceFormat::setDefaultFormat(ogl_format);
    setFormat(ogl_format);
    cur_cursor_x = 0;
    cur_cursor_y = 0;
    center_x = 0;
    center_y = 0;
    x_angle = 0;
    y_angle = 0;
    z_angle = 0;
    cursor = none;
    setFocusPolicy(Qt::ClickFocus);
}

oGL_out::~oGL_out()
{
    delete S;
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
    f30->glLoadIdentity();
    f30->glOrtho((float) -width() / 2, (float) width() / 2, (float) -height() / 2, (float) height() / 2, -1, 1);
    f30->glEnable(GL_MULTISAMPLE);
    std::string console = "ogl init: x = " + std::to_string(width()) + " y = " + std::to_string(height());
    emit print_console(console);
    console.clear();
    console = "ogl max x = " + std::to_string((float) width() / 2) + " y = " + std::to_string((float) height() / 2);
    emit print_console(console);
    S = new sphere(0, 0, 0, 400, 333, 333, f30);
}

void oGL_out::resizeGL(int nWidth, int nHeight)
{
    static int oWidth = 0, oHeight = 0;
    static float prev_angle;
    std::string console;
    if (nWidth == oWidth && nHeight  == oHeight && z_angle == prev_angle)
        console = "center moved: new x0 = " + std::to_string(center_x) + " new y0 = " + std::to_string(center_y);
    if (nWidth == oWidth && nHeight  == oHeight)
        console = "ogl resize: new x = " + std::to_string(nWidth) + " new y = " + std::to_string(nHeight);
    if (z_angle != prev_angle)
        console = "rotated: " + std::to_string(x_angle) + ", " + std::to_string(y_angle) + ", " + std::to_string(z_angle);
    emit print_console(console);
    console.clear();
    f30->glMatrixMode(GL_PROJECTION);
    f30->glLoadIdentity();
    //1 pixel is a basic value
    f30->glOrtho(center_x + ((float) -width() / 2), center_x + ((float) width() / 2),
                 center_y + ((float) -height() / 2), center_y + ((float) height() / 2),
                 -def_z, def_z);
    //f30->glFrustum(center_x + ((float) -width() / 2), center_x + ((float) width() / 2),
    //               center_y + ((float) -height() / 2), center_y + ((float) height() / 2),
    //               def_near, def_far);
    f30->glMatrixMode(GL_MODELVIEW);
    f30->glLoadIdentity();
    f30->glRotatef(x_angle, 1, 0, 0);
    f30->glRotatef(y_angle, 0, 1, 0);
    f30->glRotatef(z_angle, 0, 0, 1);
    //it is possible to use glTranslate here however... what for? center_xy are still needed

    oWidth = nWidth, oHeight  = nHeight;
}

void oGL_out::paintGL()
{
    f30->glPointSize(20);
    f30->glColor3f(0, 0.7, 0);
    f30->glEnable(GL_POINT_SMOOTH);
    f30->glLineWidth(1);
    S->draw();
    //section figures
    /*
    static GLfloat vertexes[] = {
        100, 100, 0,
        100, -100, 0,
        -100, 100, 0,
        -100, -100, 0
    };
    static GLfloat colors[] = {
        0.0, 0.0, 0,0,
        0.0, 1.0, 1,0,
        1.0, 1.0, 1,0,
        1.0, 1.0, 0,0,
    };
    f30->glClearColor(0.0, 1.0, 0.0, 0.0);
    f30->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    f30->glEnableClientState(GL_VERTEX_ARRAY);
    f30->glEnableClientState(GL_COLOR_ARRAY);
    f30->glColorPointer(3, GL_FLOAT, 0, colors);
    f30->glVertexPointer(3, GL_FLOAT, 0, vertexes);
    f30->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    */

    //section pointes (coord pointers == coord figures & pointers are displayed in human way)

    f30->glMatrixMode(GL_MODELVIEW);
    f30->glPushMatrix();
    glLoadIdentity();

    f30->glColor3f(0.5, 0.5, 0.5);
    f30->glEnable(GL_POINT_SMOOTH);
    f30->glBegin(GL_POINTS);
    f30->glVertex3f(0, 0, 0);
    f30->glVertex3f(center_x, center_y, 0);
    f30->glEnd();

    //What the... why does GL_QUADS and GL_POLYGON behave that way

    if (cursor != none) {
        f30->glPointSize(20);
        f30->glColor3f(1.0, 0.5, 0.0);
        f30->glBegin(GL_POINTS);
        f30->glVertex3f(cur_cursor_x, cur_cursor_y, 0);
        f30->glEnd();
    }

    glPopMatrix();

    context->swapBuffers(context->surface());
}

void oGL_out::keyPressEvent(QKeyEvent *ke)
{
    switch (ke->key()) {
    case Qt::Key_Right:
        z_angle++;
        //WHAT#@&#(*!_@ Why glROtate only works in resize()???
        break;
    case Qt::Key_Left:
        z_angle--;
        break;
    case Qt::Key_Up:
        x_angle--;
        break;
    case Qt::Key_Down:
        x_angle++;
        break;
    case Qt::Key_1:
        y_angle--;
        break;
    case Qt::Key_2:
        y_angle++;
        break;
    default:
        break;
    }
    QResizeEvent *myResizeEvent = new QResizeEvent(QSize(size()), QSize(size())); //call resize staff that places center where needed
    QCoreApplication::postEvent(this, myResizeEvent);
}

void oGL_out::mouseMoveEvent(QMouseEvent *me)
{
    cursor = plain;
    center_x = old_center_x - me->localPos().x() + pressed_cursor_x_raw;
    center_y = old_center_y + me->localPos().y() - pressed_cursor_y_raw;
    QResizeEvent *myResizeEvent = new QResizeEvent(QSize(size()), QSize(size())); //call resize staff that places center where needed
    QCoreApplication::postEvent(this, myResizeEvent);
}

void oGL_out::mousePressEvent(QMouseEvent *me)
{
    cursor = plain;
    cur_cursor_x = me->localPos().x() - (float) width() / 2 + center_x;
    cur_cursor_y = (float) height() / 2 - me->localPos().y() + center_y;
    update();
    emit print_console("mouse pointed to x = " + std::to_string(cur_cursor_x) + " y = " + std::to_string(cur_cursor_y));
    pressed_cursor_x_raw = me->localPos().x();
    pressed_cursor_y_raw = me->localPos().y();
    old_center_x = center_x;
    old_center_y = center_y;
}

void oGL_out::mouseReleaseEvent(QMouseEvent *me)
{

}
