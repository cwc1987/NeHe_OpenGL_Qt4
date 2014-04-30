#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include <QMessageBox>
#include <QApplication>

//Math types derived from the KempoApi tMath library
    typedef union Tuple2f_t
    {
        struct
        {
            GLfloat X, Y;
        } s;

        GLfloat T[2];
    } Tuple2fT;      //A generic 2-element tuple that is represented by single-precision floating point x,y coordinates.

    typedef union Tuple3f_t
    {
        struct
        {
            GLfloat X, Y, Z;
        } s;

        GLfloat T[3];
    } Tuple3fT;      //A generic 3-element tuple that is represented by single precision-floating point x,y,z coordinates.

    typedef union Tuple4f_t
    {
        struct
        {
            GLfloat X, Y, Z, W;
        } s;

        GLfloat T[4];
    } Tuple4fT;      //A 4-element tuple represented by single-precision floating point x,y,z,w coordinates.

    typedef union Matrix3f_t
    {
            struct
            {
                //column major
                union { GLfloat M00; GLfloat XX; GLfloat SX; };  //XAxis.X and Scale X
                union { GLfloat M10; GLfloat XY;             };  //XAxis.Y
                union { GLfloat M20; GLfloat XZ;             };  //XAxis.Z
                union { GLfloat M01; GLfloat YX;             };  //YAxis.X
                union { GLfloat M11; GLfloat YY; GLfloat SY; };  //YAxis.Y and Scale Y
                union { GLfloat M21; GLfloat YZ;             };  //YAxis.Z
                union { GLfloat M02; GLfloat ZX;             };  //ZAxis.X
                union { GLfloat M12; GLfloat ZY;             };  //ZAxis.Y
                union { GLfloat M22; GLfloat ZZ; GLfloat SZ; };  //ZAxis.Z and Scale Z
            } s;
            GLfloat M[9];
    } Matrix3fT;     //A single precision floating point 3 by 3 matrix.

    typedef union Matrix4f_t
    {
            struct
            {
                //column major
                union { GLfloat M00; GLfloat XX; GLfloat SX; };  //XAxis.X and Scale X
                union { GLfloat M10; GLfloat XY;             };  //XAxis.Y
                union { GLfloat M20; GLfloat XZ;             };  //XAxis.Z
                union { GLfloat M30; GLfloat XW;             };  //XAxis.W
                union { GLfloat M01; GLfloat YX;             };  //YAxis.X
                union { GLfloat M11; GLfloat YY; GLfloat SY; };  //YAxis.Y and Scale Y
                union { GLfloat M21; GLfloat YZ;             };  //YAxis.Z
                union { GLfloat M31; GLfloat YW;             };  //YAxis.W
                union { GLfloat M02; GLfloat ZX;             };  //ZAxis.X
                union { GLfloat M12; GLfloat ZY;             };  //ZAxis.Y
                union { GLfloat M22; GLfloat ZZ; GLfloat SZ; };  //ZAxis.Z and Scale Z
                union { GLfloat M32; GLfloat ZW;             };  //ZAxis.W
                union { GLfloat M03; GLfloat TX;             };  //Trans.X
                union { GLfloat M13; GLfloat TY;             };  //Trans.Y
                union { GLfloat M23; GLfloat TZ;             };  //Trans.Z
                union { GLfloat M33; GLfloat TW; GLfloat SW; };  //Trans.W and Scale W
            } s;
            GLfloat M[16];
    } Matrix4fT;     //A single precision floating point 4 by 4 matrix.

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
protected:
    void resizeGL(int w, int h);

    void initializeGL();

    void paintGL();

    void keyPressEvent(QKeyEvent *event);
private:
    bool m_show_full_screen;
};

#endif // MYGLWIDGET_H
