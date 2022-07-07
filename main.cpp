#include <iostream>
#include "wielomian.h"
#include <stdio.h>

/*
 0. Usun¹æ odstêpy,
 1. Okreœliæ stopieñ wielomianu,
 2. Przydzieliæ pamiêæ + wyzerowaæ,
 3. Analizowaæ jednomian po jednomianie,
 */

int main(int argc, const char* argv[]) {
	Wielomian e("x^2+x+2");
	Wielomian w("17.5+x^2-2x^3");
	
	e.Pokaz();
	w.Pokaz();

	w *= e;

	std::cout << std::endl << "WYNIK: ";
	w.Pokaz();
	return 0;
}

