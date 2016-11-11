
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "nbodyTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(10), NULL);
//3:reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1)
	
	srand((unsigned)time(NULL));//根据系统时间生成随机数种子，实现伪随机数的生成

	Initial();//调用初始化函数
	
	
	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//	SetTimer(Timer1, Hz, NULL);
	//定义定时器，其中Hz为自定义的宏，表示定时器触发事件周期的毫秒数
	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	for (p3 = bhead; p3 != NULL; p3 = p3->bnext)
	{
		mDrawE(p3);//画图函数的实现
//		TRACE("p->num %d ,p->vy %f\n", p3->num, p3->vy);
		
	}
	NS_RK4_nX();//调用并实现RK4方法
	NS_RK4_nY();//
	//
	//mCombine();
	

	//for (p3 = bhead; p3 != NULL; p3 = p3->bnext)
	//{
	//	mDrawE(p3);
	//	TRACE("p->num %d \n", p3->num);/////////////////
	//	TRACE("p->x %f \n", p3->vx);
	//}
	//for (p3 = bhead; p3->bnext != NULL; p3 = p3->bnext);
	//bend = p3;
	//for (p3 = bend; p3 != NULL; p3 = p3->bprev)
	//{
	//	TRACE("111p->num %d \n", p3->num);/////////////////
	//	TRACE("111p->x %f \n", p3->vx);
	//}
	

	CWnd::OnTimer(nIDEvent);
}

void CChildView::mDrawE(struct mbody *a)
{//画图函数的定义
	CClientDC dc(this);
	CBrush bgBrush(RGB(0,0,0));
	//CBrush bgBrush(RGB(0, 0, 0));
	CBrush colorBrush(RGB(a->Rgb, a->rGb, a->rgB));
	CPen bgPen(PS_SOLID, 1, RGB(0,0, 0));

	CPen obPen(PS_SOLID, 1, RGB(a->Rgb, a->rGb, a->rgB));
//	CPen obPen(PS_SOLID, 1, RGB(255, 0, 0));
//	CDC *tdc = this->GetDC();
	CString str;

	int x1 = a->x - a->r ;
	int y1 = a->y - a->r ;
	int x2 = a->x + a->r ;
	int y2 = a->y + a->r ;

	int tx1 = a->tx - a->r ;
	int ty1 = a->ty - a->r ;
	int tx2 = a->tx + a->r ;	
	int ty2 = a->ty + a->r ;

	CBrush *pOldBrush2 = dc.SelectObject(&bgBrush);
	//	dc.FillRect(CRect(0, 0, 800, 600), &bgBrush);
		dc.Ellipse(tx1, ty1, tx2, ty2);
	dc.SelectObject(pOldBrush2);

	CBrush *pOldBrush = dc.SelectObject(&colorBrush);
	dc.Ellipse(x1, y1, x2, y2);
//		dc.Ellipse(100, 100, 200, 200);
	dc.SelectObject(pOldBrush);

	CPen *pOldPen = dc.SelectObject(&bgPen);
	dc.SelectStockObject(NULL_BRUSH);
	dc.Ellipse(tx1, ty1, tx2, ty2);
	dc.SelectObject(pOldPen);

	CPen *pOldPen2 = dc.SelectObject(&bgPen);
		dc.Ellipse(x1, y1, x2, y2);
	dc.SelectObject(pOldPen2);
	
	/*CPen *pOldPen3 = dc.SelectObject(&obPen);
	if (a->x != 0 && a->y != 0 && a->tx != 0 && a->tx != 0)
	{
		
		dc.MoveTo(a->tx, a->ty);
		dc.LineTo(a->x, a->y);
	}
	dc.SelectObject(pOldPen3);*/

	//str.Format(_T("%d"), a->num);
	////	tdc->TextOut(a->x, a->y, str);
	//tdc->DrawText(str, CRect(x1, y1, x2, y2), DT_VCENTER | DT_CENTER | DT_SINGLELINE);

//	return(1);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	
	case ' '://暂停/开始
		if (timer_exist == FALSE)
		{
			SetTimer(Timer1, Hz, NULL);
			timer_exist = TRUE;
		}
		else
		{
			KillTimer(Timer1);
			timer_exist = FALSE;
		}
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
