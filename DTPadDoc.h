// DTPadDoc.h : interface of the CDTPadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DTPADDOC_H__FED399E4_E4C4_408E_B779_9EAAF353869D__INCLUDED_)
#define AFX_DTPADDOC_H__FED399E4_E4C4_408E_B779_9EAAF353869D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDTPadDoc : public CDocument, public CUndo
{
protected: // create from serialization only
	CDTPadDoc();
	DECLARE_DYNCREATE(CDTPadDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTPadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents() {};
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDTPadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDTPadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTPADDOC_H__FED399E4_E4C4_408E_B779_9EAAF353869D__INCLUDED_)
