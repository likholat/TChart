#include "TRoot.h"
#include "TPoint.h"
#include <stack>
#include <Math.h>

using namespace std;
using namespace System;
using namespace System::Drawing;

class TRoot;
class TPoint;
class TChart;

struct TChartLine {
	TChart *tC;
	TPoint *tS;
	TPoint *tE;
};

class TChart: public TRoot{
protected:
	TRoot *pStart, *pEnd;

public:
	
	int findStart;
	stack<TChartLine> st;

	TChart(){
		pStart = nullptr;
		pEnd = nullptr;
		visible = true;
	}

	void SetStart(TRoot *p){
		TPoint *tp = dynamic_cast<TPoint*>(p);
		TChart *tc = dynamic_cast<TChart*>(p);
		if(tp || tc)
			pStart = p;
	}

	void SetEnd(TRoot *p){
		TPoint *tp = dynamic_cast<TPoint*>(p);
		TChart *tc = dynamic_cast<TChart*>(p);
		if(tp || tc )
			pEnd = p;
	}

	TRoot* GetStart() { return pStart; }
	TRoot* GetEnd() { return pEnd; }

	TRoot* Show (Graphics^ gr, TRoot* p){
		TPoint *tB, *tE;
		TChart *tC;
		tB = dynamic_cast<TPoint*>(p);
		if(tB != nullptr){
			tB->Show(gr);
			return  p;
		}
		else{
			tC = dynamic_cast<TChart *>(p);
			tB = dynamic_cast<TPoint*>(Show(gr, tC->pStart));
			tE = dynamic_cast<TPoint*>(Show(gr, tC->pEnd));
			Pen^ newPen = gcnew Pen(Color::Black);
			gr->DrawLine(newPen, tB->GetX(), tB->GetY(), tE->GetX(), tE->GetY());
			return (TRoot*)tC;
		}
	}

	void Show(Graphics^ gr){

		TChartLine Curr;
		TRoot *tmp;
		TPoint *tp;

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while(!st.empty())
				st.pop();

		st.push(Curr);

		while(!st.empty()){

			Curr = st.top();
			st.pop();

			while(Curr.tS == nullptr){

				tmp = Curr.tC->pStart;
				tp = dynamic_cast<TPoint*>(tmp);

				if(tp!=nullptr)
					Curr.tS = tp;

				else{
					st.push(Curr);
				//		tp->Show(gr);								
					Curr.tC = dynamic_cast<TChart*>(tmp);
				}

			}

			if(Curr.tE == nullptr){

				tmp = Curr.tC->pEnd;
				tp = dynamic_cast<TPoint*>(tmp);

				if(tp!=nullptr)
					Curr.tE = tp;

				else{
					st.push(Curr);
					Curr.tC = dynamic_cast<TChart*>(tmp);
					Curr.tS = nullptr;
					st.push(Curr);
				}
			}
			if(Curr.tS && Curr.tE){
			if(Curr.tC->visible){
					if(Curr.tC->active)
						gr->DrawLine(Pens::Blue, Curr.tS->GetX(), Curr.tS->GetY(), Curr.tE->GetX(), Curr.tE->GetY());
					else
						gr->DrawLine(Pens::Black, Curr.tS->GetX(), Curr.tS->GetY(), Curr.tE->GetX(), Curr.tE->GetY());
			}
				tp = Curr.tE;

				if(!st.empty()){
					Curr = st.top();
					st.pop();

					if(Curr.tS == nullptr)
						Curr.tS = tp;

					else
						Curr.tE = tp;

					st.push(Curr);
				}
			}
		}
	}

	void Hide(Graphics^ gr){

		TChartLine Curr;
		TRoot *tmp;
		TPoint *tp;

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while(!st.empty())
				st.pop();

		st.push(Curr);

		while(!st.empty()){

			Curr = st.top();
			st.pop();

			while(!Curr.tS){

				tmp = Curr.tC->pStart;
				tp = dynamic_cast<TPoint*>(tmp);

				if(tp!=nullptr)
					Curr.tS = tp;

				else{
					st.push(Curr);
					//tp->Hide(gr);								
					Curr.tC = dynamic_cast<TChart*>(tmp);
				}

			}

			if(Curr.tE == nullptr){

				tmp = Curr.tC->pEnd;
				tp = dynamic_cast<TPoint*>(tmp);

				if(tp!=nullptr)
					Curr.tE = tp;

				else{
					st.push(Curr);
					Curr.tC = dynamic_cast<TChart*>(tmp);
					Curr.tS = nullptr;
					st.push(Curr);
				}
			}
			if(Curr.tS && Curr.tE){

				gr->DrawLine(Pens::White, Curr.tS->GetX(), Curr.tS->GetY(), Curr.tE->GetX(), Curr.tE->GetY());
				tp = Curr.tE;

				if(!st.empty()){
					Curr = st.top();
					st.pop();

					if(Curr.tS == nullptr)
						Curr.tS = tp;

					else
						Curr.tE = tp;

					st.push(Curr);
				}
			}
		}
	} 

