#include "TRoot.h"

using namespace System;
using namespace System::Drawing;


class TPoint : public TRoot
{
protected:
	int x, y;
public:
	TPoint(int _x = 0, int _y = 0){
	x = _x;
	y = _y;
	}

	int GetX() { 
		return x;
	}
	int GetY() { 
		return y;
	}

	void SetX(int _x) { 
		x = _x;
	}
	void SetY(int _y) { 
		y = _y;
	}

	virtual void Show(Graphics^ gr){
		gr->DrawEllipse(Pens::Black, x-2, y-2, x+2, y+2);
		visible = true;
	}

	virtual void Hide(Graphics^ gr){
		gr->DrawEllipse(Pens::White, x-2, y-2, x+2, y+2);
		visible = true;
	}

	virtual void Move(Graphics^ gr, int dx, int dy){
		Hide(gr);
		x += dx;
		y += dy;
		//gr->DrawEllipse(Pens::Black, x-2, y-2, x+2, y+2);
		visible = true;
	}

};