#include <iostream>
#include <fstream>
#include <string>

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
	Punkt& operator+=(Punkt& p);
	Punkt& operator=(const Punkt& p);
	bool operator==(const Punkt& p);
	Punkt operator+(const Punkt& p);
	friend std::ostream& operator<<(std::ostream& s, const Punkt& p);
	std::string pobierz_dane();
};

Punkt::Punkt(Punkt& p) : x(p.x), y(p.y) {}

Punkt::Punkt(float x_, float y_) : x(x_), y(y_) {}

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

std::string Punkt::pobierz_dane()
{
	return "Wspolrzedna x: " + std::to_string(x) + " Wspolrzedna y: " + std::to_string(y);
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
	void dodaj(const Tablica& w_);// dodaje do siebie Tablice w_
	bool porownaj(const Tablica& w);// porownnaie z Tablica w_;
	void drukuj();
	Tablica& operator=(const Tablica& tab);
	bool operator==(const Tablica& tab);
	friend std::ostream& operator<<(std::ostream& s, const Tablica& tab);
	Tablica& operator+=(const Tablica& tab);
	Punkt& operator[](int index);
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
		w[i] = w_.w[i];
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

void Tablica::dodaj(const Tablica& w_)
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

bool Tablica::porownaj(const Tablica& w_)
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

Punkt& Punkt::operator+=(Punkt& p)
{
	Punkt::dodaj(p);
	return *this;
}

Punkt& Punkt::operator=(const Punkt& p)
{
	x = p.x;
	y = p.y;
	return *this;
}

bool Punkt::operator==(const Punkt& p)
{
	if (x == p.x && y == p.y)
		return true;
	else
		return false;
}

Punkt Punkt::operator+(const Punkt& p)
{
	Punkt tmp;
	tmp.x = x + p.x;
	tmp.y = y + p.y;
	return tmp;
}

std::ostream& operator<<(std::ostream& s, const Punkt& p)
{
	s << p.x << " " << p.y;
	return s;
}

Tablica& Tablica::operator=(const Tablica& tab)
{
	if (this == &tab)
		return *this;
	dl = tab.dl;
	w = new Punkt[dl];
	for (int i = 0; i < dl; i++)
		w[i] = tab.w[i];
}

bool Tablica::operator==(const Tablica& tab)
{
	return this->porownaj(tab);
}

std::ostream& operator<<(std::ostream& s, const Tablica& tab)
{
	for (int i = 0; i < tab.dl; i++)
		s << tab.w[i].pobierz_dane() << std::endl;
	return s;
}

Tablica& Tablica::operator+=(const Tablica& tab)
{
	dodaj(tab);
	return *this;
}

Punkt& Tablica::operator[](int index) 
{
	return w[index];
}

int main()
{
	Punkt a(3, 4);
	Punkt b(5, 2);
	Punkt c(2, 6);
	a += b += c;
	a.drukuj();
	a = b;
	a.drukuj();
	a = Punkt(8, 5);
	a.drukuj();
	if (a == Punkt(8, 5))
		std::cout << "HEHUEHEU\n";
	a = b + c;
	a.drukuj();
	std::cout << a << std::endl;
	float iksy[5] = { 5, 7, 1, 4, 2 };
	float igreki[5] = { 3, 7, 2, 9, 0 };
	Tablica tab1;
	Tablica tab2(iksy, igreki, 5);
	tab1 = tab2;
	tab2.drukuj();
	Tablica tab3(5);
	if (tab1 == tab2)
		std::cout << "Jest git\n";
	if (tab1 == tab3)
		std::cout << "To nie powinno sie wyswietlic\n";
	else
		std::cout << "A to tak\n";
	tab1 += tab3;
	std::cout << tab1;
	std::cout << tab1[4];
}