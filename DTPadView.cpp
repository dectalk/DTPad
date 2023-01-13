// DTPadView.cpp : implementation of the CDTPadView class
//

#include "stdafx.h"
#include "DTPad.h"

#include "DTPadDoc.h"
#include "DTPadView.h"

#include"SettingsDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDTPadView

IMPLEMENT_DYNCREATE(CDTPadView, CEditView)

BEGIN_MESSAGE_MAP(CDTPadView, CEditView)
	//{{AFX_MSG_MAP(CDTPadView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnClearDocument)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateClearDocument)
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditChange)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_TTS_SPEAKDOC, OnSpeakDocument)
	ON_COMMAND(ID_TTS_SPEAKSEL, OnSpeakSelected)
	ON_UPDATE_COMMAND_UI(ID_TTS_SPEAKDOC, OnUpdateSpeak)
	ON_UPDATE_COMMAND_UI(ID_TTS_SPEAKSEL, OnUpdateSpeak)
	ON_COMMAND(ID_TTS_PAUSE, OnPauseResume)
	ON_UPDATE_COMMAND_UI(ID_TTS_PAUSE, OnUpdatePauseResume)
	ON_COMMAND(ID_TTS_STOP, OnStopSpeech)
	ON_COMMAND(ID_TTS_CREATEWAV, OnCreateWAV)
	ON_COMMAND(ID_TTS_CREATERAW, OnCreateRaw)
	ON_COMMAND(ID_TTS_CREATELOG, OnCreateLog)
	ON_COMMAND(ID_TTS_RESET, OnResetSpeech)
	ON_COMMAND(ID_TTS_LOADDICT, OnLoadDictionary)
	ON_COMMAND(ID_TTS_UNLOADDICT, OnUnloadDictionary)
	ON_COMMAND(ID_TTS_VERSION, OnVersionInfo)
	ON_COMMAND(ID_TTS_RATEUP, OnSpeakFaster)
	ON_COMMAND(ID_TTS_RATEDOWN, OnSpeakSlower)
	ON_COMMAND(ID_TTS_NEXTVOICE, OnNextVoice)
	ON_COMMAND(ID_TTS_PREVVOICE, OnPreviousVoice)
	ON_COMMAND(ID_TTS_SETTINGS, OnSettings)
	ON_COMMAND(ID_TTS_LOADDLL, OnLoadDLL)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTPadView construction/destruction

