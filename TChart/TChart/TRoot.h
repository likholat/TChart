#pragma once

#include <stdlib.h>

using namespace System;
using namespace System::Drawing;

class TRoot{

//protected:
public:
	bool visible;
	bool active;

public:
	TRoot(){
		visible = false;
		active = false;
	}

	bool IsVisible(){
		return visible;
	}

	bool IsActive(){
		return active;
	}

	virtual void Show(Graphics^ gr) = 0;
	virtual void Hide(Graphics^ gr) = 0;
	virtual void Move(Graphics^ gr, int dx, int dy) = 0;

};