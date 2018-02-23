//------------------------------------------------------------------------------------------
//This program demonstrates how to acquire data via using the DataqSdk control
//You can apply this program to all DATAQ products
//------------------------------------------------------------------------------------------

// sdk1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdk1.h"
#include "sdk1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	//DDX_Control(pDX, IDC_DATAQSDKCTRL1, m_sdk);
	//DDX_Control(pDX, IDC_DQCHARTCTRL1, m_chart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSdk1Dlg dialog

CSdk1Dlg::CSdk1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSdk1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSdk1Dlg)
	m_sn = _T("");
	m_pgl = FALSE;
	m_hwrev[0] = '\0';
	m_hwrev[1] = '\0';
	m_fwver = 0;
	m_edit_sample_rate = 2000.0;		//Divided between channels, two channels by default -> 1000 Hz sampling
	m_model = 0;
	m_chart.SetChannel(0);
	m_chart2.SetChannel(1);
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSdk1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSdk1Dlg)
	DDX_Control(pDX, ID_STOP, m_stop_sdk);
	DDX_Control(pDX, ID_START, m_start_sdk);
	DDX_Control(pDX, IDC_DATAQSDKCTRL1, m_dataqsdk);
	DDX_Control(pDX, IDC_DQCHARTCTRL1, m_chart);
	DDX_Control(pDX, IDC_DQCHARTCTRL2, m_chart2);
	DDX_Text(pDX, IDC_EDIT_MODEL, m_model);
	DDX_Text(pDX, IDC_EDIT_SN, m_sn);
	DDX_Text(pDX, IDC_EDIT_PGL, m_pgl);
	DDX_Text(pDX, IDC_EDIT_HWREV, (CString)m_hwrev);
	DDX_Text(pDX, IDC_EDIT_FWVER, m_fwver);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_RATE, m_edit_sample_rate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSdk1Dlg, CDialog)
	//{{AFX_MSG_MAP(CSdk1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, OnStart)
	ON_BN_CLICKED(ID_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSdk1Dlg message handlers

BOOL CSdk1Dlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSdk1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSdk1Dlg::OnPaint() 
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
HCURSOR CSdk1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSdk1Dlg::OnStart() 
{
	VARIANT vaGainList;
	VariantInit(&vaGainList);
	SAFEARRAY * psa;
	short * pshort;
	SAFEARRAYBOUND rgsabound[1];
//#define CHANNELS 8
//	static short GainList[CHANNELS] = {3,2,0,0,0,0,0,0}; //+-100V, 50V, 20V, 10V for DI-1120, ignored for DI-1110 or DI-1100

#define CHANNELS 2
	static short GainList[CHANNELS] = { 1,1 }; //+-10V, 5V, 2.5V, 1.25V for DI-720, from manual page 2


	UpdateData(); 		// Transfer data from controls to variables
	// select which device to use, see "DataqSdkDevice.vbp" or the ActiveX help documentation (dataqxc.chm) for more info
	//m_dataqsdk.SetDeviceDriver("DI330NT.DLL"); //* for DI-1120, DI310NT.DLL for DI-1110, or DI300NT.DLL for DI-1100
	//DLL from c:/Windows/TPDATAQ.INI
	m_dataqsdk.SetDeviceDriver("DI720NT.DLL"); //* for DI-1120, DI310NT.DLL for DI-1110, or DI300NT.DLL for DI-1100
	//m_dataqsdk.SetDeviceID("00000000");   
	m_dataqsdk.SetDeviceID("0");
	// allows user to set attempted SampleRate
	m_dataqsdk.SetSampleRate(m_edit_sample_rate);
	// sets EventPoint - should try to make it multiple of channel count
	m_dataqsdk.SetEventPoint(5*CHANNELS);
	//sets ChannelCount
	m_dataqsdk.SetADChannelCount(CHANNELS);
	// sets gains
	rgsabound[0].cElements=CHANNELS;
	rgsabound[0].lLbound=0;
	psa=SafeArrayCreate(VT_I2,1,rgsabound);
	vaGainList.vt=VT_I2+VT_ARRAY;
	pshort=(short HUGEP *)psa->pvData;
	memmove(pshort,GainList,CHANNELS*sizeof(short));
	vaGainList.parray=psa;
	m_dataqsdk.ADGainList(vaGainList);
	//start acquiring data
	m_dataqsdk.Start();                                     
	//display the actual SampleRate
	m_edit_sample_rate = m_dataqsdk.GetSampleRate();
	// displays ID
	m_model = m_dataqsdk.GetInfoBoardID();              
	//display PGL/PGH model as True/False
	m_pgl = m_dataqsdk.GetInfoPGL();                     
	//display hardware revision letter
	m_hwrev[0] = (char)(m_dataqsdk.GetInfoRev() & 0xFF);                    
	//display firmware version number
	m_fwver = (m_dataqsdk.GetInfoRev() >> 8)/100.0;
	//display the Serial Number  
	m_sn = m_dataqsdk.GetInfoSerial();

	UpdateData(FALSE); 	// Transfer data from variables to controls

}

void CSdk1Dlg::OnStop() 
{
	// Stop acquiring data
	m_dataqsdk.Stop();
	CDialog::OnClose();
	
}

BEGIN_EVENTSINK_MAP(CSdk1Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSdk1Dlg)
	ON_EVENT(CSdk1Dlg, IDC_DATAQSDKCTRL1, 1 /* NewData */, OnNewDataDataqsdkctrl1, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSdk1Dlg::OnNewDataDataqsdkctrl1(short Count)
{
	VARIANT v = m_dataqsdk.GetData();
	FILE *fh = fopen("LOGI.txt", "a");
	FILE *fh2 = fopen("DATADUMP.txt", "a");

	//Handle safearray here
	SAFEARRAY *parray = v.parray;
	HRESULT hr;
	hr = SafeArrayLock(parray);
	if (SUCCEEDED(hr)) {
		//v.vt 0x2000 = array VARIANT (msdn docs),0x02 = VT_I2
		//type 
		fprintf(fh, "%s\tcount %d\ttype %d\tdims %d\telements %ld", "New Data", Count, v.vt, v.parray->cDims, v.parray->cbElements);
		//Print SafeArray bounds stuff
		for (int i = 0; i < v.parray->cDims; ++i) {
			fprintf(fh, "\tdim%d elems %ld lb %ld", i, parray->rgsabound[i].cElements, parray->rgsabound[i].lLbound);
		}
		fprintf(fh, "\n");

		fclose(fh);
		
		
		//DUMP parray data into the text file
		INT16 *pvData = static_cast<INT16*>(parray->pvData);
		//INT16 **pvData = static_cast<INT16**>(parray->pvData);
		int rows = parray->rgsabound[0].cElements;
		int columns = parray->rgsabound[1].cElements;
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < columns; ++c) {
				if (c == 0) {
					fprintf(fh2,"%d", pvData[r*columns+c]);
					//fprintf(fh2, "%d", pvData[r][c]);

				}else {
					fprintf(fh2,"\t%d", pvData[r*columns + c]);
					//fprintf(fh2, "\t%d", pvData[r][c]);
				}
			}
			fprintf(fh2,"\n");
		}
		

		fclose(fh2);
	}
	SafeArrayUnlock(parray);	//Unlock the safearray afterwards
	// get data from buffer and plot it in DQChart
	m_chart.SetChannel(0);
	m_chart2.SetChannel(1);
	m_chart.SetStep(100);
	m_chart2.SetStep(100);
	m_chart.Chart(v);
	m_chart2.Chart(v);
	SafeArrayDestroy(v.parray);
}

