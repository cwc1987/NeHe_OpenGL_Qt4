#include "myglwidget.h"

//图形字体:
//在一课我们将教你绘制3D的图形字体，它们可像一般的3D模型一样被变换。

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent), m_show_full_screen(false),
    m_freeTypeFont(NULL),  m_rot(0.0f)
{
    showNormal();
    startTimer(15);
}

MyGLWidget::~MyGLWidget()
{
    glDeleteTextures(1, &m_texture[0]);
}

void MyGLWidget::resizeGL(int w, int h)
{
    if (h==0)										// Prevent A Divide By Zero By
    {
        h=1;										// Making Height Equal One
    }

    glViewport(0,0,w,h);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();									// Reset The Modelview Matrix
}

void MyGLWidget::initializeGL()
{
    loadGLTexture();
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable(GL_LIGHT0);								// Quick And Dirty Lighting (Assumes Light0 Is Set Up)
    glEnable(GL_LIGHTING);								// Enable Lighting
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);			// Select The Texture

    QString fontPath = QApplication::applicationDirPath() + "/Wingdings.ttf";
    m_freeTypeFont = new FTGLExtrdFont(fontPath.toLatin1().data());
    if(m_freeTypeFont == NULL)
    {
        QMessageBox::warning(this, tr("Warning"), tr("%1 file can't find").arg(fontPath));
    }
    else
    {
        m_freeTypeFont->FaceSize(1);
        m_freeTypeFont->Depth(0.2);
        m_freeTypeFont->CharMap(ft_encoding_unicode);
    }
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The View
    glTranslatef(1.1f*float(cos(m_rot/16.0f)),0.8f*float(sin(m_rot/20.0f)),-3.0f);
    glRotatef(m_rot,1.0f,0.0f,0.0f);						// Rotate On The X Axis
    glRotatef(m_rot*1.2f,0.0f,1.0f,0.0f);					// Rotate On The Y Axis
    glRotatef(m_rot*1.4f,0.0f,0.0f,1.0f);					// Rotate On The Z Axis
    glTranslatef(-0.35f,-0.35f,0.1f);					// Center On X, Y, Z Axis
    m_freeTypeFont->Render("N");						// Draw A Skull And Crossbones Symbol
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_F2:
        {
            m_show_full_screen = !m_show_full_screen;
            if(m_show_full_screen)
            {
                showFullScreen();
            }
            else
            {
                showNormal();
            }
            updateGL();
            break;
        }
        case Qt::Key_Escape:
        {
            qApp->exit();
            break;
        }
    }
}

void MyGLWidget::timerEvent(QTimerEvent *event)
{
    m_rot+=0.1f;											// Increase The Rotation Variable
    updateGL();
    QGLWidget::timerEvent(event);
}

void MyGLWidget::loadGLTexture()
{
    QImage image(":/image/Lights.bmp");
    image = image.convertToFormat(QImage::Format_RGB888);
    image = image.mirrored();
    glGenTextures(1, &m_texture[0]);
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.width(), image.height(),
            GL_RGB, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
}
