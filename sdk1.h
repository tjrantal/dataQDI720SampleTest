// sdk1.h : main header file for the SDK1 application
//

#if !defined(AFX_SDK1_H__49908748_EF8C_4997_9DCD_43942C018475__INCLUDED_)
#define AFX_SDK1_H__49908748_EF8C_4997_9DCD_43942C018475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSdk1App:
// See sdk1.cpp for the implementation of this class
//

class CSdk1App : public CWinApp
{
public:
	CSdk1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSdk1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSdk1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDK1_H__49908748_EF8C_4997_9DCD_43942C018475__INCLUDED_)
