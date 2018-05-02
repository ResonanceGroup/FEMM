// hviewDoc.h : interface of the ChviewDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "lua.h"
#include "luadebug.h"
#include "luaconsoledlg.h"

extern CFemmApp theApp; //<DP>

extern void lua_baselibopen (lua_State *L);
extern void lua_iolibopen (lua_State *L);
extern void lua_strlibopen (lua_State *L);
extern void lua_mathlibopen (lua_State *L);
extern void lua_dblibopen (lua_State *L);

class ChviewDoc : public CDocument
{
protected: // create from serialization only
	ChviewDoc();
	DECLARE_DYNCREATE(ChviewDoc)

// Attributes
public:

	// General problem attributes
	double	Depth;
	int		LengthUnits;
	double *LengthConv;
	BOOL    ProblemType;
	BOOL	Coords;
	CString ProblemNote;
	BOOL	FirstDraw;
	BOOL	Smooth;
	BOOL	bMultiplyDefinedLabels;
	double  extRo, extRi, extZo;

	double  A_High, A_Low;
	double	A_lb, A_ub;

	double  d_PlotBounds[4][2];
	double  PlotBounds[4][2];


	// Some default behaviors
	CString BinDir;
	int  d_LineIntegralPoints;
	BOOL bHasMask;
	
	// lists of nodes, segments, and block labels
	CArray< hviewtype::CNode, hviewtype::CNode&>             nodelist;
	CArray< hviewtype::CSegment, hviewtype::CSegment&>       linelist;
	CArray< hviewtype::CBlockLabel, hviewtype::CBlockLabel&> blocklist;
	CArray< hviewtype::CArcSegment, hviewtype::CArcSegment&> arclist;

	// CArrays containing the mesh information
	CArray< hviewtype::CMeshNode, hviewtype::CMeshNode&>			meshnode;
	CArray< hviewtype::CElement, hviewtype::CElement&>			meshelem;
	
	// List of elements connected to each node;
	int *NumList;
	int **ConList;

	// lists of properties
	CArray< hviewtype::CMaterialProp, hviewtype::CMaterialProp& > blockproplist;
	CArray< hviewtype::CBoundaryProp, hviewtype::CBoundaryProp& > lineproplist;
	CArray< hviewtype::CPointProp,    hviewtype::CPointProp&    > nodeproplist;	
	CArray< hviewtype::CCircuit,      hviewtype::CCircuit&      > circproplist;

	// list of points in a user-defined contour;
	CArray< CComplex, CComplex& > contour;

	// member functions
	int InTriangle(double x, double y);
	BOOL InTriangleTest(double x, double y, int i);
	BOOL GetPointValues(double x, double y, hviewtype::CPointVals &u);
	BOOL GetPointValues(double x, double y, int k, hviewtype::CPointVals &u);
	void GetLineValues(CXYPlot &p, int PlotType, int npoints);
	void GetElementD(int k);
	void OnReload();
	int ClosestNode(double x, double y);
	CComplex Ctr(int i);
	double ElmArea(int i);
	double ElmArea(hviewtype::CElement *elm);
	void GetPointD(double x, double y, CComplex &D, hviewtype::CElement &elm);
	void GetNodalD(CComplex *d, int i);
	CComplex BlockIntegral(int inttype);
	void LineIntegral(int inttype, double *z);
	int ClosestArcSegment(double x, double y);
	void GetCircle(hviewtype::CArcSegment &asegm,CComplex &c, double &R);
	double ShortestDistanceFromArc(CComplex p, hviewtype::CArcSegment &arc);
	double ShortestDistanceFromSegment(double p, double q, int segm);
	double ShortestDistance(double p, double q, int segm);
	int ClosestSegment(double x, double y);
	BOOL IsSameMaterial(int e1, int e2);
	double AECF(int k);
	double AECF(int k, CComplex p);

	BOOL ScanPreferences();
	void BendContour(double angle, double anglestep);
	CComplex HenrotteVector(int k);
	BOOL IsKosher(int k);
	void FindBoundaryEdges();
	CComplex E(int k);
	CComplex D(int k);
	CComplex e(int k, int i);
	CComplex d(int k, int i);
	
/*	// Tests for whether or not one is inside a user-defined
    // contour; this was really mostly used pre- v3.0, when
	// the areas over which block integrals were taken were
	// defined by a closed, user-generated contour.
	BOOL ContourClosed();
	BOOL SlowInContour(double x, double y);
	BOOL InContour(double x, double y);
	BOOL InContour(CElement &elm);
	BOOL InContour(CComplex p);
	BOOL OnContour(CElement &elm);
	void AvgMaxwell(double &fx, double &fy);
	void AvgMaxwell(double &fx,  double &fy,
					CComplex &f2x, CComplex &f2y); 
*/

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChviewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	// lua extensions
	bool luafired;
	void initalise_lua();
	static int lua_dumpheader(lua_State * L);
	static int lua_getpointvals(lua_State * L);
	static int lua_exitpost(lua_State * L);
	static int lua_addcontour(lua_State * L);
	static int lua_clearcontour(lua_State * L);
	static int lua_lineintegral(lua_State * L);	
	static int lua_selectblock(lua_State * L);
	static int lua_groupselectblock(lua_State * L);
	static int lua_blockintegral(lua_State * L);
	static int lua_clearblock(lua_State * L);
	static int lua_zoomout(lua_State * L);
	static int lua_zoomin(lua_State * L);
	static int lua_zoomnatural(lua_State * L);
	static int lua_hidemesh(lua_State * L);
	static int lua_showmesh(lua_State * L);
	static int lua_showgrid(lua_State * L);
	static int lua_hidegrid(lua_State * L);
	static int lua_showdensity(lua_State * L);
	static int lua_hidedensity(lua_State * L);
	static int lua_hidecountour(lua_State * L);
	static int lua_showcountour(lua_State * L);
	static int lua_zoom(lua_State * L);
	static int lua_smoothing(lua_State * L);
	static int lua_hidepoints(lua_State * L);
	static int lua_showpoints(lua_State * L);
	static int lua_gridsnap(lua_State * L);
	static int lua_setgrid(lua_State * L);
	static int lua_getprobleminfo(lua_State * L);
	static int lua_savebitmap(lua_State * L);
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC) ;
	static int lua_getcircuitprops(lua_State *L);
	static int lua_saveWMF(lua_State *L);
	static int lua_refreshview(lua_State *L);
	static int lua_selectline(lua_State *L);
	static int lua_seteditmode(lua_State *L);
	static int lua_bendcontour(lua_State *L);
	static int lua_makeplot(lua_State *L);
	static int lua_unselectall(lua_State *L);
	static int lua_selectconductor(lua_State *L);
	static int lua_shownames(lua_State * L);
	static int lua_vectorplot(lua_State * L);
	static int lua_reload(lua_State *L);
	static int lua_switchfocus(lua_State *L);
	static int luaResize(lua_State *L);
	static int luaMinimize(lua_State *L);
	static int luaMaximize(lua_State *L);
	static int luaRestore(lua_State *L);
	static int lua_gettitle(lua_State *L);

	// commands to access low-level information through Lua
	static int lua_numnodes(lua_State *L);
	static int lua_numelements(lua_State *L);
	static int lua_getnode(lua_State *L);
	static int lua_getelement(lua_State *L);

	virtual ~ChviewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(ChviewDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:

};

/////////////////////////////////////////////////////////////////////////////
char* StripKey(char *c);
