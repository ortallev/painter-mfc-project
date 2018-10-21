
// MyPainterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPainter.h"
#include "MyPainterDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyPainterDlg dialog




CMyPainterDlg::CMyPainterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPainterDlg::IDD, pParent)
	, isThin(FALSE)
{
	futureFigKIND=LINE;
	isPressed=false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CMyPainterDlg::~CMyPainterDlg()
{}

void CMyPainterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK1, isThin);
	DDX_Control(pDX, IDC_MFC_MOVE, ActiveBot);
	DDX_Control(pDX, IDC_MFC_Controler_move, MoveButY);


}

BEGIN_MESSAGE_MAP(CMyPainterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_frameThin, &CMyPainterDlg::OnBnClicked_frameThin)

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//ON_WM_HSCROLL()


	
	ON_BN_CLICKED(IDC_Line, &CMyPainterDlg::OnBnClicked_Line)
	ON_BN_CLICKED(IDC_RECTANGLE, &CMyPainterDlg::OnBnClicked_RECTANGLE)
	ON_BN_CLICKED(IDC_TRIANGLE, &CMyPainterDlg::OnBnClicked_TRIANGLE)
	ON_BN_CLICKED(IDC_ELLIPSE, &CMyPainterDlg::OnBnClicked_ELLIPSE)
	ON_BN_CLICKED(IDC_SQUARE, &CMyPainterDlg::OnBnClicked_SQUARE)
	ON_BN_CLICKED(IDC_PARALLELOGRAM, &CMyPainterDlg::OnBnClicked_PARALLELOGRAM)
	ON_BN_CLICKED(IDC__RIGHT_ANGLED_TRAPEZOID, &CMyPainterDlg::OnBnClicked_RIGHT_ANGLED_TRAPEZOID)
	ON_BN_CLICKED(IDC__RIGHT_TRIANGLE, &CMyPainterDlg::OnBnClicked_RIGHT_TRIANGLE)
	ON_BN_CLICKED(IDC_MFC_save, &CMyPainterDlg::OnBnClickedMfcsave)
	ON_BN_CLICKED(IDC_MFCload, &CMyPainterDlg::OnBnClickedMfcload)
	ON_BN_CLICKED(IDC_MFCRedo, &CMyPainterDlg::OnBnClickedMfcredo)
	ON_BN_CLICKED(IDC_MFCUndo, &CMyPainterDlg::OnBnClickedMfcundo)
	ON_BN_CLICKED(IDC_MFCNew, &CMyPainterDlg::OnBnClickedMfcnew)
	ON_BN_CLICKED(IDC_MFC_CBackground, &CMyPainterDlg::OnBnClickedMfcCbackground)
	ON_BN_CLICKED(IDC_MFC_FrameColor, &CMyPainterDlg::OnBnClickedMfcFramecolor)
	ON_BN_CLICKED(IDC_MFC_MOVE, &CMyPainterDlg::OnBnClickedMfcMove)
	ON_BN_CLICKED(IDC_MFC_Controler_move, &CMyPainterDlg::OnBnClickedMfcControlermove)
END_MESSAGE_MAP()


// CMyPainterDlg message handlers

BOOL CMyPainterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPainterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyPainterDlg::OnPaint()
{
	CPaintDC dc(this);

	for (int i=0; i < shapes.GetSize(); ++i)
		shapes[i]->draw(&dc);


	CBrush brush(bgColor);
	CBrush *oldBrush = dc.SelectObject(&brush);
	CPen pen(PS_SOLID, isThin?1:3,FbgColor);
	CPen *oldPen = dc.SelectObject(&pen);
	//dc.Rectangle(875,52,915,92); 
	dc.SelectObject( oldBrush ); 
	dc.SelectObject(oldPen);
		
	CDialogEx::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyPainterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyPainterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(isPressed)
	{

		shapes[shapes.GetSize() - 1]->setEnd(point);
		Invalidate();

	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMyPainterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isPressed=true;
		CClientDC dc(this);
	Figure *n=0;
	switch(futureFigKIND)
	{
	case RECTANGLE: n = new RectangleM(isThin);
		break;
	case ELLIPSE: n = new EllipseM(isThin); 
		break;
	case LINE: n = new LineM(isThin);
		break;
	case TRIANGLE: n = new TriangleM(isThin);
		break;
	case SQUARE: n = new SqureM(isThin);
		break;
	case PARALLELOGRAM: n = new ParallelogramM(isThin);
		break;
	case RIGHTANGLEDTRAPEZOID: n = new TrapezoidM(isThin);
		break;
	case RIGHTTRIANGLE: n = new RTriangleM(isThin);
		break;
	}
	

	Command *c = new shape_add(shapes, n);// enter the shape that create to the stack 
	c->perform();
	commands.push(c);
	n->setBg(bgColor);// save for the shape the fiil color 
	n->setFBg(FbgColor);// save for the shape the frame color 
	n->setStart(point);
	n->setEnd(point);
	Invalidate(); // drew  the screen 
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMyPainterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isPressed = false;
	CDialogEx::OnLButtonUp(nFlags, point);
	
}

void CMyPainterDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
}
 
