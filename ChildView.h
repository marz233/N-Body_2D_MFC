
// ChildView.h : CChildView 类的接口
//


#pragma once
#include<cmath>
#define h 0.005
#define Timer1 1
#define Hz 60
#define mpowfer 0.5
#define epis 10

// CChildView 窗口

class CChildView : public CWnd
{
public:
	CChildView();
public:
	int n = 100;
	struct mbody
	{
		double x, y, vx, vy, m, tx, ty,r;
		int num, Rgb, rGb, rgB;
		struct mbody * bprev, *bnext, *dprev, *dnext;//bodyprevious/next,dataprevious/next
	
	}mhead,mMelt;

	struct mbody *bhead = &mhead, *pMelt = &mMelt, *p3, *bend, *pt, *ptt;
	BOOL timer_exist = FALSE;
	
	double fastPow(double a, double b) {
		union {
			double d;
			int x[2];
		} u = { a };
		u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
		u.x[0] = 0;
		return u.d;
	}

	BOOL Initial()//初始化函数
	{
		struct mbody *p1, *p2;
		for (p1 = bhead, p1->num = 1, p1->bprev = NULL;
			 p1->num <= n-1 ; 
			 p1 = p1->bnext)
		{//建立长度为n的结构体链表
			p2 = (struct mbody *)malloc(sizeof(struct mbody));
			p2->bnext = NULL;
			p1->bnext = p2;
			p2->bprev = p1;
			p2->num = p1->num + 1;
		}
		for (p1 = bhead; p1 != NULL; p1 = p1->bnext)
		{//遍历链表，给每一个结构体对象赋初值，分别对成员变量赋在给定范围内生成的随机数
			p1->x = RangeRand(1500,100);
			p1->y = RangeRand(800,100);
			p1->vx = RangeRand(0, 0);
			p1->vy = RangeRand(0, 0);
			p1->m = RangeRand(1000,0);
			p1->r = powf(p1->m/9,0.4);

			p1->Rgb = RangeRand(255, 0);
			p1->rGb = RangeRand(255, 0);
			p1->rgB = RangeRand(255, 0);
		}
		return(1);
	}

	double K11, K21, K12, K22, K13, K23, K14, K24;//定义RK4方法的参数为全局变量
	double powfer=mpowfer,ePis=epis;

	double RangeRand(int max, int min)
	{//在一个范围内生成随机数
		return (max - min)*rand() / (RAND_MAX + 0.1) + min;
	}

	double g_X(double x, struct mbody * a, struct mbody * b)
	{//X分量的万有引力公式的单个项
		return
			(
			b->m*(b->x - x) / powf(powf(b->x - x, 2) + powf(b->y - a->y, 2) + ePis, powfer)
			);
	}

	double g_Y(double y, struct mbody * a, struct mbody * b)
	{//Y分量的万有引力公式的单个项
		return
			(
			b->m*(b->y - y) / powf(powf(b->y - y, 2) + powf(b->x - a->x, 2) + ePis, powfer)
			);
	}

	double gxSum(double x)
	{//对X分量的n项万有引力公式求和
		double gxSum = 0;
		struct mbody *p2;
		for (p2 = bhead->bnext; p2 != NULL; p2 = p2->bnext)gxSum = gxSum + g_X(x, bhead, p2);
		return(gxSum);
	}

	double gySum(double y)
	{//对Y分量的n项万有引力公式求和
		double gySum = 0;
		struct mbody *p2;
		for (p2 = bhead->bnext; p2 != NULL; p2 = p2->bnext)gySum = gySum + g_Y(y, bhead, p2);
		return(gySum);
	}

