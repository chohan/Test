// Semaphore_ExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Semaphore_Ex.h"
#include "Semaphore_ExDlg.h"
#include <process.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Handles to the semaphores
HANDLE m_hProduction,m_hCustomer;

//Handles to the events that start/stop the threads
HANDLE hEventProd,hEventCons;

//Handles to the threads
HANDLE hT1,hT2;

#pragma data_seg("Babu")
int g_Var = 0;
#pragma data_seg()


#define MAX_ELEMENTS 10
int containerArray[MAX_ELEMENTS];

//************************************************************************
//THIS THREAD DOES THE PRODCUTION BASED ON THE CUSTOMER REQUEST.
//IF THE CUSTOMER SEMAPHORE OBJECT IS SIGNALLED THEN THE PRODUCTION IS READY TO START.
//AN EVENT OBJECT hEventProd SIGNALS THE PRODUCTION LINE IF THE POWER IS ON OTHERWISE
//UNSIGNALS IT.
//IF THE PRODUCTION IS DONE THEN IT SIGNALS THE PRODUCTION SEMAPHORE OBJECT
//SO THAT THE CUSTOMER WILL GET HIS PRODUCT

unsigned WINAPI Production(PVOID dlgPtr )
{
	CSemaphore_ExDlg* pDlg = (CSemaphore_ExDlg*)(dlgPtr);

	//Do the production if there is any customer request.Otherwise waitn for the
	//customer's request
	DWORD res = WaitForSingleObject( m_hCustomer,INFINITE );

	//if the object is signalled,do the production
	int i = 0, j = 0;
	static int Ctr = 0;
	while ( res == WAIT_OBJECT_0 )
	{
		//Check for the production event signal
		WaitForSingleObject( hEventProd, INFINITE );

		containerArray[j++] = i++;
		Ctr++;

		g_Var++;
		CString str;
		str.Format("%d", g_Var );
		pDlg->m_statNew.SetWindowText( str );

		//Set the value in the progress bar
		(pDlg->m_ctrlProd).SetValue( Ctr );
		
		if( j >= MAX_ELEMENTS )
			j = j % MAX_ELEMENTS;

	
		//Production is done.So signal the csutomer 
		LONG pOldVal;
		ReleaseSemaphore( m_hProduction,1,&pOldVal );

		//Do the production continously
		res = WaitForSingleObject( m_hCustomer,INFINITE );
		Sleep( 50 );

	}

	return 0;
}
//************************************************************************
//THIS THREAD IS TO GET THE CUSTOMER REQUEST AND TO SIGNAL THE CUSTOMER SEMAPHORE
//OBJECT ABD GET THE PRODUCT FROM THE PRODUCTION LINE AND DISPATCH IT TO THE CUSTOMER.
//IF PRODUCTION SEMAPHORE IS SIGNALLED [ ie.,IF THERE ARE SOME FINISHED PRODUCTS ]
//AN EVENT OBJECT m_hCustomer USED TO GET THE REQUEST FROM THE CUSTOMER.IF THIS IS SIGNALLED
//REQUEST IS TAKEN FROM CUSTOMER OTHER WISE NO MORE CUSTOMER REQUEST IS ACCEPTED.
unsigned WINAPI Consumption(PVOID dlgPtr )
{
	CSemaphore_ExDlg* pDlg = (CSemaphore_ExDlg*)(dlgPtr);

	//Consume the product if already some produced goods are available
	DWORD res = WaitForSingleObject( m_hProduction,INFINITE );

	//if the object is signalled,do the production
	int i = 0, j = 0;
	static int Ctr = 0;
	while ( res == WAIT_OBJECT_0 )
	{
		//Check for the consumer event object
		WaitForSingleObject( hEventCons, INFINITE );

		containerArray[j++] = -1;
		Ctr++;

		(pDlg->m_ctrlCons).SetValue(Ctr );

		if( j >= MAX_ELEMENTS )
			j = j % MAX_ELEMENTS;

		//Consumption is done.So signal the empty object
		ReleaseSemaphore( m_hCustomer,1,0 );

		//Do the consumption continously
		res = WaitForSingleObject( m_hProduction,INFINITE );
		Sleep( 50 );


	}

	return 0;
}
//************************************************************************

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSemaphore_ExDlg dialog

