// LIntDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLIntDlg dialog

class CLIntDlg : public CDialog
{
// Construction
public:
	CLIntDlg(CWnd* pParent = NULL);   // standard constructor

	int linttype;

// Dialog Data
	//{{AFX_DATA(CLIntDlg)
	enum { IDD = IDD_LINEINT };
	CComboBox	m_inttype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLIntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLIntDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
