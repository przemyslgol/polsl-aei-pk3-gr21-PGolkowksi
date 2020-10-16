#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

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
	bool porownaj(const Punkt& p) const; 
	Punkt& operator+=(Punkt& p);
	Punkt& operator=(const Punkt& p);
	bool operator==(const Punkt& p);
	Punkt operator+(const Punkt& p);
	friend std::ostream& operator<<(std::ostream& s, const Punkt& p);
	std::string pobierz_dane();
	float getX() const;
	float getY() const;
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

bool Punkt::porownaj(const Punkt& p) const
{
	return (x == p.x && y == p.y);
}

std::string Punkt::pobierz_dane()
{
	return "Wspolrzedna x: " + std::to_string(x) + " Wspolrzedna y: " + std::to_string(y);
}

float Punkt::getX() const
{
	return x;
}

float Punkt::getY() const
{
	return y;
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
	return (x == p.x && y == p.y);
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

class Wektor : public Punkt
{
	float dlugosc;
	float kierunek;
public:
	Wektor(float x_ = 0, float y_ = 0);
	Wektor(const Wektor& w);
	void dodaj(Punkt& p);
	void dodaj(Punkt* p);
	void drukuj();
	bool porownaj(const Punkt& p) const;
	bool operator==(const Punkt& p) const;
	float getDlugosc();
};

Wektor::Wektor(float x_, float y_) : Punkt(x_, y_), dlugosc(sqrt(x_ * x_ + y_ * y_)), kierunek(atan(y_ / x_)) {}

Wektor::Wektor(const Wektor& w) : Punkt(w.getX(), w.getY()), dlugosc(w.dlugosc), kierunek(w.kierunek) {}

void Wektor::dodaj(Punkt& p)
{
	Punkt::dodaj(p);
	dlugosc = sqrt(getX() * getX() + getY() * getY());
	kierunek = atan(getY() / getX());
}

void Wektor::dodaj(Punkt* p)
{
	Punkt::dodaj(p);
	dlugosc = sqrt(getX() * getX() + getY() * getY());
	kierunek = atan(getY() / getX());
}

void Wektor::drukuj()
{
	Punkt::drukuj();
	std::cout << "Dlugosc: " << dlugosc << ", Kierunek: " << kierunek << std::endl;
}

bool Wektor::porownaj(const Punkt& p) const
{
	return Punkt::porownaj(p);
}

bool Wektor::operator==(const Punkt& p) const
{
	return Punkt::porownaj(p);
}

float Wektor::getDlugosc()
{
	return dlugosc;
}

class TablicaWektorow
{
protected:
	int dl;
	Wektor* w;
public:
	TablicaWektorow(int dl_ = 0);
	TablicaWektorow(float* x, float* y, int dl_);
	~TablicaWektorow();
	void drukuj();
};

TablicaWektorow::TablicaWektorow(int dl_)
{
	dl = dl_;
	w = new Wektor[dl];
}

TablicaWektorow::TablicaWektorow(float* x, float* y, int dl_)
{
	dl = dl_;
	w = new Wektor[dl];
	for (int i = 0; i < dl; i++)
		w[i] = Wektor(x[i], y[i]);
}

TablicaWektorow::~TablicaWektorow()
{
	delete[] w;
}

void TablicaWektorow::drukuj()
{
	for (int i = 0; i < dl; i++)
		w[i].drukuj();
	std::cout << std::endl;
}

class TabWektorowSort : public TablicaWektorow
{
public:
	TabWektorowSort(int dl_);
	TabWektorowSort(float* x, float* y, int dl_);
	void sortuj(int dl_);
	void wstaw(Wektor& wek);
};

TabWektorowSort::TabWektorowSort(int dl_) : TablicaWektorow(dl_) 
{
	sortuj(dl_);
}

TabWektorowSort::TabWektorowSort(float* x, float* y, int dl_) : TablicaWektorow(x, y, dl_) 
{
	sortuj(dl_);
}

void TabWektorowSort::sortuj(int dl_)
{
	for (int i = 0; i < dl_ - 1; i++)
	{
		int indexMax = 0;
		for (int j = 1; j < dl_ - i; j++)
		{
			if (w[j].getDlugosc() > w[indexMax].getDlugosc())
				indexMax = j;
		}
		Wektor temp = w[indexMax];
		w[indexMax] = w[dl_ - (i + 1)];
		w[dl_ - (i + 1)] = temp;
	}
}

void TabWektorowSort::wstaw(Wektor& wek)
{
	Wektor* nowaTablica = new Wektor[dl + 1];
	int i = 0;
	while (i < dl && wek.getDlugosc() > w[i].getDlugosc())
	{
		nowaTablica[i] = w[i];
		i++;
	}
	nowaTablica[i++] = wek;
	dl++;
	for(;i < dl; i++)
		nowaTablica[i] = w[i-1];
	delete[] w;
	w = nowaTablica;
}

int main()
{
	Wektor a(5, 2);
	Wektor b(a);
	Punkt punkcik(4, 8);
	b.dodaj(punkcik);
	b.drukuj();
	std::cout << b.porownaj(punkcik) << std::endl;
	std::cout << punkcik.porownaj(Punkt(4, 8)) << std::endl;
	std::cout << (a == Punkt(5, 2)) << std::endl;
	float x[5] = { 7, 2, 5, 19, 15 };
	float y[5] = { 8, 1, 2, 8, 21 };
	TabWektorowSort tabSort(x, y, 5);
	tabSort.drukuj();
	tabSort.wstaw(b);
	tabSort.drukuj();
	tabSort.wstaw(a);
	tabSort.drukuj();
}