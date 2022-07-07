#include <iostream>
#include "wielomian.h"

using namespace std;

Wielomian::~Wielomian() {
	delete[] wsp;
}

Wielomian::Wielomian(const Wielomian& w) {
	this->st = w.st;
	this->alokuj();
	for (int i = 0; i <= w.st; i++)
		this->wsp[i] = w.wsp[i];
}

Wielomian::Wielomian() {
	st = 0;
	alokuj();
}

Wielomian::Wielomian(const char* napis) {
	wsp = 0;
	Analizuj(napis);
}

Wielomian::Wielomian(const double* tab, int size) {
	st = size - 1;
	alokuj();
	for (int i = 0; i <= st; i++)
		wsp[i] = tab[i];
}

char* Wielomian::czytajJednomian(char* napis)
{
	char* endptr;
	double wspolczynnik;
	int st, znak = 1;

	if (*napis == '-')
	{
		znak = -1;
		napis++;
	}
	else
		if (*napis == '+') napis++;

	if (*napis == 'x')
		wspolczynnik = 1;
	else
	{
		wspolczynnik = strtod(napis, &endptr);
		napis = endptr;
	}

	if (*napis != 'x')
		st = 0;
	else
		if (*++napis != '^')
			st = 1;
		else
		{
			st = strtol(++napis, &endptr, 10);
			napis = endptr;
		}

	wsp[st] += (znak * wspolczynnik);
	return napis;
}

void czytajJednomiany(Wielomian& w, char* napis) {
	while (*napis)
		napis = w.czytajJednomian(napis);
}
char* usunOdstepy(const char* napis) {
	char* nowyNapis = new char[strlen(napis) + 1];
	char* praca = nowyNapis;
	while (*napis) {
		if (*napis != ' ' && *napis != '\t')
			*praca++ = *napis;
		napis++;
	}
	*praca = 0;
	return nowyNapis;
}
unsigned okreslStopien(const char* napis) {
	unsigned st = 0;
	while (*napis) {
		if (*napis++ == 'x') {
			if (st < 1)
				st = 1;
			if (*napis++ == '^') {
				char* endptr;
				long stop = strtol(napis, &endptr, 10);
				napis = endptr;
				if (st < stop)
					st = (unsigned)stop;
			}
		}
	}
	return st;
}

void Wielomian::alokuj() {
	wsp = new double[st + 1];
	for (int i = 0; i <= st; i++)
		wsp[i] = 0;
}

void Wielomian::Analizuj(const char* napis) {
	char* nowyNapis = usunOdstepy(napis);
	st = okreslStopien(nowyNapis);
	alokuj();
	czytajJednomiany(*this, nowyNapis);
}


void Wielomian::Pokaz() {
	for (int i = st; i >= 0; i--) {
		if (i == 0) {
			if (wsp[i] > 0)
				cout << "+" << wsp[i];
			if (wsp[i] < 0)
				cout << wsp[i];
		}
		if (i == 1) {
			if (wsp[i] > 0)
				cout << "+" << wsp[i] << "x";
			if (wsp[i] < 0)
				cout << wsp[i] << "x";
		}
		if (i > 1) {
			if (wsp[i] > 0)
				cout << "+" << wsp[i] << "x^" << i;
			if (wsp[i] < 0)
				cout << wsp[i] << "x^" << i;
		}
	}
	cout << endl;
}

Wielomian& Wielomian::operator+=(const Wielomian& w) {
	if (this->st >= w.st) {
		for (int i = 0; i <= (w.st); i++) {
			this->wsp[i] += w.wsp[i];
		}
	}
	else {
		Wielomian pom(*this);
		this->st = w.st;
		this->alokuj();
		for (int i = 0; i <= (this->st); i++) {
			this->wsp[i] = pom.wsp[i] + w.wsp[i];
		}
		for (int i = this->st + 1; i <= w.st; i++)
			this->wsp[i] = w.wsp[i];
	}
	return *this;
}

Wielomian& Wielomian::operator+(const Wielomian& w) {
	Wielomian wynik(*this);
	wynik += w;
	return wynik;
}

Wielomian& Wielomian::operator-=(const Wielomian& w) {
	if (this->st > w.st) {
		for (int i = 0; i <= (w.st); i++) {
			this->wsp[i] -= w.wsp[i];
		}
	}
	else {
		Wielomian pom(*this);
		this->st = w.st;
		this->alokuj();
		for (int i = 0; i <= (this->st); i++) {
			this->wsp[i] = pom.wsp[i] - w.wsp[i];
		}
		for (int i = this->st + 1; i <= w.st; i++)
			this->wsp[i] = -w.wsp[i];
	}
	return *this;
}

Wielomian& Wielomian::operator-(const Wielomian& w) {
	Wielomian wynik(*this);
	wynik += w;
	return wynik;
}

Wielomian& Wielomian::operator*=(const Wielomian& w) {
	Wielomian pom(*this);
	this->st += w.st;
	this->alokuj();
	for (int i = 0; i <= pom.st; i++)
		for (int j = 0; j <= w.st; j++)
			this->wsp[i + j] += pom.wsp[i] * w.wsp[j];
	return *this;
}

Wielomian& Wielomian::operator*(const Wielomian& w) {
	Wielomian wynik(*this);
	wynik *= w;
	return wynik;
}

Wielomian Wielomian::Pochodna() {
	Wielomian wynik;
	wynik.st = st - 1;
	wynik.alokuj();
	for (int i = st; i > 0; i--)
		wynik.wsp[i - 1] = wsp[i] * i;
	return wynik;
}