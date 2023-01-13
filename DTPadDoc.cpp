// DTPadDoc.cpp : implementation of the CDTPadDoc class
//

#include "stdafx.h"
#include "DTPad.h"

#include "DTPadDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDTPadDoc

IMPLEMENT_DYNCREATE(CDTPadDoc, CDocument)

BEGIN_MESSAGE_MAP(CDTPadDoc, CDocument)
	//{{AFX_MSG_MAP(CDTPadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTPadDoc construction/destruction

CDTPadDoc::CDTPadDoc()
{
	// TODO: add one-time construction code here

}

CDTPadDoc::~CDTPadDoc()
{
}

BOOL CDTPadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	CheckPoint();
	return TRUE;
}

BOOL CDTPadDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	CheckPoint();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDTPadDoc serialization

void CDTPadDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDTPadDoc diagnostics

#ifdef _DEBUG
void CDTPadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDTPadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDTPadDoc commands
