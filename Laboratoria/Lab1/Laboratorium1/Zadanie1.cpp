#include <iostream>

class Punkt
{
	float x;
	float y;
public:
	Punkt(Punkt& p);
	Punkt(float x_ = 0, float y_ = 0);
	void dodaj(Punkt& p);//dodaje do siebie wspó³rzêdne punktu p (dodawanie wektorów w przestrzeni 2d )
	void dodaj(Punkt* p);
	void drukuj();// drukuje swoje wspó³rzêdne
	bool porownaj(Punkt& p);
};

Punkt::Punkt(Punkt& p): x(p.x), y(p.y) {}

Punkt::Punkt(float x_, float y_): x(x_), y(y_) {}

void Punkt::dodaj(Punkt& p)
{
	x += p.x;
	y += p.y;
}

void Punkt::dodaj(Punkt* p)
{
	x += p->x;
	y += p->y;
}

void Punkt::drukuj()
{
	std::cout << "Wspolrzedna x: " << x << ", wspolrzedna y: " << y << std::endl;
}

bool Punkt::porownaj(Punkt& p)
{
	if (x == p.x && y == p.y)
		return true;
	else
		return false;
}

class Tablica
{
	Punkt* w;
	int dl; // dlugoœæ Tablicy
public:
	Tablica(int dl = 0); // tworzy Tablice o zadanej d³ugoœci i wype³nia punktami (0,0)
	Tablica(Tablica& w_); //inicjalizacja za pomoc¹ Tablicy w_
	Tablica(float* x, float* y, int dl); // inicjalizacja tablicy punktów tablicami x -ów i y -ów
	~Tablica();
	void dodaj(Tablica& w_);// dodaje do siebie Tablice w_
	bool porownaj(Tablica& w);// porownnaie z Tablica w_;
	void drukuj();
};

Tablica::Tablica(int dl)
{
	Tablica::dl = dl;
	w = new Punkt[dl];
}

Tablica::Tablica(Tablica& w_)
{
	dl = w_.dl;
	w = new Punkt[dl];
	for (int i = 0; i < dl; i++)
		w[i] = Punkt(w_.w[i]);
}

Tablica::Tablica(float* x, float* y, int dl)
{
	Tablica::dl = dl;
	w = new Punkt[dl];
	for (int i = 0; i < dl; i++)
		w[i] = Punkt(x[i], y[i]);
}

Tablica::~Tablica()
{
	delete(w);
}

void Tablica::dodaj(Tablica& w_)
{
	Punkt* nowa_tablica = new Punkt[dl + w_.dl];
	for (int i = 0; i < dl; i++)
		nowa_tablica[i] = w[i];
	for (int i = 0; i < w_.dl; i++)
		nowa_tablica[dl + i] = w_.w[i];
	dl += w_.dl;
	delete(w);
	w = nowa_tablica;
}

bool Tablica::porownaj(Tablica& w_)
{
	if (dl != w_.dl)
		return false;
	else
	{
		int i = dl - 1;
		while (i > -1 && w[i].porownaj(w_.w[i]))
			i--;
		if (i == -1)
			return true;
		else
			return false;
	}
}

void Tablica::drukuj()
{
	for (int i = 0; i < dl; i++)
		w[i].drukuj();
}

int main()
{
	Punkt p1(3, 5);
	Punkt p2;
	p1.drukuj();
	p2.drukuj();
	p1.dodaj(p2);
	p1.drukuj();
	Punkt p3(12, 4);
	Punkt p4(p3);
	p3.drukuj();
	p4.drukuj();
	p3.dodaj(p4);
	p3.drukuj();
	Punkt p5(7, 1);
	Punkt* p6 = new Punkt(p5);
	p5.drukuj();
	p6->drukuj();
	p5.dodaj(p6);
	p5.drukuj();

	float tab_x[5] = { 5, 7, 1, 6, 3 };
	float tab_y[5] = { 1, 0, 3, 9, 7 };
	Tablica tab1(8);
	tab1.drukuj();
	Tablica tab2(tab_x, tab_y, 5);
	tab2.drukuj();
	Tablica tab3(tab2);
	tab3.drukuj();
	tab1.dodaj(tab2);
	tab1.drukuj();
	if (tab2.porownaj(tab3))
		std::cout << "Tablice sa takie same! ";
	return 0;
}