CSemaphore_ExDlg::CSemaphore_ExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSemaphore_ExDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CSemaphore_ExDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CSemaphore_ExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSemaphore_ExDlg)
	DDX_Control(pDX, IDC_STATIC_NEW, m_statNew);
	DDX_Control(pDX, IDC_STATIC_PROD, m_ctrlProd);
	DDX_Control(pDX, IDC_STATIC_CONS, m_ctrlCons);
	DDX_Control(pDX, IDC_CHECK_CONS, m_butCons);
	DDX_Control(pDX, IDC_CHECK_PROD, m_butProd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSemaphore_ExDlg, CDialog)
	//{{AFX_MSG_MAP(CSemaphore_ExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CONS, OnConsumption)
	ON_BN_CLICKED(IDC_CHECK_PROD, OnProduction)		
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSemaphore_ExDlg message handlers

BOOL CSemaphore_ExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	Initialize();	

	CString str;
	str.Format("%d", g_Var );
	m_statNew.SetWindowText( str );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSemaphore_ExDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSemaphore_ExDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSemaphore_ExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSemaphore_ExDlg::OnConsumption() 
{
	// TODO: Add your control notification handler code here
	CString str;
	if( m_butCons.GetCheck() == BST_CHECKED )
	{
		SetEvent(hEventCons);
		str = "Stop";
	}
	else
	{
		ResetEvent( hEventCons );
		str = "Start";
	}
	m_butCons.SetWindowText(str);
}

void CSemaphore_ExDlg::OnProduction() 
{
	// TODO: Add your control notification handler code here
	int state = m_butProd.GetCheck();
	CString str;
	//Toggle the event object
	if( state == BST_CHECKED )
	{
		SetEvent(hEventProd);			
		str = "Stop";
	}
	else
	{
		ResetEvent( hEventProd );	
		str = "Start";
	}
	m_butProd.SetWindowText(str);
}
//***************************************************************************
void CSemaphore_ExDlg::Initialize()
{
	//Set the color for the progress bar
	m_ctrlCons.SetFillColor( 255,75,75);
	m_ctrlProd.SetFillColor( 11,157,58);
	m_ctrlCons.SetShowValue( true);	
	m_ctrlProd.SetShowValue( true);

	//Set the event button intially as stop
	m_butCons.SetCheck( BST_UNCHECKED );
	m_butProd.SetCheck( BST_UNCHECKED );
	m_butCons.SetWindowText("Start");
	m_butProd.SetWindowText("Start");

	//Create the semaphores
	//Initially nonsignalled
	m_hProduction		=	CreateSemaphore( NULL,0,MAX_ELEMENTS,"Full");

	//Initially signalled.Means there are some customer request 
	m_hCustomer	=	CreateSemaphore( NULL,MAX_ELEMENTS,MAX_ELEMENTS,"Empty");	

	hEventProd = CreateEvent( NULL,TRUE,false,NULL );
	hEventCons = CreateEvent( NULL,TRUE,false,NULL );

	//Create the threads
	unsigned dTID = 0;
	//hT1 = CreateThread( NULL,0,Production,this,0,&tID );
	hT1 = (HANDLE)_beginthreadex( NULL,0,Production,this,0,&dTID );
	hT2 = (HANDLE)_beginthreadex( NULL,0,Consumption,this,0,&dTID );
	
	
}
//***************************************************************************

void CSemaphore_ExDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	SuspendThread( hT1);
	SuspendThread( hT2);

	CDialog::OnCancel();
}

void CSemaphore_ExDlg::OnOK() 
{
	// TODO: Add extra validation here
	SuspendThread( hT1);
	SuspendThread( hT2);
	CDialog::OnOK();

	MEMORYSTATUS memState;
	GlobalMemoryStatus(&memState );

	int* p = new int;

	int* nb = new int[64];

	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery( p,&mbi,sizeof(mbi) );

	int* paddress = (int*)(1024*1024*50);
	void* pvoid = VirtualAlloc( paddress,1024,MEM_RESERVE,PAGE_READWRITE );


	
}