CDTPadView::CDTPadView()
{
	// TODO: add construction code here

	TextToSpeechStartupEx_func = NULL;
	TextToSpeechGetStatus_func = NULL;
	TextToSpeechGetCaps_func = NULL;
	TextToSpeechVersion_func = NULL;
	TextToSpeechAddBuffer_func = NULL;
	TextToSpeechReturnBuffer_func = NULL;
	TextToSpeechOpenInMemory_func = NULL;
	TextToSpeechCloseInMemory_func = NULL;
	TextToSpeechOpenWaveOutFile_func = NULL;
	TextToSpeechCloseWaveOutFile_func = NULL;
	TextToSpeechOpenLogFile_func = NULL;
	TextToSpeechCloseLogFile_func = NULL;
	TextToSpeechLoadUserDictionary_func = NULL;
	TextToSpeechUnloadUserDictionary_func = NULL;
	TextToSpeechSetRate_func = NULL;
	TextToSpeechGetRate_func = NULL;
	TextToSpeechSetSpeaker_func = NULL;
	TextToSpeechGetSpeaker_func = NULL;
	TextToSpeechSetLanguage_func = NULL;
	TextToSpeechGetLanguage_func = NULL;
	TextToSpeechSpeak_func = NULL;
	TextToSpeechPause_func = NULL;
	TextToSpeechResume_func = NULL;
	TextToSpeechSync_func = NULL;
	TextToSpeechReset_func = NULL;
	TextToSpeechShutdown_func = NULL;
	dtlib = NULL;
	engine = NULL;
	memset(&caps, 0, sizeof(caps));
	BufferMessage = 0;
	memset(&buffer, 0, sizeof(buffer));
	memset(samples, 0, sizeof(samples));
	pcmfile = NULL;
	paused = false;

	char filename[MAX_PATH];
	memset(filename, 0, sizeof(filename));
	SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
	strncat(filename, "\\DTPad.ini", MAX_PATH);
	char curdir[MAX_PATH];
	memset(curdir, 0, sizeof(curdir));
	GetCurrentDirectory(MAX_PATH, curdir);
	char libdir[MAX_PATH];
	memset(libdir, 0, sizeof(libdir));
	GetPrivateProfileString("Settings", "DLLDir", curdir, libdir, MAX_PATH, filename);
	char libname[MAX_PATH];
	memset(libname, 0, sizeof(libname));
	GetPrivateProfileString("Settings", "DECtalkDLL", "dectalk.dll", libname, MAX_PATH, filename);
	SetCurrentDirectory(libdir);
	if (!LoadDECtalkDLL(libname))
	{
		if (MessageBox("No DECtalk DLL found! Would you like to load one now?", "Error", MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			TCHAR szFilters[] = "DLL Files (*.DLL)|*.DLL|All Files (*.*)|*.*||";
			CFileDialog fileDialog(TRUE, "DLL", "*.DLL", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
			fileDialog.m_ofn.lpstrTitle = "Select Default DECtalk DLL";
			if (fileDialog.DoModal() == IDOK)
			{
				CString pathName = fileDialog.GetPathName();
				if (!LoadDECtalkDLL(pathName.GetBuffer(0)))
				{
					char msg[MAX_PATH];
					sprintf(msg, "Failed to open %s!", pathName.GetBuffer(0));
					MessageBox(msg, "Error", MB_ICONERROR);
					return;
				}
				memset(curdir, 0, sizeof(curdir));
				GetCurrentDirectory(MAX_PATH, curdir);
				WritePrivateProfileString("Settings", "DECtalkDLL", pathName.GetBuffer(0), filename);
				WritePrivateProfileString("Settings", "DLLDir", curdir, filename);
			}
		}
	}

}

CDTPadView::~CDTPadView()
{
	if (engine)
	{
		TextToSpeechUnloadUserDictionary_func(engine);
		TextToSpeechShutdown_func(engine);
		engine = NULL;
		FreeLibrary(dtlib);
		dtlib = NULL;
	}
}

BOOL CDTPadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDTPadView drawing

void CDTPadView::OnDraw(CDC* pDC)
{
	CDTPadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDTPadView printing

BOOL CDTPadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CDTPadView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDTPadView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CDTPadView::OnClearDocument()
{
	CEditView::OnEditSelectAll();
	CEditView::OnEditClear();
}

void CDTPadView::OnUpdateClearDocument(CCmdUI* pCmdUI)
{
	if (CEditView::GetBufferLength() != 0)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

BOOL CDTPadView::OnEditChange()
{
	CDTPadDoc* pDoc = GetDocument();
	pDoc->CheckPoint();
	return CEditView::OnEditChange();
}

void CDTPadView::OnEditUndo()
{
	CDTPadDoc* pDoc = GetDocument();
	pDoc->Undo();
}

void CDTPadView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	CDTPadDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanUndo());
}

void CDTPadView::OnEditRedo()
{
	CDTPadDoc* pDoc = GetDocument();
	pDoc->Redo();
}

void CDTPadView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	CDTPadDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanRedo());
}

