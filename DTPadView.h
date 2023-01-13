// DTPadView.h : interface of the CDTPadView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DTPADVIEW_H__FDB1DA2C_3042_4AEA_B72C_1B80A3C34D54__INCLUDED_)
#define AFX_DTPADVIEW_H__FDB1DA2C_3042_4AEA_B72C_1B80A3C34D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include "TTSAPI.H"
#include "TTSID.h"

class CDTPadView : public CEditView
{
protected: // create from serialization only
	CDTPadView();
	DECLARE_DYNCREATE(CDTPadView)

// Attributes
public:
	CDTPadDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTPadView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnClearDocument();
	virtual void OnUpdateClearDocument(CCmdUI* pCmdUI);
	virtual BOOL OnEditChange();
	virtual void OnEditUndo();
	virtual void OnUpdateEditUndo(CCmdUI* pCmdUI);
	virtual void OnEditRedo();
	virtual void OnUpdateEditRedo(CCmdUI* pCmdUI);
	virtual void OnSpeakDocument();
	virtual void OnSpeakSelected();
	virtual void OnUpdateSpeak(CCmdUI* pCmdUI);
	virtual void OnPauseResume();
	virtual void OnUpdatePauseResume(CCmdUI* pCmdUI);
	virtual void OnStopSpeech();
	virtual void OnCreateWAV();
	virtual void OnCreateRaw();
	virtual void OnCreateLog();
	virtual void OnResetSpeech();
	virtual void OnLoadDictionary();
	virtual void OnUnloadDictionary();
	virtual void OnVersionInfo();
	virtual void OnSpeakFaster();
	virtual void OnSpeakSlower();
	virtual void OnNextVoice();
	virtual void OnPreviousVoice();
	virtual void OnSettings();
	virtual void OnLoadDLL();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDTPadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	typedef MMRESULT f_TextToSpeechStartupEx(LPTTS_HANDLE_T*, UINT, DWORD, VOID(*DtCallbackRoutine)(LONG, LONG, DWORD, UINT), LONG);
	f_TextToSpeechStartupEx *TextToSpeechStartupEx_func;
	typedef MMRESULT f_TextToSpeechGetStatus(LPTTS_HANDLE_T, LPDWORD, LPDWORD, DWORD);
	f_TextToSpeechGetStatus *TextToSpeechGetStatus_func;
	typedef MMRESULT f_TextToSpeechGetCaps(LPTTS_CAPS_T);
	f_TextToSpeechGetCaps *TextToSpeechGetCaps_func;
#ifdef UNDER_CE
	typedef ULONG f_TextToSpeechVersion(LPTSTR*);
#else
	typedef ULONG f_TextToSpeechVersion(LPSTR*);
#endif
	f_TextToSpeechVersion *TextToSpeechVersion_func;
	typedef MMRESULT f_TextToSpeechAddBuffer(LPTTS_HANDLE_T, LPTTS_BUFFER_T);
	f_TextToSpeechAddBuffer *TextToSpeechAddBuffer_func;
	typedef MMRESULT f_TextToSpeechReturnBuffer(LPTTS_HANDLE_T, LPTTS_BUFFER_T*);
	f_TextToSpeechReturnBuffer *TextToSpeechReturnBuffer_func;
	typedef MMRESULT f_TextToSpeechOpenInMemory(LPTTS_HANDLE_T, DWORD);
	f_TextToSpeechOpenInMemory *TextToSpeechOpenInMemory_func;
	typedef MMRESULT f_TextToSpeechCloseInMemory(LPTTS_HANDLE_T);
	f_TextToSpeechCloseInMemory *TextToSpeechCloseInMemory_func;
#ifdef UNDER_CE
	typedef MMRESULT f_TextToSpeechOpenWaveOutFile(LPTTS_HANDLE_T, wchar_t *, DWORD);
#else
	typedef MMRESULT f_TextToSpeechOpenWaveOutFile(LPTTS_HANDLE_T, char *, DWORD);
#endif
	f_TextToSpeechOpenWaveOutFile *TextToSpeechOpenWaveOutFile_func;
	typedef MMRESULT f_TextToSpeechCloseWaveOutFile(LPTTS_HANDLE_T);
	f_TextToSpeechCloseWaveOutFile *TextToSpeechCloseWaveOutFile_func;
#ifdef UNDER_CE
	typedef MMRESULT f_TextToSpeechOpenLogFile(LPTTS_HANDLE_T, LPTSTR, DWORD);
#else
	typedef MMRESULT f_TextToSpeechOpenLogFile(LPTTS_HANDLE_T, LPSTR, DWORD);
#endif
	f_TextToSpeechOpenLogFile *TextToSpeechOpenLogFile_func;
	typedef MMRESULT f_TextToSpeechCloseLogFile(LPTTS_HANDLE_T);
	f_TextToSpeechCloseLogFile *TextToSpeechCloseLogFile_func;
	typedef MMRESULT f_TextToSpeechLoadUserDictionary(LPTTS_HANDLE_T, char *);
	f_TextToSpeechLoadUserDictionary *TextToSpeechLoadUserDictionary_func;
	typedef MMRESULT f_TextToSpeechUnloadUserDictionary(LPTTS_HANDLE_T);
	f_TextToSpeechUnloadUserDictionary *TextToSpeechUnloadUserDictionary_func;
	typedef MMRESULT f_TextToSpeechSetRate(LPTTS_HANDLE_T, DWORD);
	f_TextToSpeechSetRate *TextToSpeechSetRate_func;
	typedef MMRESULT f_TextToSpeechGetRate(LPTTS_HANDLE_T, LPDWORD);
	f_TextToSpeechGetRate *TextToSpeechGetRate_func;
	typedef MMRESULT f_TextToSpeechSetSpeaker(LPTTS_HANDLE_T, SPEAKER_T);
	f_TextToSpeechSetSpeaker *TextToSpeechSetSpeaker_func;
	typedef MMRESULT f_TextToSpeechGetSpeaker(LPTTS_HANDLE_T, LPSPEAKER_T);
	f_TextToSpeechGetSpeaker *TextToSpeechGetSpeaker_func;
	typedef MMRESULT f_TextToSpeechSetLanguage(LPTTS_HANDLE_T, LANGUAGE_T);
	f_TextToSpeechSetLanguage *TextToSpeechSetLanguage_func;
	typedef MMRESULT f_TextToSpeechGetLanguage(LPTTS_HANDLE_T, LPLANGUAGE_T);
	f_TextToSpeechGetLanguage *TextToSpeechGetLanguage_func;
#ifdef UNDER_CE
	typedef MMRESULT f_TextToSpeechSpeak(LPTTS_HANDLE_T, const wchar_t*, DWORD);
#else
	typedef MMRESULT f_TextToSpeechSpeak(LPTTS_HANDLE_T, const LPSTR, DWORD);
#endif
	f_TextToSpeechSpeak *TextToSpeechSpeak_func;
	typedef MMRESULT f_TextToSpeechPause(LPTTS_HANDLE_T);
	f_TextToSpeechPause *TextToSpeechPause_func;
	typedef MMRESULT f_TextToSpeechResume(LPTTS_HANDLE_T);
	f_TextToSpeechResume *TextToSpeechResume_func;
	typedef MMRESULT f_TextToSpeechSync(LPTTS_HANDLE_T);
	f_TextToSpeechSync *TextToSpeechSync_func;
	typedef MMRESULT f_TextToSpeechReset(LPTTS_HANDLE_T, BOOL);
	f_TextToSpeechReset *TextToSpeechReset_func;
	typedef MMRESULT f_TextToSpeechShutdown(LPTTS_HANDLE_T);
	f_TextToSpeechShutdown *TextToSpeechShutdown_func;
	HINSTANCE dtlib;
	bool LoadDECtalkDLL(LPSTR libname);

	LPTTS_HANDLE_T engine;
	TTS_CAPS_T caps;

	UINT BufferMessage;
	TTS_BUFFER_T buffer;
	BYTE samples[8192];
	FILE *pcmfile;
	static void callback(LONG LParam1, LONG lParam2, DWORD user, UINT msg);

	bool paused;

// Generated message map functions
protected:
	//{{AFX_MSG(CDTPadView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DTPadView.cpp
inline CDTPadDoc* CDTPadView::GetDocument()
   { return (CDTPadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTPADVIEW_H__FDB1DA2C_3042_4AEA_B72C_1B80A3C34D54__INCLUDED_)
