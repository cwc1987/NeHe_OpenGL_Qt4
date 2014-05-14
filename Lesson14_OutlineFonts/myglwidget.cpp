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
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    glEnable(GL_LIGHT0);								// Enable Default Light (Quick And Dirty)
    glEnable(GL_LIGHTING);								// Enable Lighting
    glEnable(GL_COLOR_MATERIAL);						// Enable Coloring Of Material

    QString fontPath = QApplication::applicationDirPath() + "/Test.ttf";
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glTranslatef(0.0f,0.0f,-10.0f);						// Move One Unit Into The Screen
    glRotatef(m_rot,1.0f,0.0f,0.0f);						// Rotate On The X Axis
    glRotatef(m_rot*1.5f,0.0f,1.0f,0.0f);					// Rotate On The Y Axis
    glRotatef(m_rot*1.4f,0.0f,0.0f,1.0f);					// Rotate On The Z Axis
    // Pulsing Colors Based On The Rotation
    glColor3f(1.0f*float(cos(m_rot/20.0f)),1.0f*float(sin(m_rot/25.0f)),1.0f-0.5f*float(cos(m_rot/17.0f)));
    QString renderText = QString("NeHe - %1").arg(m_rot/50);
    glTranslatef(-3.0,0.0f,0.0f);                           // Center Our Text On The Screen
    m_freeTypeFont->Render(renderText.toLatin1().data());						// Print GL Text To The Screen
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
    m_rot+=0.5f;											// Increase The Rotation Variable
    updateGL();
    QGLWidget::timerEvent(event);
}

//在这一课中，我已试着尽量详细解释一切。每一步都与设置有关，并创建了一个全屏OpenGL程序。
//当您按下ESC键程序就会退出，并监视窗口是否激活。
//如果您有什么意见或建议请给我EMAIL。如果您认为有什么不对或可以改进，请告诉我。
//我想做最好的OpenGL教程并对您的反馈感兴趣。