bool CDTPadView::LoadDECtalkDLL(LPSTR libname)
{
	if (dtlib && engine)
	{
		TextToSpeechUnloadUserDictionary_func(engine);
		TextToSpeechShutdown_func(engine);
		engine = NULL;
		FreeLibrary(dtlib);
		dtlib = NULL;
	}
	dtlib = LoadLibrary(libname);
	if (!dtlib)
	{
		return false;
	}
	TextToSpeechStartupEx_func = (f_TextToSpeechStartupEx*)GetProcAddress(dtlib, "TextToSpeechStartupEx");
	TextToSpeechGetStatus_func = (f_TextToSpeechGetStatus*)GetProcAddress(dtlib, "TextToSpeechGetStatus");
	TextToSpeechGetCaps_func = (f_TextToSpeechGetCaps*)GetProcAddress(dtlib, "TextToSpeechGetCaps");
	TextToSpeechVersion_func = (f_TextToSpeechVersion*)GetProcAddress(dtlib, "TextToSpeechVersion");
	TextToSpeechAddBuffer_func = (f_TextToSpeechAddBuffer*)GetProcAddress(dtlib, "TextToSpeechAddBuffer");
	TextToSpeechReturnBuffer_func = (f_TextToSpeechReturnBuffer*)GetProcAddress(dtlib, "TextToSpeechReturnBuffer");
	TextToSpeechOpenInMemory_func = (f_TextToSpeechOpenInMemory*)GetProcAddress(dtlib, "TextToSpeechOpenInMemory");
	TextToSpeechCloseInMemory_func = (f_TextToSpeechCloseInMemory*)GetProcAddress(dtlib, "TextToSpeechCloseInMemory");
	TextToSpeechOpenWaveOutFile_func = (f_TextToSpeechOpenWaveOutFile*)GetProcAddress(dtlib, "TextToSpeechOpenWaveOutFile");
	TextToSpeechCloseWaveOutFile_func = (f_TextToSpeechCloseWaveOutFile*)GetProcAddress(dtlib, "TextToSpeechCloseWaveOutFile");
	TextToSpeechOpenLogFile_func = (f_TextToSpeechOpenLogFile*)GetProcAddress(dtlib, "TextToSpeechOpenLogFile");
	TextToSpeechCloseLogFile_func = (f_TextToSpeechCloseLogFile*)GetProcAddress(dtlib, "TextToSpeechCloseLogFile");
	TextToSpeechLoadUserDictionary_func = (f_TextToSpeechLoadUserDictionary*)GetProcAddress(dtlib, "TextToSpeechLoadUserDictionary");
	TextToSpeechUnloadUserDictionary_func = (f_TextToSpeechUnloadUserDictionary*)GetProcAddress(dtlib, "TextToSpeechUnloadUserDictionary");
	TextToSpeechSetRate_func = (f_TextToSpeechSetRate*)GetProcAddress(dtlib, "TextToSpeechSetRate");
	TextToSpeechGetRate_func = (f_TextToSpeechGetRate*)GetProcAddress(dtlib, "TextToSpeechGetRate");
	TextToSpeechSetSpeaker_func = (f_TextToSpeechSetSpeaker*)GetProcAddress(dtlib, "TextToSpeechSetSpeaker");
	TextToSpeechGetSpeaker_func = (f_TextToSpeechGetSpeaker*)GetProcAddress(dtlib, "TextToSpeechGetSpeaker");
	TextToSpeechSetLanguage_func = (f_TextToSpeechSetLanguage*)GetProcAddress(dtlib, "TextToSpeechSetLanguage");
	TextToSpeechGetLanguage_func = (f_TextToSpeechGetLanguage*)GetProcAddress(dtlib, "TextToSpeechGetLanguage");
	TextToSpeechSpeak_func = (f_TextToSpeechSpeak*)GetProcAddress(dtlib, "TextToSpeechSpeak");
	TextToSpeechPause_func = (f_TextToSpeechPause*)GetProcAddress(dtlib, "TextToSpeechPause");
	TextToSpeechResume_func = (f_TextToSpeechResume*)GetProcAddress(dtlib, "TextToSpeechResume");
	TextToSpeechSync_func = (f_TextToSpeechSync*)GetProcAddress(dtlib, "TextToSpeechSync");
	TextToSpeechReset_func = (f_TextToSpeechReset*)GetProcAddress(dtlib, "TextToSpeechReset");
	TextToSpeechShutdown_func = (f_TextToSpeechShutdown*)GetProcAddress(dtlib, "TextToSpeechShutdown");
	if (!TextToSpeechStartupEx_func || !TextToSpeechGetStatus_func || !TextToSpeechGetCaps_func || !TextToSpeechVersion_func || !TextToSpeechAddBuffer_func || !TextToSpeechReturnBuffer_func || !TextToSpeechOpenInMemory_func || !TextToSpeechCloseInMemory_func || !TextToSpeechOpenWaveOutFile_func || !TextToSpeechCloseWaveOutFile_func || !TextToSpeechOpenLogFile_func || !TextToSpeechCloseLogFile_func || !TextToSpeechLoadUserDictionary_func || !TextToSpeechUnloadUserDictionary_func || !TextToSpeechSetRate_func || !TextToSpeechGetRate_func || !TextToSpeechSetSpeaker_func || !TextToSpeechGetSpeaker_func || !TextToSpeechSetLanguage_func || !TextToSpeechGetLanguage_func || !TextToSpeechSpeak_func || !TextToSpeechPause_func || !TextToSpeechResume_func || !TextToSpeechSync_func || !TextToSpeechReset_func || !TextToSpeechShutdown_func)
	{
		return false;
	}
	TextToSpeechGetCaps_func(&caps);
	DWORD device = WAVE_MAPPER;
	DWORD flags = 0;
	char filename[MAX_PATH];
	memset(filename, 0, sizeof(filename));
	SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
	strncat(filename, "\\DTPad.ini", MAX_PATH);
	device = GetPrivateProfileInt("Settings", "AudioDevice", 0, filename);
	if (GetPrivateProfileInt("Settings", "OwnDevice", 0, filename))
	{
		flags = OWN_AUDIO_DEVICE;
	}
	if (TextToSpeechStartupEx_func(&engine, device, flags, callback, (LONG)this))
	{
		if (TextToSpeechStartupEx_func(&engine, WAVE_MAPPER, flags, callback, (LONG)this))
		{
			return false;
		}
	}
	BufferMessage = RegisterWindowMessage("DECtalkBufferMessage");
	buffer.lpData = (LPSTR)samples;
	buffer.dwMaximumBufferLength = sizeof(samples);
	if (GetPrivateProfileInt("Settings", "StartupSpeak", 0, filename))
	{
		char msg[MAX_PATH];
		memset(msg, 0, sizeof(msg));
		GetPrivateProfileString("Settings", "StartupMessage", "Welcome to DTPad!", msg, MAX_PATH, filename);
		TextToSpeechSpeak_func(engine, msg, TTS_FORCE);
	}
	return true;
}