void CMyPainterDlg::OnOK()
{
	CFile file(L"FILE.$$", CFile::modeWrite | CFile::modeCreate);
	CArchive ar(&file, CArchive::store);
	shapes.Serialize(ar);
	Invalidate();
	CDialogEx::OnOK();
}

void CMyPainterDlg::OnBnClicked_frameThin()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}

void CMyPainterDlg::OnBnClicked_Line()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=LINE;
}

void CMyPainterDlg::OnBnClicked_RECTANGLE()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=RECTANGLE;
}

void CMyPainterDlg::OnBnClicked_TRIANGLE()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=TRIANGLE;
}

void CMyPainterDlg::OnBnClicked_ELLIPSE()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=ELLIPSE;
}

void CMyPainterDlg::OnBnClicked_SQUARE()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=SQUARE;
}

void CMyPainterDlg::OnBnClicked_PARALLELOGRAM()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=PARALLELOGRAM;
}

void CMyPainterDlg::OnBnClicked_RIGHT_ANGLED_TRAPEZOID()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=RIGHTANGLEDTRAPEZOID;
}

void CMyPainterDlg::OnBnClicked_RIGHT_TRIANGLE()
{
	// TODO: Add your control notification handler code here
	futureFigKIND=RIGHTTRIANGLE;
}

void CMyPainterDlg::OnBnClickedMfcsave()
{
	// TODO: Add your control notification handler code here
		std::string *pPath;
	CFileDialog dlg(false,_T("Chart Files (*.$$)|*.$$|"),NULL,NULL,_T("Chart Files (*.$$)|*.$$|"));
	auto result = dlg.DoModal();
    if(result != IDOK)
		 MessageBox(_T("Problem With Choosing This File"), _T("Error"), 
      MB_ICONERROR | MB_OK);
    //else 
		//pPath->assign(dlg.GetPathName());
OPENFILENAME& ofn = dlg.GetOFN( );
	char* s = NULL;
	try
	{
		CFile file(ofn.lpstrFile, CFile::modeCreate);
	}
	catch(int e)
	{};
	CFile file(ofn.lpstrFile, CFile::modeWrite);
	
	CArchive ar (&file, CArchive::store);
	shapes.Serialize(ar);
	ar.Close();
	file.Close();
}

void CMyPainterDlg::OnBnClickedMfcload()
{
	// TODO: Add your control notification handler code here
		std::string *pPath;
	CFileDialog dlg(true,_T("Chart Files (*.$$)|*.$$|"),NULL,NULL,_T("Chart Files (*.$$)|*.$$|"));
	auto result = dlg.DoModal();
    if(result != IDOK)
			 MessageBox(_T("Problem With Choosing This File"), _T("Error"), 
      MB_ICONERROR | MB_OK);
	OPENFILENAME& ofn = dlg.GetOFN( );
	CFile file(ofn.lpstrFile, CFile::modeRead);
	CArchive ar (&file, CArchive::load);
	shapes.Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();
}

void CMyPainterDlg::OnBnClickedMfcredo()
{
	// TODO: Add your control notification handler code here
		if(undoes.empty())
		return;
	Command *c = undoes.top();
	c->perform();
	commands.push(c);
	undoes.pop();
	Invalidate();
}

void CMyPainterDlg::OnBnClickedMfcundo()
{
	// TODO: Add your control notification handler code here
		if(commands.empty())
		return;
		Command *c = commands.top();
		c->rollback();
		undoes.push(c);
		commands.pop();
		Invalidate();
}

void CMyPainterDlg::OnBnClickedMfcnew()
{
	// TODO: Add your control notification handler code here
		while(!commands.empty())
	{
		Command *c = commands.top();
		c->rollback();
		undoes.push(c);
		commands.pop();
		Invalidate();
	}
	return;
}

void CMyPainterDlg::OnBnClickedMfcCbackground()
{
	// TODO: Add your control notification handler code here
		CColorDialog dlg;
	
	dlg.DoModal();
	bgColor=dlg.GetColor();

}

void CMyPainterDlg::OnBnClickedMfcFramecolor()
{
	// TODO: Add your control notification handler code here
		CColorDialog dlg;
	
	dlg.DoModal();
	FbgColor=dlg.GetColor();
}

void CMyPainterDlg::OnBnClickedMfcMove()
{
	// TODO: Add your control notification handler code here
	// button move 
	if(!started)
	{
		MoveX_MoveY = 0;
		SetTimer(1,4,NULL);
		started = true;
	}
	else
	{
		KillTimer(1);
		started = false;
	}
}

void CMyPainterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// set timer for function move 
	CRect rect;
	GetClientRect (&rect);
		for(int i=0;i<shapes.GetSize();i++)
			shapes[i]->Move(2,MoveX_MoveY,rect);
	 Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}

void CMyPainterDlg::OnBnClickedMfcControlermove()
{
	// TODO: Add your control notification handler code here
	// the function move shape in diraction 
	
		if(!MoveX_MoveY)
	{
		this->MoveX_MoveY = 1;
		MoveButY.SetWindowTextW(_T("MoveX"));
	}
	else
	{
		this->MoveX_MoveY = 0;
		MoveButY.SetWindowTextW(_T("MoveY"));
	}
} 