	/*	void Show(Graphics^ gr){

		TChartLine Curr;
		TPoint *tmp;
		

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while(!st.empty())
				st.pop();

		st.push(Curr);

		while(!st.empty()){

			Curr = st.top();
			st.pop();

			while(!Curr.tS){

				tmp = dynamic_cast<TPoint*>(Curr.tC->pStart);

				if(tmp)
					Curr.tS = tmp;

				else{
					st.push(Curr);							
					Curr.tC = (TChart*)Curr.tC->pStart;
				}

			}

			if(!Curr.tE){

				tmp = dynamic_cast<TPoint*>(Curr.tC->pEnd);

				if(tmp)
					Curr.tE = tmp;

				else{
					st.push(Curr);
					Curr.tC = (TChart*)Curr.tC->pEnd;
					Curr.tS = nullptr;
					st.push(Curr);
				}
			}
			if(Curr.tS && Curr.tE){

				gr->DrawLine(Pens::Black, Curr.tS->GetX(), Curr.tS->GetY(), Curr.tE->GetX(), Curr.tE->GetY());
				Curr.tS->Show(gr);
				Curr.tE->Show(gr);
				tmp = Curr.tE;
				if(!st.empty()){
					Curr = st.top();
					st.pop();

					if(!Curr.tS)
						Curr.tS = tmp;

					else
						Curr.tE = tmp;

					st.push(Curr);
				}
			}
		}
	}

	void Hide(Graphics^ gr){

		TChartLine Curr;
		TPoint *tmp;
		

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while(!st.empty())
				st.pop();

		st.push(Curr);

		while(!st.empty()){

			Curr = st.top();
			st.pop();

			while(!Curr.tS){

				tmp = dynamic_cast<TPoint*>(Curr.tC->pStart);

				if(tmp)
					Curr.tS = tmp;

				else{
					st.push(Curr);							
					Curr.tC = (TChart*)Curr.tC->pStart;
				}

			}

			if(!Curr.tE){

				tmp = dynamic_cast<TPoint*>(Curr.tC->pEnd);

				if(tmp)
					Curr.tE = tmp;

				else{
					st.push(Curr);
					Curr.tC = (TChart*)Curr.tC->pEnd;
					Curr.tS = nullptr;
					st.push(Curr);
				}
			}
			if(Curr.tS && Curr.tE){

				gr->DrawLine(Pens::White, Curr.tS->GetX(), Curr.tS->GetY(), Curr.tE->GetX(), Curr.tE->GetY());
				
				tmp = Curr.tE;
				if(!st.empty()){
					Curr = st.top();
					st.pop();

					if(!Curr.tS)
						Curr.tS = tmp;

					else
						Curr.tE = tmp;

					st.push(Curr);
				}
			}
		}
	} */

	TPoint* Find (int X, int Y){

		TChartLine Curr;
		TPoint *tmp;

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while (!st.empty()) 
			st.pop();

		st.push(Curr);

		while (!st.empty()) {

			Curr = st.top();
			st.pop();

			while (Curr.tS == nullptr) {

				tmp = dynamic_cast<TPoint *>(Curr.tC->pStart);

				if (tmp!=nullptr)
					Curr.tS = tmp;

				else {
					st.push(Curr);
					Curr.tC = (TChart *)Curr.tC->pStart;
				}
			}

			if (Curr.tE == nullptr) {

				tmp = dynamic_cast<TPoint *>(Curr.tC->pEnd);

				if (tmp!=nullptr) 
					Curr.tE = tmp;

			else {

				st.push(Curr);

				Curr.tC = (TChart*)Curr.tC->pEnd;

				Curr.tS = nullptr;
				st.push(Curr);
			}
		}

		if (Curr.tS && Curr.tE) {

			if (abs(Curr.tS->GetX() - X) <  30 && abs(Curr.tS->GetY() - Y) < 30) {

				findStart = 1;
				return Curr.tS;
			}

			if (abs(Curr.tE->GetX() - X) <  30 && abs(Curr.tE->GetY() - Y) < 30) {
				findStart = 0;

				return Curr.tE;
			}

			tmp = Curr.tE;

			if (!st.empty()) {
				Curr = st.top();
				st.pop();

				if (Curr.tS == nullptr)
					Curr.tS = tmp;

				else 
					Curr.tE = tmp;

				st.push(Curr);
			}
		}
	}
	}

