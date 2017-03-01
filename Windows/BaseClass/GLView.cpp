// GLView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GLView.h"
#include <math.h>


// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

CGLView::CGLView()
{

	//PFD
	//Default PFD
	PIXELFORMATDESCRIPTOR default_pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), //size of this pfd
		1, //version number
		PFD_DRAW_TO_WINDOW | //support window
		PFD_SUPPORT_OPENGL| //supprt opengl
		PFD_DOUBLEBUFFER, //double buffering
		PFD_TYPE_RGBA, //RGBA type
		24, //24bit color depth
		0,0,0,0,0,0, //color bit ignored
		0, //no alpha buffer
		0, //shift bit ignored
		0, //no accumulation buffer
		0,0,0,0, //accumm bits ignored
		32, //32bit z buffer
		0,
		0,
		PFD_MAIN_PLANE, //main layer
		0,
		0,0,0
	};
	memcpy(&(m_vp.pfd),&default_pfd,sizeof(PIXELFORMATDESCRIPTOR));

	//VIEWPORT
	m_vp.Width = m_vp.Height = 1;

	//CLEAR
	m_vp.ClearColor[0]=m_vp.ClearColor[1]=m_vp.ClearColor[2]=m_vp.ClearColor[3]=0.f;
	m_vp.ClearDepth = 1.f;

	//BUFFER
	m_vp.CaptureDepth = GL_FALSE;
	m_vp.DepthBuffers = NULL;
	m_vp.IsCaptureDepth = GL_FALSE;

	//PERSPECTIVE VIEWING VOLUME
	m_vp.FOV	=	45.0;
	m_vp.AspectRatio	= (GLdouble)m_vp.Width/(GLdouble)m_vp.Height;
	m_vp.Near	= 1.0;
	m_vp.Far	= 5000.0;

	//ORTHOGONAL VIEWING VOLUME
	m_vp.OrthoView[0]=m_vp.OrthoView[2]=m_vp.OrthoView[4]=	-100.0;
	m_vp.OrthoView[1]=m_vp.OrthoView[3]=m_vp.OrthoView[5]=	100.0;
	m_vp.Distance2VolumeRatio = 0.4f;

	//PROJECTION MODE
	m_vp.IsPerspective = GL_TRUE;
	m_vp.IsPerspective = GL_FALSE;

	//MODELVIEW MATRIX
	GLfloat vmat[16]=
	{
		1.f,	0.f,	0.f,	0.f,
		0.f,	1.f,	0.f,	0.f,
		0.f,	0.f,	1.f,	0.f,
		0.f,	0.f,	0.f,	1.f,
	};
	memcpy(m_vp.vMatRot,vmat,sizeof(GLfloat)*16);


	//LIGHT0 - Base LIght
	m_vp.LightDiffuse[0]=m_vp.LightDiffuse[1]=m_vp.LightDiffuse[2]=0.8f; m_vp.LightDiffuse[3]=1.f;
	m_vp.LightAmbient[0]=m_vp.LightAmbient[1]=m_vp.LightAmbient[2]=0.2f; m_vp.LightAmbient[3]=1.f;
	m_vp.LightSpecular[0]=m_vp.LightSpecular[1]=m_vp.LightSpecular[2]=m_vp.LightSpecular[3]=0.7f;
	
	m_vp.LightPosition0[0]=1.f; m_vp.LightPosition0[1]=1.f; m_vp.LightPosition0[2]=1.f;	m_vp.LightPosition0[3]=0.f;
	m_vp.LightOn = GL_TRUE;

	//CAMERA
	m_vp.CameraDistance = 350.f;
	m_vp.CameraCntr[0] = m_vp.CameraCntr[1] = m_vp.CameraCntr[2] = 0.f;

	//AXIS
	m_vp.bShowAxis = GL_TRUE;// GL_FALSE;
	m_vp.axisLength = 100.f;

	///////// DERIVED PARAM
	//CLEAR BITs
	m_dp.ClearBits = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT;

	//DC,RC
	m_dp.hdc	= 0;
	m_dp.hglrc	= 0;

	m_bDragRot = FALSE;
	m_bDragPan = FALSE;


}

void CGLView::InitVMat()
{
	//MODELVIEW MATRIX
	GLfloat vmat[16]=
	{
		1.f,	0.f,	0.f,	0.f,
		0.f,	1.f,	0.f,	0.f,
		0.f,	0.f,	1.f,	0.f,
		0.f,	0.f,	0.f,	1.f,
	};
	memcpy(m_vp.vMatRot,vmat,sizeof(GLfloat)*16);

}


CGLView::~CGLView()
{
	if(m_vp.DepthBuffers)	delete m_vp.DepthBuffers;
	m_vp.DepthBuffers = new GLfloat[m_vp.Width*m_vp.Height];

}

