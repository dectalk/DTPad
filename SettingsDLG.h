#if !defined(AFX_SETTINGSDLG_H__E93EDEF5_1F07_46E1_BB87_7AF6BC0B5375__INCLUDED_)
#define AFX_SETTINGSDLG_H__E93EDEF5_1F07_46E1_BB87_7AF6BC0B5375__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingsDLG dialog

class CSettingsDLG : public CDialog
{
// Construction
public:
	CSettingsDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDLG)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_AudioDevice;
	CButton	m_OwnDevice;
	CComboBox	m_AudioFormat;
	CComboBox	m_LogMode;
	CButton	m_StartupSpeak;
	CEdit	m_StartupMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__E93EDEF5_1F07_46E1_BB87_7AF6BC0B5375__INCLUDED_)
