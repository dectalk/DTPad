// SettingsDLG.cpp : implementation file
//

#include "stdafx.h"
#include "DTPad.h"
#include "SettingsDLG.h"

#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDLG dialog


CSettingsDLG::CSettingsDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSettingsDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDLG)
	DDX_Control(pDX, IDC_DEVICE, m_AudioDevice);
	DDX_Control(pDX, IDC_OWN, m_OwnDevice);
	DDX_Control(pDX, IDC_FORMAT, m_AudioFormat);
	DDX_Control(pDX, IDC_LOGMODE, m_LogMode);
	DDX_Control(pDX, IDC_STARTSPEAK, m_StartupSpeak);
	DDX_Control(pDX, IDC_STARTMSG, m_StartupMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDLG, CDialog)
	//{{AFX_MSG_MAP(CSettingsDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDLG message handlers

BOOL CSettingsDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	for (UINT i = 0; i < waveOutGetNumDevs(); i++)
	{
		WAVEOUTCAPS waveoutcaps;
		memset(&waveoutcaps, 0, sizeof(waveoutcaps));
		waveOutGetDevCaps(i, &waveoutcaps, sizeof(waveoutcaps));
		m_AudioDevice.AddString(waveoutcaps.szPname);
	}
	m_AudioFormat.AddString("11 kHz, 16-Bit, Mono");
	m_AudioFormat.AddString("11 kHz, 8-Bit, Mono");
	m_AudioFormat.AddString("8 kHz, Mu-Law, Mono");
	m_LogMode.AddString("Phonemes");
	m_LogMode.AddString("Syllables");
	m_LogMode.AddString("Text");
	char filename[MAX_PATH];
	memset(filename, 0, sizeof(filename));
	SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
	strncat(filename, "\\DTPad.ini", MAX_PATH);
	m_AudioDevice.SetCurSel(GetPrivateProfileInt("Settings", "AudioDevice", 0, filename));
	m_OwnDevice.SetCheck(GetPrivateProfileInt("Settings", "OwnDevice", 0, filename));
	m_AudioFormat.SetCurSel(GetPrivateProfileInt("Settings", "AudioFormat", 0, filename));
	m_LogMode.SetCurSel(GetPrivateProfileInt("Settings", "LogMode", 0, filename));
	m_StartupSpeak.SetCheck(GetPrivateProfileInt("Settings", "StartupSpeak", 0, filename));
	char msg[MAX_PATH];
	memset(msg, 0, sizeof(msg));
	GetPrivateProfileString("Settings", "StartupMessage", "Welcome to DTPad!", msg, MAX_PATH, filename);
	CString text = msg;
	m_StartupMessage.SetWindowText(text);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDLG::OnOK() 
{
	char filename[MAX_PATH];
	memset(filename, 0, sizeof(filename));
	SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
	strncat(filename, "\\DTPad.ini", MAX_PATH);
	char str[MAX_PATH];
	memset(str, 0, sizeof(str));
	sprintf(str, "%d", m_AudioDevice.GetCurSel());
	WritePrivateProfileString("Settings", "AudioDevice", str, filename);
	memset(str, 0, sizeof(str));
	sprintf(str, "%d", m_OwnDevice.GetCheck());
	WritePrivateProfileString("Settings", "OwnDevice", str, filename);
	memset(str, 0, sizeof(str));
	sprintf(str, "%d", m_AudioFormat.GetCurSel());
	WritePrivateProfileString("Settings", "AudioFormat", str, filename);
	memset(str, 0, sizeof(str));
	sprintf(str, "%d", m_LogMode.GetCurSel());
	WritePrivateProfileString("Settings", "LogMode", str, filename);
	memset(str, 0, sizeof(str));
	sprintf(str, "%d", m_StartupSpeak.GetCheck());
	WritePrivateProfileString("Settings", "StartupSpeak", str, filename);
	CString text;
	m_StartupMessage.GetWindowText(text);
	WritePrivateProfileString("Settings", "StartupMessage", text.GetBuffer(0), filename);
	CDialog::OnOK();
}
