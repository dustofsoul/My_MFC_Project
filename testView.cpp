// 1401150312View.cpp : implementation of the CMy1401150312View class
//
#include<cmath>

#include "stdafx.h"
#include "1401150312.h"

#include "1401150312Doc.h"
#include "1401150312View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy1401150312View

IMPLEMENT_DYNCREATE(CMy1401150312View, CView)

BEGIN_MESSAGE_MAP(CMy1401150312View, CView)
	//{{AFX_MSG_MAP(CMy1401150312View)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(ID_DRAW_OVAL, OnDrawOval)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1401150312View construction/destruction

CMy1401150312View::CMy1401150312View()
{
	// TODO: add construction code here

}

CMy1401150312View::~CMy1401150312View()
{
}

BOOL CMy1401150312View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy1401150312View drawing

void CMy1401150312View::OnDraw(CDC* pDC)
{
	CMy1401150312Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMy1401150312View printing

BOOL CMy1401150312View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy1401150312View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy1401150312View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy1401150312View diagnostics

#ifdef _DEBUG
void CMy1401150312View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1401150312View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1401150312Doc* CMy1401150312View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1401150312Doc)));
	return (CMy1401150312Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////菜单响应
// CMy1401150312View message handlers


void CMy1401150312View::OnDrawLine() 
{
	// TODO: Add your command handler code here
	flag=true;
	drawtype=1;
}

void CMy1401150312View::OnDrawCircle() 
{
	// TODO: Add your command handler code here
	flag =true;
	drawtype=2;
}

void CMy1401150312View::OnDrawOval() 
{
	// TODO: Add your command handler code here
	flag=true;
	drawtype=3;
}

/////////////////////////////////////////////////////////////////////////////鼠标响应

void CMy1401150312View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(flag==true)
		startpoint=point;
	
	CView::OnLButtonDown(nFlags, point);
}

void CMy1401150312View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(flag==true){
		endpoint=point;
//debug
//		flag=false;

//use lineto
//		CClientDC dc(this);
//		dc.MoveTo(startpoint.x,startpoint.y);
//		dc.LineTo(endpoint.x,endpoint.y);
		switch(drawtype){
		case 1:
			BresenhamLine(startpoint,endpoint);
		break;
		case 2:
			BresenhamCircle(startpoint,endpoint);
		break;
		case 3:
			BresenhamOval(startpoint,endpoint);
		break;
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////实现部分

void CMy1401150312View::BresenhamLine(CPoint sp,CPoint ep){
//	CClientDC dc(this);
	CDC* pDC=GetDC();
	CPoint np, temp;
	COLORREF clr = RGB(0, 0, 0);
	//交换顶点起点低
	if(sp.y>ep.y){
		temp=sp;
		sp=ep;
		ep=temp;
	}
	//k=斜率，d=中点误差项
	double k,d;
	k=static_cast<double>(ep.y-sp.y)/(ep.x-sp.x);
	if(fabs(sp.x-ep.x)<1e-6)//画垂直直线
		for(int i=sp.y;i<ep.y;i++)
			pDC->SetPixelV(sp.x,i,clr);
	else{
		//四种斜率分别
		if(k>1){
			if (sp.y > ep.y){
				temp = sp; 
				sp = ep; 
				ep = temp;
			}
			d = 1 - 0.5*k;
			
			for (np = sp; np.y < ep.y; np.y++){
				pDC->SetPixelV(np.x, np.y, clr);
				if (d >= 0){
					np.x++; 
					d += 1 - k;
				}
				else
					d += 1;
			}//end for

		}//end if
		if(k >= 0 && k <= 1){
			if(sp.x > ep.x){
				temp = sp;
				sp = ep;
				ep = temp;
			}
			d = 0.5 - k;
			for(np = sp ; np.x < ep.x ; np.x++){
			pDC->SetPixelV(np.x , np.y,clr);
				if(d < 0){
					np.y++;
					d+=1-k;
				}
				else
					d-=k;
			}//end for
		}//end if
		if(k>=-1 && k<0){
			if (sp.x > ep.x){
				temp = sp; 
				sp = ep; 
				ep = temp;
			}
			d = - 0.5 - k;
			
			for (np = sp; np.x < ep.x; np.x++){
				pDC->SetPixelV(np.x, np.y, clr);
				if (d > 0){
					np.y--; 
					d -= 1 + k;
				}
				else
					d -= k;
			}//end for

		}//end if
		if(k<-1){
			if (sp.y < ep.y){
				temp = sp; 
				sp = ep; 
				ep = temp;
			}
			d = -1 - 0.5*k;
			
			for (np = sp; np.y > ep.y; np.y--){
				pDC->SetPixelV(np.x, np.y, clr);
				if (d < 0){
					np.x++; 
					d -= 1 + k;
				}
				else
					d -= 1;
			}//end if
		}//end if
	}//end else
}

void CMy1401150312View::BresenhamCircle(CPoint sp,CPoint ep){
	CDC* pDC=GetDC();
	CPoint np;
	COLORREF clr = RGB(0, 0, 0);
	double r=sqrt(pow(ep.x-sp.x,2) + pow(ep.y-sp.y,2));
	CPoint tp(0,static_cast<int>(r));
	double d;
	d=1.25+r;
	for(np=tp;np.x<=r/sqrt(2);np.x++){
		pDC->SetPixelV(sp.x+np.x,sp.y+np.y, clr);
		pDC->SetPixelV(sp.x+np.y,sp.y+np.x, clr);
		pDC->SetPixelV(sp.x-np.y,sp.y+np.x, clr);
		pDC->SetPixelV(sp.x+np.x,sp.y-np.y, clr);
		pDC->SetPixelV(sp.x-np.x,sp.y-np.y, clr);
		pDC->SetPixelV(sp.x-np.y,sp.y-np.x, clr);
		pDC->SetPixelV(sp.x+np.y,sp.y-np.x, clr);
		pDC->SetPixelV(sp.x-np.x,sp.y+np.y, clr);

		if(d>=0){
			d+=2*(np.x-np.y)+5;
			np.y--;
		}//end if
		else{
			d+=2*np.x+3;
		}//end if
	}//end for
}

void CMy1401150312View::BresenhamOval(CPoint sp,CPoint ep){
	CDC* pDC=GetDC();
	CPoint np, temp;
	COLORREF clr = RGB(0, 0, 0);

	double a=abs(static_cast<double>(ep.x-sp.x))/2,
		   b=abs(static_cast<double>(ep.y-ep.x))/2;
	double ab=sqrt(a*a+b*b);
	CPoint pa(0,b),
		   pb(a,0),
		   pc(static_cast<int>(a*a/ab),static_cast<int>(b*b/ab));
//	double d1=pow(b*(pa.x+1),2)+pow(a*(pa.y-0.5),2)-pow(a*b,2);
//	double d2=pow(b*(pa.x+0.5),2)+pow(a*(pa.y-1),2)-pow(a*b,2);
	double d1=b*b+a*a*(-b+0.25);
	double d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;


/*
	for(np=pa;pa.x<pc.x;no.x++)//椭圆AC弧段{
		if (d1<0)
			d1+=b*b*(2*x+3);
		else{
			d1+=b*b*(2*x+3)+a*a*(-2*y+2);
			np.y--;
		}
		pDC->SetPixelV();
	}
	d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;//椭圆CB弧段
	for(np=pc;np.y>=o,np.y--){
		if (d2<0){
			d2+=b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
		}
		else
			d2+=a*a*(-2*y+3);

		pDC->SetPixelV();
	}	
*/
}


/////////////////////////////////////////////end////////////////////////////////////////////