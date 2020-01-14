////////////////////////////////////
//    LIBRARY BY Michal Haldas    //
////////////////////////////////////

/*
---------------------------------------------------------
		TO DO: 
	1. SPECJALNY NAMESPACE DAL FUNKCJI STATYCZNYCH
	2. FUNKCJE ZNAJDUJACE PODNAPIS W NAPISIE
---------------------------------------------------------
*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <sstream>

class Napis
{
private:
	char* napis;
	unsigned dlugosc{};
	
	// KONSTRUKTOR KOPIUJACY
	Napis(unsigned size)
	{
		dlugosc = size;
		napis = new char[dlugosc + 1];
	}

public:
	/////////////////////////////////////////
	//
	//       KONSTRUKTORY I DESTRUKTOR
	//
	/////////////////////////////////////////

	//explicit 
	Napis(const char* n = "")
	{
		dlugosc = strlen(n);
		napis = new char[dlugosc + 1];
		strcpy(napis, n);
	}

	Napis(const Napis& wzor)
	{
		dlugosc = wzor.dlugosc;
		//napis = wzor.napis;
		napis = new char[dlugosc + 1];
		strcpy(napis, wzor.napis);
	}

	~Napis()
	{
		delete[] napis;
	}

	/////////////////////////////////////////
	//
	//	NIEOKRESLONE FUNKCJE KLASY
	//
	/////////////////////////////////////////

	// Funkcja zwracajaca dlugosc napisu
	unsigned Dlugosc()
	{
		return dlugosc;
	}

	// Funkcja zastepujaca wybrany znak podanym napisem
	void WstawZamiastZnaku(const char* napis, int x = 0)
	{
		unsigned size = strlen(napis);
		dlugosc += size - 1;
		char* nowy = new char[dlugosc + 1];
		strncpy(nowy, this->napis, x);
		nowy[x] = 0;
		strcat(nowy, napis);
		strcat(nowy, this->napis + x + 1);
		delete[] this->napis;
		this->napis = nowy;
	}

	// Funkcja zastepujaca wybrany znak podanym napisem
	void WstawZamiastZnaku(const Napis& n, int x = 0)
	{
		WstawZamiastZnaku(n.napis, x);
	}

	// Funkcja zastepujaca wszytkie kolejne znaki podanym napisem
	void NadpiszNapis(const char* napis, unsigned x = 0)
	{
		unsigned size = strlen(napis);
		if (size > dlugosc - x)
		{
			dlugosc += abs(static_cast <int>(dlugosc - size - x));
			char* nowy = new char[dlugosc+1];
			strcpy(nowy, this->napis);
			delete[] this->napis;
			this->napis = nowy;
			for (unsigned i = x, j = 0; j < size+1; i++, j++)
				this->napis[i] = napis[j];
		}
		else
		{
			for (unsigned i = x, j = 0; j < size; i++, j++)
				this->napis[i] = napis[j];
		}
	}

	// Funkcja zastepujaca wszytkie kolejne znaki podanym napisem
	void NadpiszNapis(const Napis& n, unsigned x = 0)
	{
		NadpiszNapis(n.napis, x);
	}

	// Funkcja wstawiajaca tekst przed wybranym znakiem napisu
	void WstawPrzedZnakiem(const char* napis, unsigned x = 0)
	{
		unsigned dlugosc = strlen(napis);
		this->dlugosc += dlugosc;
		char* nowy = new char[this->dlugosc+1];
		strncpy(nowy, this->napis, x);
		nowy[x] = 0;
		strcat(nowy, napis);
		strcat(nowy, this->napis + x);
		delete[] this->napis;
		this->napis = nowy;
	}

	// Funkcja wstawiajaca tekst przed wybranym znakiem napisu
	void WstawPrzedZnakiem(const Napis& n, unsigned x = 0)
	{
		WstawPrzedZnakiem(n.napis, x);
	}


	// Funkcja zamieniajaca ze soba napisy (dziala na zasadzie swap)
	void ZamienNapisy(Napis& n1)
	{
		char* nowy;
		nowy = this->napis;
		this->napis = n1.napis;
		n1.napis = nowy;
	}

	// Statyczna funkcja zamieniajaca ze soba napisy (dziala na zasadzie swap)
	static void ZamienNapisy(Napis& n1, Napis& n2)
	{
		char* nowy;
		nowy = n1.napis;
		n1.napis = n2.napis;
		n2.napis = nowy;
	}

	/////////////////////////////////////////
	/////////// WIELKOSC ZNAKOW /////////////
	/////////////////////////////////////////

	// Funkcja zamieniajaca konkretny znak napisu na maly
	void ZamienNaMaleZnak(unsigned x = 0)
	{
		if (napis[x] > 64 &&  napis[x] < 93)
			napis[x] = napis[x] + 32;
	}

	// Funkcja zamieniajaca konkretny znak napisu na duzy
	void ZamienNaDuzeZnak(unsigned x = 0)
	{
		if (napis[x] > 96 && napis[x] < 123)
			napis[x] = napis[x] - 32;
	}

	// Funkcja zamieniajaca caly napis na maly
	void ZamienNaMaleWszystko()
	{
		for (unsigned i = 0; i < dlugosc; i++)
		{
			if (napis[i] > 64 && napis[i] < 93)
				napis[i] = napis[i] + 32;
		}
	}

	// Funkcja zamieniajaca caly napis na duzy
	void ZamienNaDuzeWszystko()
	{
		for (unsigned i = 0; i < dlugosc; i++)
		{
			if (napis[i] > 96 && napis[i] < 123)
				napis[i] = napis[i] - 32;
		}
	}

	/////////////////////////////////////////
	//
	//	FUNKCJE KONWERTUJACE NAPIS
	//
	/////////////////////////////////////////

	//Funkcja konwertujaca dowolny typ zmiennej na napis
	template <typename T>
	static Napis KonwertujNaNapis(T zmienna)
	{
		//Napis n1;
		std::stringstream os;
		os << zmienna;
		Napis n1(os.str().c_str());
		return n1;
	}

	// to uczucie kiedy funkcja atof() assci to float konwertuje na double xd

	/////////////////////////////////////////
	////////////// STATYCZNE ////////////////
	/////////////////////////////////////////

	// Statyczna funkcja konwertujaca wybrany napis na zmienna typu double
	static double NapisNaDouble(const Napis& n1) { return atof(n1.napis); }
	// Statyczna funkcja konwertujaca wybrany napis na zmienna typu float
	static float NapisNaFloat(const Napis& n1) { return static_cast<float>(atof(n1.napis)); }
	// Statyczna funkcja konwertujaca wybrany napis na zmienna typu int
	static int NapisNaInt(const Napis& n1) { return atoi(n1.napis); }
	// Statyczna funkcja konwertujaca wybrany napis na zmienna typu unsigned
	static unsigned NapisNaUnsigned(const Napis& n1) { return static_cast<unsigned>(atoi(n1.napis)); }

	/////////////////////////////////////////
	///////////// OBIEKT KLASY //////////////
	/////////////////////////////////////////

	// Funkcja konwertujaca napis na zmienna typu double
	double NapisNaDouble() { return atof(this->napis); }
	// Funkcja konwertujaca napis na zmienna typu float
	float NapisNaFloat() { return static_cast<float>(atof(this->napis)); }
	// Funkcja konwertujaca napis na zmienna typu int
	int NapisNaInt() { return atoi(this->napis); }
	// Funkcja konwertujaca napis na zmienna typu unsigned
	unsigned NapisNaUnsigned() { return static_cast<unsigned>(atoi(this->napis)); }

	/*

	/////////////////////////////////////////
	//
	//       FUNKCJE WYSZYKUJACE NAPISY
	//
	/////////////////////////////////////////

		unsigned ZnajdzNapis() {}
		unsigned ZnajdzZnak() {}
		Napis& ZwrocPodnapis(unsigned x, unsigned y) {}  - zwraca napis z przedzialu
		void UsunPodnapis(unsigned x, unsigned y) - wyszukuje podnapis i go usuwa

	*/

	/////////////////////////////////////////
	//
	//	OPERATORY ==, != i FUNKCJE
	//	SPRAWDZAJACE ROWNOSC TABLIC 	
	//
	/////////////////////////////////////////

	friend bool operator == (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) == 0) return true;
		else return false;
	}

	friend bool operator != (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) != 0) return true;
		else return false;
	}

	// Funkcja sprawdzajaca czy napisy sa takie same
	bool SprawdzRownosc(const Napis& n1)
	{
		if (strcmp(n1.napis, napis) == 0) return true;
		else return false;
	}

	// Funkcja sprawdzajaca czy napisy sa takie same
	bool SprawdzRownosc(const char* napis)
	{
		if (strcmp(this->napis, napis) == 0) return true;
		else return false;
	}

	// Statyczna funkcja sprawdzajaca czy napisy sa takie same
	static bool SprawdzRownosc(const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) == 0) return true;
		else return false;
	}

	/////////////////////////////////////////
	//
	//	OPERATORY >, >=, <, <= i FUNKCJE
	//	POROWNOJACE TABLICE	
	//
	/////////////////////////////////////////

	friend bool operator > (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) < 0) return true;
		else return false;
	}

	friend bool operator >= (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) <= 0) return true;
		else return false;
	}

	friend bool operator < (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) > 0) return true;
		else return false;
	}

	friend bool operator <= (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) >= 0) return true;
		else return false;
	}

	// Funkcja zwracajaca "wiekszy" napis
	// (ex. "ala" > "ola")
	Napis& ZwrocWiekszy(Napis& n1)
	{
		if (strcmp(this->napis, n1.napis) < 0) return *this;
		else return n1;
	}

	// Funkcja zwracajaca "mniejszy" napis
	// (ex. "ala" > "ola")
	Napis& ZwrocMniejszy(Napis& n1)
	{
		if (strcmp(this->napis, n1.napis) > 0) return *this;
		else return n1;
	}

	// Statyczna funkcja zwracajaca "wiekszy" napis
	// (ex. "ala" > "ola")
	static Napis& ZwrocWiekszy(Napis& n1, Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) < 0) return n1;
		else return n2;
	}

	// Statyczna funkcja zwracajaca "mniejszy" napis
	// (ex. "ala" > "ola")
	static Napis& ZwrocMniejszy(Napis& n1, Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis) > 0) return n1;
		else return n2;
	}

	/////////////////////////////////////////
	//
	//    OPERATORY = NADPISUJACE TABLICE
	//
	/////////////////////////////////////////

	Napis& operator = (const Napis& wzor)
	{
		if (this != &wzor) // obj = obj;
		{
			delete[] napis;
			dlugosc = wzor.dlugosc;
			napis = new char[dlugosc + 1];
			strcpy(napis, wzor.napis);
		}
		return *this;
	}

	Napis& operator = (const char* napis)
	{
		delete[] this->napis;
		dlugosc = strlen(napis);
		this->napis = new char[dlugosc + 1];
		//this->napis = napis;
		strcpy(this->napis, napis);
		return *this;
	}

	/////////////////////////////////////////
	//
	//     OPERATORY + DODAJACE TABLICE
	//
	/////////////////////////////////////////

	Napis operator + (const Napis& n2)const
	{
		unsigned size = this->dlugosc + n2.dlugosc;
		Napis suma(size);

		strcpy(suma.napis, napis);
		strcat(suma.napis, n2.napis);
		return suma;
	}

	friend Napis operator + (const char* napis, Napis& n2)
	{
		Napis dodane;
		dodane = n2 + napis;
		return dodane;
	}

	/////////////////////////////////////////
	//
	//   OPERATORY += DOPISUJACE DO TABLICY
	//
	/////////////////////////////////////////

	Napis& operator += (const Napis& n2)
	{
		// obj1 = obj1 + obj2

		dlugosc += n2.dlugosc;
		char* copy = new char[dlugosc+1];

		strcpy(copy, this->napis);
		strcat(copy, n2.napis);
		delete[] napis;
		napis = copy;

		return *this;
	}

	Napis& operator += (const char* napis)
	{
		dlugosc += strlen(napis);
		char* copy = new char[dlugosc + 1];

		strcpy(copy, this->napis);
		strcat(copy, napis);
		delete[] this->napis;
		this->napis = copy;

		return *this;
	}

	/////////////////////////////////////////
	//
	//      OPERATORY WYJSCIA i WEJSCIA
	//
	/////////////////////////////////////////

	friend std::ostream& operator << (std::ostream& out, const Napis& n)
	{
		return out << n.napis;
	}

	friend std::istream& operator >> (std::istream& in, Napis& n)
	{
		char buff[80];
		in >> buff[0];
		in.get(buff + 1, 79);
		n = buff;
		while (in.peek() != '\n' && in)
		{
			in.get(buff, 80);
			n += buff;
		}
		in.get(); // wyciagniecie ze strumienia '\n'

		return in;
	}

	/////////////////////////////////////////
	//
	//	  OPERATORY PRZESUWAJACE
	//
	/////////////////////////////////////////		

	Napis(Napis&& wzor) noexcept
	{
		napis = wzor.napis;
		dlugosc = wzor.dlugosc;
		wzor.napis = nullptr;
		wzor.dlugosc = 0;
	}

	Napis& operator = (Napis&& wzor) noexcept
	{
		napis = wzor.napis;
		dlugosc = wzor.dlugosc;
		wzor.napis = nullptr;
		wzor.dlugosc = 0;
		return *this;
	}

	/////////////////////////////////////////
	//
	//   OPERATOR [] i FUNKCJA ODWOLUJACA
	//   SIE DO DANEGO MIEJSCA W TABLICY
	//
	/////////////////////////////////////////

	char& operator [] (unsigned x)
	{
		if (x < dlugosc - 1)
			return napis[x];
		else throw 1;
	}

	// Funkcja zwracajaca znak z danego indexu napisu
	char& Znak(unsigned x)
	{
		if (x < dlugosc - 1)
			return napis[x];
		else throw 1;
	}
};
