#include <iostream>
#include "graphics.h"

using namespace std;

class Figure {
		bool visible;
	protected:
		int x, y, c;

		virtual void draw() = 0;
	public:
		Figure(int c, int x, int y):c(c), visible(0), x(x), y(y) {}
		virtual ~Figure() {}

		void move(int x, int y);
		void setcolor(int c);

		int getcolor() const {
			return c;
		}

		void hide();
		void show();

		bool isvisible() const {
			return visible;
		}

		virtual void area(int &x1, int &y1, int &x2, int &y2) const = 0;
};

void Figure::setcolor(int c) {
	this -> c = c;

	if (visible) draw();
}

void Figure::move(int x, int y) {
	bool f = visible;
	if (f) hide();

	this -> x = x;
	this -> y = y;

	if (f) show();
}

void Figure::hide() {
	if (!visible) return;

	int x1, y1, x2, y2;
	area(x1, y1, x2, y2);

	setfillstyle(SOLID_FILL, BLACK);
	bar(x1, y1, x2, y2);

	visible = 0;
}

void Figure::show() {
	if (visible) return;
	visible = 1;

	draw();
}

class Cylinder: public Figure {
	protected:
		int h, r1, r2;
		void draw();
	public:
		Cylinder(int c, int x, int y, int h, int r1, int r2): Figure(c, x, y), h(h), r1(r1), r2(r2) {}
		~Cylinder() {
			hide();
		}

		void setsizes(int h, int r1, int r2);
		void area(int &x1, int &y1, int &x2, int &y2) const;
};

void Cylinder::setsizes(int h, int r1, int r2) {
	bool f = isvisible();
	if (f) hide();

	this -> h = h;
	this-> r1 = r1;
	this -> r2 = r2;

	if (f) show();
}

void Cylinder::area(int &x1, int &y1, int &x2, int &y2)const {
	x1 = x - r1;
	y1 = y + r2;
	x2 = x + 2 * r1;
	y2 = y - h - r2;
}

void Cylinder::draw() {
	::setcolor(getcolor());

	ellipse(x, y, 180, 360, r1, r2);
	ellipse(x, y - h, 0, 360, r1, r2);

	moveto(x - r1, y - h);
	lineto(x - r1, y);

	moveto(x + r1, y - h);
	lineto(x + r1, y);
}

class FillCylinder: public Cylinder {
	protected:
		int fc;

		void draw();
	public:
		FillCylinder(int c, int x, int y, int h, int r1, int r2, int fc):Cylinder(c, x, y, h, r1, r2), fc(fc) {}

		void setfillcolor(int);
};

void FillCylinder::draw() {
	setfillstyle(SOLID_FILL, fc);

	fillellipse(x, y - h, r1, r2);

	Cylinder::draw();

	floodfill(x, y - h / 2, c);
}

void FillCylinder::setfillcolor(int c) {
	fc = c;
	if (isvisible()) draw();
}

int main() {
	initwindow(640, 480);

	int testX = 200, testY = 300, testH = 50, testR1 = 30, testR2 = 15;

	Figure *a=new Cylinder(GREEN, testX, testY, testH, testR1,testR2);
	Figure *b=new FillCylinder(YELLOW, testX + 100, testY, testH, testR1, testR2, BROWN);
	
	a -> show();
	b -> show();
	getch();

	a -> move(testX - 90, testY - 90);
	getch();
	
	b -> move(testX + 90, testY + 90);
	getch();
	
	a -> setcolor(WHITE);
	getch();
	
	b -> setcolor(CYAN);
	getch();
	
	if(Cylinder *r=dynamic_cast<Cylinder*>(a)) r -> setsizes(testH + 50, testR1 * 3, testR2 * 2);
	getch();
	
	if(Cylinder *r=dynamic_cast<Cylinder*>(b)) r -> setsizes(testH + 50, testR1 * 2, testR2 * 2);
	getch();
	
	if(FillCylinder *r=dynamic_cast<FillCylinder*>(a)) r -> setfillcolor(GREEN);
	getch();
	
	if(FillCylinder *r=dynamic_cast<FillCylinder*>(b)) r -> setfillcolor(BLUE);
	getch();
	
	delete a;
	delete b;
	
	
	return 0;
}