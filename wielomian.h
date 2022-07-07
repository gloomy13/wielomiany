#ifndef wielomian_h
#define wielomian_h

class Wielomian{
private:
	double* wsp;
	unsigned st;
	void alokuj();

public:
	Wielomian();
	Wielomian(const Wielomian& w);
	Wielomian(const char* napis);
	Wielomian(const double* tab, int size);
	~Wielomian();
	void Analizuj(const char* napis);
	char* czytajJednomian(char* napis);
	void Pokaz();
	double operator[](int i) {
		return wsp[i];
	}

	Wielomian& operator+=(const Wielomian& w);
	Wielomian& operator+(const Wielomian& w);
	Wielomian& operator-=(const Wielomian& w);
	Wielomian& operator-(const Wielomian& w);
	Wielomian& operator*=(const Wielomian& w);
	Wielomian& operator*(const Wielomian& w);

	Wielomian Pochodna();
};

char* usunOdstepy(const char* napis);
unsigned okreslStopien(const char* napis);
void czytajJednomiany(Wielomian& w, char* napis);

#endif /* wielomian_h */
