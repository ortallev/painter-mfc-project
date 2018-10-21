#include "stdafx.h"
#include "Figure.h"
#include "MyPainter.h"
#include "MyPainterDlg.h"
#include "afxdialogex.h"
IMPLEMENT_SERIAL(Figure, CObject, 1)
Figure::Figure(void){ bgColor = RGB(255, 0, 0); FbgColor = RGB(0, 255, 0); dirx=diry=1;}
Figure::Figure(BOOL isThin):isThin(isThin){dirx=diry=1;}
Figure::~Figure(void){}
void Figure::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

    // now do the stuff for our specific class
    if(archive.IsStoring())
		archive << startP.x << startP.y << endP.x << endP.y << bgColor;
    else
        archive >> startP.x >> startP.y >> endP.x >> endP.y >> bgColor;
}
void Figure::draw(CDC *dc) {
	CPen pen(PS_SOLID, isThin?1:3, FbgColor);
	CBrush brush(bgColor);
	CBrush *old = dc->SelectObject(&brush);
	CPen *oldPen = dc->SelectObject(&pen);
	innerDraw(dc);
	dc->SelectObject(oldPen);
	dc->SelectObject(old);
}
void Figure::Move(int d,int dir,const CRect& r) // function for move shape in dircation 
{
	if(dir == 0)
		{
			if(this->endP.x>=  r.BottomRight().x || this->startP.x<=0)
			
				dirx*=-1;
			
		        this->startP.x=this->startP.x+d*dirx;
			    this->endP.x=this->endP.x+d*dirx;
			
		}
	else
		{
			if(this->endP.y>= r.BottomRight().y || this->startP.y<=0)
			
				diry*= -1;
			this->startP.y=this->startP.y+d*diry;
			this->endP.y=this->endP.y+d*diry;
			
	
		}
} 