BEGIN_MESSAGE_MAP(CGLView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CGLView::SetDistance(float dist)
{
	m_vp.CameraDistance = dist;
}
float CGLView::GetDistance()
{
	return m_vp.CameraDistance;
}


void CGLView::SetClearBits(GLbitfield	clear_bits)
{
	m_dp.ClearBits = clear_bits;
}


void CGLView::CreateGLView(CView* pParent,CRect rect)
{
	Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,rect,pParent,0);
	m_vp.Width	= rect.Width();
	m_vp.Height	= rect.Height();
	m_vp.AspectRatio	= (GLdouble)m_vp.Width/(GLdouble)m_vp.Height;

	m_vp.TrackBallSqrSize = (float)(m_vp.Height*m_vp.Height + m_vp.Width*m_vp.Width)/4.f;
	Update_Ortho();


}

//기본 픽셀 포멧을 사용하지 않으려면, CreateGLView를 호출하기 전에 PFD를 설정해주면 된다.
void CGLView::CopyCustomePixelFormat(PIXELFORMATDESCRIPTOR* pPFD)
{
	if(!pPFD)	return;
	memcpy(&(m_vp.pfd),pPFD,sizeof(PIXELFORMATDESCRIPTOR));
}

void CGLView::BeginGL()
{
	wglMakeCurrent(m_dp.hdc,m_dp.hglrc);
}

void CGLView::Setup_Viewport()
{
	//Use viewport the same size as the shadow map
	glViewport(0, 0, m_vp.Width, m_vp.Height);

}

void CGLView::ClearBuffer()
{
	glClearColor(m_vp.ClearColor[0],m_vp.ClearColor[1],m_vp.ClearColor[2],m_vp.ClearColor[3]);
	glClearDepth(m_vp.ClearDepth);
	glClear(m_dp.ClearBits);
}

void CGLView::Update_Ortho()
{
	//높이를 거리의 두배로 설정.
	GLfloat fBaseLength = m_vp.CameraDistance * m_vp.Distance2VolumeRatio;

	m_vp.OrthoView[2] = -fBaseLength;	//Bottom
	m_vp.OrthoView[3] = fBaseLength;	//Top

	m_vp.OrthoView[0] = -fBaseLength * m_vp.AspectRatio;	//Left
	m_vp.OrthoView[1] = fBaseLength * m_vp.AspectRatio;	//Right

	m_vp.OrthoView[4] = m_vp.Near;	//Near
	m_vp.OrthoView[5] = m_vp.Far;	//Far
}

void CGLView::Setup_Projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(m_vp.IsPerspective) 	gluPerspective(m_vp.FOV, m_vp.AspectRatio, m_vp.Near, m_vp.Far);
	else
	{
		glOrtho(m_vp.OrthoView[0], m_vp.OrthoView[1],
			m_vp.OrthoView[2], m_vp.OrthoView[3],
			m_vp.OrthoView[4], m_vp.OrthoView[5]);
	}
}

void CGLView::Setup_Camera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//원점으로 옮겨서 회전 시킨 후, 거리만큼 뒤로 보낸다.
	glTranslatef(0.f,0.f,-m_vp.CameraDistance);
	glMultMatrixf(m_vp.vMatRot);	//Rotate
	glTranslatef(-m_vp.CameraCntr[0], -m_vp.CameraCntr[1], -m_vp.CameraCntr[2]);	//Translate


	/*
	gluLookAt(150.0,150.0,150.0,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
				*/
}


void CGLView::DrawGL()
{
	DrawAxis();
	DrawViewAxis();
	DrawCamCenterAxis();

	//glColor3f(1.f,0.5f,0.5f);
	//glutSolidCube(50.f);
	//glutSolidSphere(50.,20,20);
}

void CGLView::EndGL()
{
	wglMakeCurrent(NULL,NULL);
}

void CGLView::Init()
{
	BeginGL();

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, m_vp.LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_vp.LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_vp.LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, m_vp.LightPosition0);
	if(m_vp.LightOn)
	{
		glEnable(GL_LIGHT0);
	}


	InitTexture();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);

	EndGL();
}

void	CGLView::InitTexture()
{

}
void	CGLView::ReleaseTexture()
{

}


// CGLView 그리기입니다.

void CGLView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	BeginGL();

	Setup_Viewport();

	ClearBuffer();

	Setup_Projection();

	Setup_Camera();

	glLightfv(GL_LIGHT0, GL_POSITION, m_vp.LightPosition0);

	DrawGL();


	glFinish();

	Capture();

	SwapBuffers(m_dp.hdc);

	EndGL();

}

void CGLView::Capture()
{
	if(m_vp.CaptureDepth)
	{
		glReadPixels(0, 0, m_vp.Width, m_vp.Height, GL_DEPTH_COMPONENT, GL_FLOAT, m_vp.DepthBuffers);
		m_vp.CaptureDepth = GL_FALSE;
		m_vp.IsCaptureDepth = GL_TRUE;
	}

}