	BOOL NS_RK4_nX()
	{//X分量的RK4方法，遍历链表计算n个体的状态并赋值
//		struct mbody *pt, *ptt;
		BOOL cycleEnd = FALSE;
//		int mark2 = 0;
		for (pt = bhead->bnext, ptt = pt->bnext; !cycleEnd; pt = ptt)
		{
	//		TRACE("bhead->num %d \n", bhead->num);
			

			K11 = bhead->vx;
			K21 = gxSum(bhead->x);
			K12 = bhead->vx + h / 2 * K21;
			K22 = gxSum(bhead->x + h / 2 * K11);
			K13 = bhead->vx + h / 2 * K22;
			K23 = gxSum(bhead->x + h / 2 * K12);
			K14 = bhead->vx + h * K23;
			K24 = gxSum(bhead->x + h * K13);
			bhead->tx = bhead->x;
			bhead->x = bhead->x + h / 6 * (K11 + 2 * K12 + 2 * K13 + K14);
			bhead->vx = bhead->vx + h / 6 * (K21 + 2 * K22 + 2 * K23 + K24);
			
			if (ptt != NULL)
			{
				pt->bprev->bnext = pt->bnext;
				if (pt->bnext != NULL)pt->bnext->bprev = pt->bprev;///////
				ptt = pt->bnext;
				pt->bnext = bhead;
				bhead->bprev = pt;
				bhead = pt;

				bhead->bprev = NULL;
			}
			
		//	if (ptt == NULL/*&&n != 2*/)cycleEnd = TRUE;
			else cycleEnd = TRUE;//else not equal to ptt==NULL
			/*if (n == 2)
			{
				mark2++;
				if (mark2 == 2)cycleEnd = TRUE;
			}*/
		}

//		CClientDC dc(this);//////////////////
//		dc.TextOut(0, 0, _T("x"));///////////

		return(1);
	}

	BOOL NS_RK4_nY()
	{//Y分量的RK4方法，遍历链表计算n个体的状态并赋值
//		struct mbody *pt, *ptt;
		BOOL cycleEnd = FALSE;
//		int mark2 = 0;
		for (pt = bhead->bnext, ptt = pt->bnext; !cycleEnd; pt = ptt)
		{
			K11 = bhead->vy;
			K21 = gySum(bhead->y);
			K12 = bhead->vy + h / 2 * K21;
			K22 = gySum(bhead->y + h / 2 * K11);
			K13 = bhead->vy + h / 2 * K22;
			K23 = gySum(bhead->y + h / 2 * K12);
			K14 = bhead->vy + h * K23;
			K24 = gySum(bhead->y + h * K13);
			bhead->ty = bhead->y;
			bhead->y = bhead->y + h / 6 * (K11 + 2 * K12 + 2 * K13 + K14);
			bhead->vy = bhead->vy + h / 6 * (K21 + 2 * K22 + 2 * K23 + K24);

			if (ptt != NULL)
			{
				pt->bprev->bnext = pt->bnext;
				if (pt->bnext != NULL)pt->bnext->bprev = pt->bprev;///////
				ptt = pt->bnext;
				pt->bnext = bhead;
				bhead->bprev = pt;
				bhead = pt;

				bhead->bprev = NULL;
			}
		//	if (ptt == NULL/*&&n != 2*/)cycleEnd = TRUE;
			else cycleEnd = TRUE;
			/*if (n == 2)
			{
				mark2++;
				if (mark2 == 2)cycleEnd = TRUE;
			}*/
		}
		return(1);
	}

	BOOL mbodyCollision(struct mbody *a, struct mbody *b)
	{//检测碰撞函数，认定当两圆内切时为碰撞
		double temp = sqrt(powf(a->x - b->x, 2) + powf(a->y - b->y, 2));
		return((temp <= a->r) | (temp <= b->r));
			
//		return(sqrt(powf(a->x - b->x, 2) + powf(a->y - b->y, 2)) <= abs(a->r - b->r));
	}

	BOOL mbodyCombine(struct mbody *a, struct mbody *b)
	{//定义体间融合的函数，满足动量守恒和质量守恒
		struct mbody *c=pMelt;
		//struct mbody *c = NULL;
		c->x = (a->x*a->m + b->x*b->m) / (a->m + b->m);
		c->y = (a->y*a->m + b->y*b->m) / (a->m + b->m);
		c->vx = (a->vx*a->m + b->vx*b->m) / (a->m + b->m);
		c->vy = (a->vy*a->m + b->vy*b->m) / (a->m + b->m);
		c->m = a->m + b->m;

		c->r = powf(c->m, 0.33);

		a->x = c->x;
		a->vx = c->vx;
		a->m = c->m;
		a->r = c->r;

		b->bprev->bnext = b->bnext;//
		if(b->bnext!=NULL)b->bnext->bprev = b->bprev;
		b->bprev = NULL;
		b->bnext = NULL;

		return(1);
	}

	BOOL mCombine()
	{//实现体间融合的函数
		struct mbody *tbhead,*p2;
		for (tbhead = bhead; tbhead->bnext != NULL; tbhead = tbhead->bnext)/////
		{
			for (p2 = tbhead->bnext; p2 != NULL; p2 = p2->bnext)
			{
				if (mbodyCollision(tbhead, p2))mbodyCombine(tbhead, p2);
			}
		}
		return(1);
	}
public:
	void mDrawE(struct mbody* a);//画图函数的声明
	// 重写
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
