// sdk1Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "dataqsdk.h"
#include "dqchart.h"
//}}AFX_INCLUDES

#if !defined(AFX_SDK1DLG_H__D6AF4914_9AA6_4EA0_B8C2_4F5742062A47__INCLUDED_)
#define AFX_SDK1DLG_H__D6AF4914_9AA6_4EA0_B8C2_4F5742062A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSdk1Dlg dialog

class CSdk1Dlg : public CDialog
{
// Construction
public:
	CSdk1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSdk1Dlg)
	enum { IDD = IDD_SDK1_DIALOG };
	CButton	m_stop_sdk;
	CButton	m_start_sdk;
	CDataqSdk	m_dataqsdk;
	CDQChart	m_chart;
	CDQChart	m_chart2;
	CString	m_sn;
	BOOL	m_pgl;
	char	m_hwrev[2];
	double	m_fwver;
	double	m_edit_sample_rate;
	short	m_model;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSdk1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSdk1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnNewDataDataqsdkctrl1(short Count);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDK1DLG_H__D6AF4914_9AA6_4EA0_B8C2_4F5742062A47__INCLUDED_)