	TChartLine Find_2(int X, int Y){

		TChartLine Curr;
		TPoint *tmp;
		findStart = -1;

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while (!st.empty()) 
			st.pop();

		st.push(Curr);

		while (!st.empty()) {

			Curr = st.top();
			st.pop();

			while (Curr.tS == nullptr) {

				tmp = dynamic_cast<TPoint *>(Curr.tC->pStart);

				if (tmp!=nullptr)
					Curr.tS = tmp;

				else {
					st.push(Curr);
					Curr.tC = (TChart *)Curr.tC->pStart;
				}
			}

			if (Curr.tE == nullptr) {

				tmp = dynamic_cast<TPoint *>(Curr.tC->pEnd);

				if (tmp!=nullptr) 
					Curr.tE = tmp;

			else {

				st.push(Curr);

				Curr.tC = (TChart*)Curr.tC->pEnd;

				Curr.tS = nullptr;
				st.push(Curr);
			}
		}

		if (Curr.tS && Curr.tE) {

			if (abs(Curr.tS->GetX() - X) <  5 && abs(Curr.tS->GetY() - Y) < 5) {

				findStart = 1;
				Curr.tE = NULL;
				return Curr;
			}

			if (abs(Curr.tE->GetX() - X) <  5 && abs(Curr.tE->GetY() - Y) < 5) {
				findStart = 0;
				Curr.tS = NULL;
				return Curr;
			}

			tmp = Curr.tE;

			if (!st.empty()) {
				Curr = st.top();
				st.pop();

				if (Curr.tS == nullptr)
					Curr.tS = tmp;

				else 
					Curr.tE = tmp;

				st.push(Curr);
			}
		}
	}

		return Curr;
	}

	TChart* Click(int X, int Y){
		TChartLine Curr;
		TPoint *tmp;

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while (!st.empty()) 
			st.pop();

		st.push(Curr);

		while (!st.empty()) {

			Curr = st.top();
			st.pop();

			while (Curr.tS == nullptr) {

				tmp = dynamic_cast<TPoint *>(Curr.tC->pStart);

				if (tmp!=nullptr)
					Curr.tS = tmp;

				else {
					st.push(Curr);
					Curr.tC = (TChart *)Curr.tC->pStart;
				}
			}

			if (Curr.tE == nullptr) {

				tmp = dynamic_cast<TPoint *>(Curr.tC->pEnd);

				if (tmp!=nullptr) 
					Curr.tE = tmp;

			else {

				st.push(Curr);

				Curr.tC = (TChart*)Curr.tC->pEnd;

				Curr.tS = nullptr;
				st.push(Curr);
			}
		}

		if (Curr.tS && Curr.tE) {

			int dx1 = Curr.tE->GetX() - Curr.tS->GetX(); 
			int dy1 = Curr.tE->GetY() - Curr.tS->GetY();

			int dx = X -  Curr.tS->GetX();
			int dy = Y -  Curr.tS->GetY();

			double lenght = sqrt(dx1*dx1 + dy1*dy1); // длина прямой

			double S = abs(dx1*dy - dx*dy1);

			double distance = S/lenght;

			if (distance < 10) {
				return Curr.tC;
			}

			tmp = Curr.tE;

			if (!st.empty()) {
				Curr = st.top();
				st.pop();

				if (Curr.tS == nullptr)
					Curr.tS = tmp;

				else 
					Curr.tE = tmp;

				st.push(Curr);
			}
		}
	}
		return nullptr;
	}

	void Move (Graphics ^gr, int dx, int dy){
		
		Hide(gr);

		pStart->Move(gr, dx, dy);
		pEnd->Move(gr, dx, dy);

		Show(gr);

	}



	};

/*		void Show(Graphics^ gr){

		TChartLine Curr;
		TRoot *tmp;
		TPoint *tp;

		Curr.tC = this;
		Curr.tS = Curr.tE = nullptr;

		while(!st.empty())
				st.pop();

		st.push(Curr);

		while(!st.empty()){

			Curr = st.top();
			st.pop();

			while(Curr.tS == nullptr){

				tmp = Curr.tC->pStart;
				tp = dynamic_cast<TPoint*>(tmp);

				if(tp!=nullptr)
					Curr.tS = tp;

				else{
					st.push(Curr);
				//		tp->Show(gr);								
					Curr.tC = dynamic_cast<TChart*>(tmp);
				}

			}

			if(Curr.tE == nullptr){

				tmp = Curr.tC->pEnd;
				tp = dynamic_cast<TPoint*>(tmp);

				if(tp!=nullptr)
					Curr.tE = tp;

				else{
					st.push(Curr);
					Curr.tC = dynamic_cast<TChart*>(tmp);
					Curr.tS = nullptr;
					st.push(Curr);
				}
			}
			if(Curr.tS && Curr.tE){
			//	if(Curr.tC->visible){
				//	if(Curr.tC->active)
				gr->DrawLine(Pens::Black, Curr.tS->GetX(), Curr.tS->GetY(), Curr.tE->GetX(), Curr.tE->GetY());
				tp = Curr.tE;

				if(!st.empty()){
					Curr = st.top();
					st.pop();

					if(Curr.tS == nullptr)
						Curr.tS = tp;

					else
						Curr.tE = tp;

					st.push(Curr);
				}
			}
		}
	} */