void CGLView::SetCaptureDepthBuffer()
{
	m_vp.CaptureDepth = GL_TRUE;

	if(m_vp.DepthBuffers)	delete m_vp.DepthBuffers;
	m_vp.DepthBuffers = new GLfloat[m_vp.Width*m_vp.Height];

	m_vp.IsCaptureDepth = GL_FALSE;
	
}

void CGLView::ReleaseCapturedDepthBuffer()
{
	if(m_vp.DepthBuffers)	delete m_vp.DepthBuffers;
	m_vp.DepthBuffers = NULL;

	m_vp.CaptureDepth = GL_FALSE;
	m_vp.IsCaptureDepth = GL_FALSE;
}

GLboolean CGLView::IsCaptured()
{
	return m_vp.IsCaptureDepth;
}

GLfloat* CGLView::GetCapturedDepthBuffer()
{
	return m_vp.DepthBuffers;
}


// CGLView 진단입니다.

#ifdef _DEBUG
void CGLView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// 픽셀포멧 설정

int CGLView::SetupPixelFormat(HDC hdc)
{
	int iPixelFormat;
	//get the device context's best, abailable pixel format match
	if((iPixelFormat = ChoosePixelFormat(hdc,&(m_vp.pfd)))==0)
	{
		MessageBox("ChoosePixelFormat Failed!","Error",MB_OK);
		return 0;
	}

	//make that match the device context's current pixel format
	if(SetPixelFormat(hdc,iPixelFormat,&(m_vp.pfd))==FALSE)
	{
		MessageBox("SetPixelFormat Failed!","Error",MB_OK);
		return 0;
	}

	//DERIVED 
	m_dp.hdc = hdc;
	m_dp.hglrc = wglCreateContext(hdc);


	return 1;
}

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetupPixelFormat(::GetDC(m_hWnd));
	Init();

	return 0;
}


void CGLView::OnDestroy()
{
	CView::OnDestroy();

	BeginGL();
	ReleaseTexture();
	EndGL();


	// TODO: 여기에 메시지 처리기 코드를 추가합니다
	::ReleaseDC(m_hWnd,m_dp.hdc);
	wglDeleteContext(m_dp.hglrc);

}
void CGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDragRot = TRUE;

	m_vp.oPt[0] = m_vp.cPt[0]	=	(float)(point.x - m_vp.Width/2);
	m_vp.oPt[1] = m_vp.cPt[1]	=	(float)(m_vp.Height/2 - point.y);
	m_vp.oPt[2] = m_vp.cPt[2]	=	(float)sqrt(m_vp.TrackBallSqrSize - m_vp.oPt[0] * m_vp.oPt[0] - m_vp.oPt[1] * m_vp.oPt[1]);

	CView::OnLButtonDown(nFlags, point);
}

void CGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDragRot = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CGLView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDragPan = TRUE;

	m_vp.oPt[0] = m_vp.cPt[0] = (float)(point.x);
	m_vp.oPt[1] = m_vp.cPt[1] = (float)(point.y);
	m_vp.oPt[2] = m_vp.cPt[2] = 0.f;

	SetCapture();
	CView::OnMButtonDown(nFlags, point);
}


void CGLView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDragPan = FALSE;
	ReleaseCapture();

	CView::OnMButtonUp(nFlags, point);
}


void CGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bDragRot && !m_bDragPan)	return;

	if (m_bDragRot)
	{
		//Point on Trackball
		m_vp.cPt[0] = (float)(point.x - m_vp.Width / 2);
		m_vp.cPt[1] = (float)(m_vp.Height / 2 - point.y);
		m_vp.cPt[2] = (float)sqrt(m_vp.TrackBallSqrSize - m_vp.cPt[0] * m_vp.cPt[0] - m_vp.cPt[1] * m_vp.cPt[1]);
		//	printf("CPoint =%f, %f, %f\n",m_vp.cPt[0],m_vp.cPt[1],m_vp.cPt[2]);

		//Rot axis
		m_vp.rotAx[0] = m_vp.oPt[1] * m_vp.cPt[2] - m_vp.oPt[2] * m_vp.cPt[1];
		m_vp.rotAx[1] = m_vp.oPt[2] * m_vp.cPt[0] - m_vp.oPt[0] * m_vp.cPt[2];
		m_vp.rotAx[2] = m_vp.oPt[0] * m_vp.cPt[1] - m_vp.oPt[1] * m_vp.cPt[0];

		//angle
		float angle;
		angle = (float)acos((m_vp.cPt[0] * m_vp.oPt[0] + m_vp.cPt[1] * m_vp.oPt[1] + m_vp.cPt[2] * m_vp.oPt[2]) / (m_vp.TrackBallSqrSize));

	//	m_vp.vMatRot[12] = m_vp.vMatRot[13] = m_vp.vMatRot[14] = 0.f; //Remove translate
		this->BeginGL();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(angle*180.f / 3.141592f, m_vp.rotAx[0], m_vp.rotAx[1], m_vp.rotAx[2]);
		glMultMatrixf(m_vp.vMatRot);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_vp.vMatRot);
	//	m_vp.vMatRot[12] = m_vp.vMatRot[13] = m_vp.vMatRot[14] = 0.f; //Remove translate
		this->EndGL();
		m_vp.oPt[0] = m_vp.cPt[0];
		m_vp.oPt[1] = m_vp.cPt[1];
		m_vp.oPt[2] = m_vp.cPt[2];
	}
	else if (m_bDragPan)
	{
		//Delta
		float dH = -(float)(point.x - m_vp.oPt[0]);
		float dV = -(float)(m_vp.oPt[1] - point.y);
		float fScale = m_vp.CameraDistance * 0.001f;

		float dP[3];
		dP[0] = (m_vp.vMatRot[0] * dH + m_vp.vMatRot[1] * dV) * fScale;
		dP[1] = (m_vp.vMatRot[4] * dH + m_vp.vMatRot[5] * dV) * fScale;
		dP[2] = (m_vp.vMatRot[8] * dH + m_vp.vMatRot[9] * dV) * fScale;

		m_vp.CameraCntr[0] += dP[0];
		m_vp.CameraCntr[1] += dP[1];
		m_vp.CameraCntr[2] += dP[2];

		m_vp.oPt[0] = m_vp.cPt[0] = (float)point.x;
		m_vp.oPt[1] = m_vp.cPt[1] = (float)point.y;
		m_vp.oPt[2] = m_vp.cPt[2] = 0.f;
	}





	Invalidate(FALSE);

	CView::OnMouseMove(nFlags, point);
}

BOOL CGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	if(zDelta>0)	m_vp.CameraDistance *= 1.005f;
	else			m_vp.CameraDistance *= 0.995f;

	if (m_vp.IsPerspective == GL_FALSE)
		Update_Ortho();

	Invalidate(FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	return CView::OnEraseBkgnd(pDC);
}

//////////////////////////////////////////////
void	CGLView::DrawAxis()
{
	// TODO: Add your message handler code here and/or call default
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(0.f, 0.f, 0.f); glVertex3f( m_vp.axisLength, 0.f, 0.f);
	glColor3ub(0,255,  0);
	glVertex3f(0.f, 0.f, 0.f); glVertex3f( 0.f,m_vp.axisLength, 0.f);
	glColor3ub(0,0,255);
	glVertex3f(0.f, 0.f, 0.f); glVertex3f( 0.f,0.f, m_vp.axisLength);
	glEnd();
	glPopAttrib();
}

void	CGLView::DrawViewAxis()
{
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	glColor3ub(0, 255, 255);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(m_vp.vMatRot[0] * 100.f, m_vp.vMatRot[4] * 100.f, m_vp.vMatRot[8] * 100.f);

	glColor3ub(255, 0, 255);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(m_vp.vMatRot[1] * 100.f, m_vp.vMatRot[5] * 100.f, m_vp.vMatRot[9] * 100.f);

	glColor3ub(255, 255, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(m_vp.vMatRot[2] * 100.f, m_vp.vMatRot[6] * 100.f, m_vp.vMatRot[10] * 100.f);
	glEnd();
	glPopAttrib();
}

void	CGLView::DrawCamCenterAxis()
{
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	glColor3ub(0, 255, 255);
	glVertex3f(m_vp.CameraCntr[0], m_vp.CameraCntr[1], m_vp.CameraCntr[2]);
	glVertex3f(m_vp.CameraCntr[0]+100.f, m_vp.CameraCntr[1], m_vp.CameraCntr[2]);

	glColor3ub(255, 0, 255);
	glVertex3f(m_vp.CameraCntr[0], m_vp.CameraCntr[1], m_vp.CameraCntr[2]);
	glVertex3f(m_vp.CameraCntr[0], m_vp.CameraCntr[1] + 100.f, m_vp.CameraCntr[2]);

	glColor3ub(255, 255, 0);
	glVertex3f(m_vp.CameraCntr[0], m_vp.CameraCntr[1], m_vp.CameraCntr[2]);
	glVertex3f(m_vp.CameraCntr[0], m_vp.CameraCntr[1], m_vp.CameraCntr[2] + 100.f);
	glEnd();
	glPopAttrib();

}


//Projection
void	CGLView::ToggleProjection()
{
	m_vp.IsPerspective = !m_vp.IsPerspective;
	Invalidate();
}