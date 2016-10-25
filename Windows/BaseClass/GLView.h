#pragma once


// CGLView 뷰입니다.
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>


#define	DEFAULT_SIZE	50.f;

class CGLView : public CView
{
	DECLARE_DYNCREATE(CGLView)

public:
	CGLView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CGLView();

	struct GLVIEW_PARAM_USER
	{
		//PFD
		PIXELFORMATDESCRIPTOR pfd;

		//VIEWPORT
		GLint		Width;
		GLint		Height;

		//CLEAR 
		GLclampf	ClearColor[4];
		GLclampf	ClearDepth;

		//BUFFER
		GLboolean	CaptureDepth;
		GLboolean	IsCaptureDepth;
		GLfloat*	DepthBuffers;


		//PERSPECTIVE VIEWING VOLUME
		GLdouble	FOV;
		GLdouble	AspectRatio;
		GLdouble	Near;
		GLdouble	Far;

		//ORTHOGONAL VIEWING VOLUME
		GLdouble	OrthoView[6];
		GLfloat		Distance2VolumeRatio;	

		//MODELVIEW MATRIX
		GLfloat		vMat[16];

		//TRACKBALL
		GLfloat oPt[3];
		GLfloat cPt[3];
		GLfloat rotAx[3];
		GLfloat TrackBallSqrSize;

		//PROJECTION MODE
		GLboolean	IsPerspective;

		//LIGHT - Base LIght
		GLfloat		LightDiffuse[4];
		GLfloat		LightAmbient[4];
		GLfloat		LightSpecular[4];
		GLfloat		LightPosition0[4];
		GLboolean	LightOn;

		//CAMERA
		GLfloat		CameraCntr[3];
		GLfloat		CameraDistance;

		//Axis
		GLboolean	bShowAxis;
		GLfloat		axisLength;


	};
	typedef	GLVIEW_PARAM_USER	GLVIEW_PARAM_USER;

protected:
	struct GLVIEW_PARAM_DERIVED
	{
		//CLEAR BIT from PFD
		GLbitfield	ClearBits;

		//DC,RC
		HDC		hdc;
		HGLRC	hglrc;
	};
	typedef	GLVIEW_PARAM_DERIVED	GLVIEW_PARAM_DERIVED;


	GLVIEW_PARAM_USER		m_vp;
	GLVIEW_PARAM_DERIVED	m_dp;

	BOOL			m_bDrag;


public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

public:
	void	CreateGLView(CView* pParent, CRect rect);

	//OPENGL 
	virtual void	BeginGL();
	virtual void	DrawGL();
	virtual void	EndGL();
	virtual void	Capture();

	//Initial setting
	virtual void	Init();
	virtual void	InitTexture();
	virtual void	ReleaseTexture();

	//Per frame setting
	virtual void	Setup_Viewport();
	virtual void	ClearBuffer();
	virtual void	Setup_Projection();
	virtual void	Update_Ortho();
	virtual void	Setup_Camera();

	//Camera
	void	SetDistance(float dist);
	float	GetDistance();

	//Matrix
	void	InitVMat();

	//Depth buffer
	void		SetCaptureDepthBuffer();
	GLboolean	IsCaptured();
	GLfloat*	GetCapturedDepthBuffer();
	void		ReleaseCapturedDepthBuffer();

	//Axis
	void	DrawAxis();

	//Projection
	void	ToggleProjection();

		
private:

	void	CopyCustomePixelFormat(PIXELFORMATDESCRIPTOR* pPFD);
	int		SetupPixelFormat(HDC hdc);	// 픽셀포멧 설정
	void	SetClearBits(GLbitfield	clear_bits);
	

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