void CDTPadView::OnSpeakDocument()
{
	CString text;
	GetWindowText(text);
	if (engine)
	{
		if (paused)
		{
			TextToSpeechResume_func(engine);
			paused = false;
		}
		TextToSpeechSpeak_func(engine, text.GetBuffer(0), TTS_FORCE);
	}
}

void CDTPadView::OnSpeakSelected()
{
	CString text;
	GetSelectedText(text);
	if (engine)
	{
		if (paused)
		{
			TextToSpeechResume_func(engine);
			paused = false;
		}
		TextToSpeechSpeak_func(engine, text.GetBuffer(0), TTS_FORCE);
	}
}

void CDTPadView::OnUpdateSpeak(CCmdUI* pCmdUI)
{
	DWORD status = STATUS_SPEAKING;
	DWORD result = 0;
	if (engine)
	{
		TextToSpeechGetStatus_func(engine, &status, &result, 1);
	}
	if (result)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CDTPadView::OnPauseResume()
{
	if (engine)
	{
		if (!paused)
		{
			TextToSpeechPause_func(engine);
			paused = true;
		}
		else
		{
			TextToSpeechResume_func(engine);
			paused = false;
		}
	}
}

void CDTPadView::OnUpdatePauseResume(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(paused);
}

void CDTPadView::OnStopSpeech()
{
	if (engine)
	{
		TextToSpeechReset_func(engine, FALSE);
	}
}

void CDTPadView::OnCreateWAV()
{
	TCHAR szFilters[] = "WAV Files (*.WAV)|*.WAV|All Files (*.*)|*.*||";
	CFileDialog fileDialog(FALSE, "WAV", "*.WAV", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		CString text;
		GetWindowText(text);
		if (engine)
		{
			TextToSpeechReset_func(engine, TRUE);
			DWORD AudioFormat = WAVE_FORMAT_1M16;
			char filename[MAX_PATH];
			memset(filename, 0, sizeof(filename));
			SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
			strncat(filename, "\\DTPad.ini", MAX_PATH);
			switch(GetPrivateProfileInt("Settings", "AudioFormat", 0, filename))
			{
			case 0:
				AudioFormat = WAVE_FORMAT_1M16;
				break;
			case 1:
				AudioFormat = WAVE_FORMAT_1M08;
				break;
			case 2:
				AudioFormat = WAVE_FORMAT_08M08;
				break;
			}
			if (TextToSpeechOpenWaveOutFile_func(engine, pathName.GetBuffer(0), AudioFormat))
			{
				char msg[MAX_PATH];
				sprintf(msg, "Failed to open %s!", pathName.GetBuffer(0));
				MessageBox(msg, "Error", MB_ICONERROR);
				return;
			}
			TextToSpeechSpeak_func(engine, text.GetBuffer(0), TTS_FORCE);
			TextToSpeechSync_func(engine);
			TextToSpeechCloseWaveOutFile_func(engine);
			TextToSpeechReset_func(engine, TRUE);
			char msg[MAX_PATH];
			sprintf(msg, "%s successfully created!", pathName.GetBuffer(0));
			MessageBox(msg, "Information", MB_ICONINFORMATION);
		}
	}
}

void CDTPadView::OnCreateRaw()
{
	TCHAR szFilters[] = "Raw Audio Files (*.RAW)|*.RAW|All Files (*.*)|*.*||";
	CFileDialog fileDialog(FALSE, "RAW", "*.RAW", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		CString text;
		GetWindowText(text);
		pcmfile = fopen(pathName.GetBuffer(0), "wb");
		if (!pcmfile)
		{
			char msg[MAX_PATH];
			sprintf(msg, "Failed to open %s!", pathName.GetBuffer(0));
			MessageBox(msg, "Error", MB_ICONERROR);
			return;
		}
		if (engine)
		{
			TextToSpeechReset_func(engine, TRUE);
			DWORD AudioFormat = WAVE_FORMAT_1M16;
			char filename[MAX_PATH];
			memset(filename, 0, sizeof(filename));
			SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
			strncat(filename, "\\DTPad.ini", MAX_PATH);
			switch(GetPrivateProfileInt("Settings", "AudioFormat", 0, filename))
			{
			case 0:
				AudioFormat = WAVE_FORMAT_1M16;
				break;
			case 1:
				AudioFormat = WAVE_FORMAT_1M08;
				break;
			case 2:
				AudioFormat = WAVE_FORMAT_08M08;
				break;
			}
			TextToSpeechOpenInMemory_func(engine, AudioFormat);
			TextToSpeechAddBuffer_func(engine, &buffer);
			TextToSpeechSpeak_func(engine, text.GetBuffer(0), TTS_FORCE);
			TextToSpeechSync_func(engine);
			TextToSpeechCloseInMemory_func(engine);
			TextToSpeechReset_func(engine, TRUE);
			fclose(pcmfile);
			pcmfile = NULL;
			char msg[MAX_PATH];
			sprintf(msg, "%s successfully created!", pathName.GetBuffer(0));
			MessageBox(msg, "Information", MB_ICONINFORMATION);
		}
	}
}

void CDTPadView::callback(LONG LParam1, LONG lParam2, DWORD user, UINT msg)
{
	CDTPadView *view = (CDTPadView*)user;
	if (msg == view->BufferMessage)
	{
		LPTTS_BUFFER_T buffer = (LPTTS_BUFFER_T)lParam2;
		fwrite(view->samples, 1, buffer->dwBufferLength, view->pcmfile);
		fflush(view->pcmfile);
		view->TextToSpeechAddBuffer_func(view->engine, buffer);
	}
}

void CDTPadView::OnCreateLog()
{
	TCHAR szFilters[] = "Log Files (*.LOG)|*.LOG|All Files (*.*)|*.*||";
	CFileDialog fileDialog(FALSE, "LOG", "*.LOG", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		CString text;
		GetWindowText(text);
		if (engine)
		{
			TextToSpeechReset_func(engine, TRUE);
			DWORD LogMode = LOG_PHONEMES;
			char filename[MAX_PATH];
			memset(filename, 0, sizeof(filename));
			SHGetSpecialFolderPath(NULL, filename, CSIDL_PERSONAL, FALSE);
			strncat(filename, "\\DTPad.ini", MAX_PATH);
			switch(GetPrivateProfileInt("Settings", "LogMode", 0, filename))
			{
			case 0:
				LogMode = LOG_PHONEMES;
				break;
			case 1:
				LogMode = LOG_SYLLABLES;
				break;
			case 2:
				LogMode = LOG_TEXT;
				break;
			}
			if (TextToSpeechOpenLogFile_func(engine, pathName.GetBuffer(0), LogMode))
			{
				char msg[MAX_PATH];
				sprintf(msg, "Failed to open %s!", pathName.GetBuffer(0));
				MessageBox(msg, "Error", MB_ICONERROR);
				return;
			}
			TextToSpeechSpeak_func(engine, text.GetBuffer(0), TTS_FORCE);
			TextToSpeechSync_func(engine);
			TextToSpeechCloseLogFile_func(engine);
			TextToSpeechReset_func(engine, TRUE);
			char msg[MAX_PATH];
			sprintf(msg, "%s successfully created!", pathName.GetBuffer(0));
			MessageBox(msg, "Information", MB_ICONINFORMATION);
		}
	}
}

void CDTPadView::OnResetSpeech()
{
	if (engine)
	{
		TextToSpeechReset_func(engine, TRUE);
		if (!paused)
		{
			TextToSpeechSpeak_func(engine, "Reset speech", TTS_FORCE);
		}
	}
}

void CDTPadView::OnLoadDictionary()
{
	TCHAR szFilters[] = "Dictionary Files (*.DIC)|*.DIC|All Files (*.*)|*.*||";
	CFileDialog fileDialog(TRUE, "DIC", "*.DIC", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		if (engine)
		{
			TextToSpeechUnloadUserDictionary_func(engine);
			if (TextToSpeechLoadUserDictionary_func(engine, pathName.GetBuffer(0)))
			{
				char msg[MAX_PATH];
				sprintf(msg, "Failed to open %s!", pathName.GetBuffer(0));
				MessageBox(msg, "Error", MB_ICONERROR);
			}
		}
	}
}

void CDTPadView::OnUnloadDictionary()
{
	if (engine)
	{
		TextToSpeechUnloadUserDictionary_func(engine);
	}
}

void CDTPadView::OnVersionInfo()
{
	char *versioninfo = NULL;
	TextToSpeechVersion_func(&versioninfo);
	MessageBox(versioninfo, "DECtalk Version Information", MB_ICONINFORMATION);
}

void CDTPadView::OnSpeakFaster()
{
	if (engine)
	{
		TextToSpeechReset_func(engine, FALSE);
		DWORD rate = 0;
		TextToSpeechGetRate_func(engine, &rate);
		rate += 5;
		if (rate > caps.dwMaximumSpeakingRate)
		{
			rate = caps.dwMaximumSpeakingRate;
		}
		TextToSpeechSetRate_func(engine, rate);
		if (!paused)
		{
			char msg[32];
			sprintf(msg, "Rate %d", rate);
			TextToSpeechSpeak_func(engine, msg, TTS_FORCE);
		}
	}
}

void CDTPadView::OnSpeakSlower()
{
	if (engine)
	{
		TextToSpeechReset_func(engine, FALSE);
		DWORD rate = 0;
		TextToSpeechGetRate_func(engine, &rate);
		rate -= 5;
		if (rate < caps.dwMinimumSpeakingRate)
		{
			rate = caps.dwMinimumSpeakingRate;
		}
		TextToSpeechSetRate_func(engine, rate);
		if (!paused)
		{
			char msg[32];
			sprintf(msg, "Rate %d", rate);
			TextToSpeechSpeak_func(engine, msg, TTS_FORCE);
		}
	}
}

const char *voiceNames[9] =
{
	"Paul",
	"Betty",
	"Harry",
	"Frank",
	"Dennis",
	"Kit",
	"Ursula",
	"Rita",
	"Wendy"
};

void CDTPadView::OnNextVoice()
{
	if (engine)
	{
		TextToSpeechReset_func(engine, FALSE);
		DWORD voice = 0;
		TextToSpeechGetSpeaker_func(engine, &voice);
		voice++;
		if (voice > WENDY || voice < PAUL)
		{
			voice = WENDY;
		}
		TextToSpeechSetSpeaker_func(engine, voice);
		if (!paused)
		{
			char msg[32];
			sprintf(msg, "%s", voiceNames[voice]);
			TextToSpeechSpeak_func(engine, msg, TTS_FORCE);
		}
	}
}

void CDTPadView::OnPreviousVoice()
{
	if (engine)
	{
		TextToSpeechReset_func(engine, FALSE);
		DWORD voice = 0;
		TextToSpeechGetSpeaker_func(engine, &voice);
		voice--;
		if (voice > WENDY || voice < PAUL)
		{
			voice = PAUL;
		}
		TextToSpeechSetSpeaker_func(engine, voice);
		if (!paused)
		{
			char msg[32];
			sprintf(msg, "%s", voiceNames[voice]);
			TextToSpeechSpeak_func(engine, msg, TTS_FORCE);
		}
	}
}

void CDTPadView::OnSettings()
{
	CSettingsDLG dlg;
	dlg.DoModal();
}

void CDTPadView::OnLoadDLL()
{
	TCHAR szFilters[] = "DLL Files (*.DLL)|*.DLL|All Files (*.*)|*.*||";
	CFileDialog fileDialog(TRUE, "DLL", "*.DLL", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		if (!LoadDECtalkDLL(pathName.GetBuffer(0)))
		{
			char msg[MAX_PATH];
			sprintf(msg, "Failed to open %s!", pathName.GetBuffer(0));
			MessageBox(msg, "Error", MB_ICONERROR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDTPadView diagnostics

#ifdef _DEBUG
void CDTPadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDTPadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDTPadDoc* CDTPadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDTPadDoc)));
	return (CDTPadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDTPadView message handlers
