////////////////////////////////////
//    LIBRARY BY Michal Haldas    //
////////////////////////////////////

/*
////////////////////////////////////
	     TO DO:
------------------------------------
1. Funkcja wstaw przed znakiem
2. Operatory/funkcje typu >, <

////////////////////////////////////
*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

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
	void WstawZaZnak(const char* napis, int x = 0)
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
	void WstawZaZnak(const Napis& n, int x = 0)
	{
		WstawZaZnak(n.napis, x);
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
	void WstawPrzedZnakiem() {};

	/////////////////////////////////////////
	//
	//   OPERATORY i FUNKCJE POROWNUJACE
	//
	/////////////////////////////////////////
	friend bool operator == (const Napis& n1, const Napis& n2)
	{
		if (!strcmp(n1.napis, n2.napis)) return true;
		else return false;
	}

	friend bool operator != (const Napis& n1, const Napis& n2)
	{
		if (strcmp(n1.napis, n2.napis)) return true;
		else return false;
	}

	// Funkcja sprawdzajaca czy napisy sa takie same
	bool Porównaj(const Napis& n1)
	{
		if (!strcmp(n1.napis, napis)) return true;
		else return false;
	}

	// Funkcja sprawdzajaca czy napisy sa takie same
	bool Porównaj(const char* napis)
	{
		if (!strcmp(this->napis, napis)) return true;
		else return false;
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
	//		 OPERATORY PRZESUWAJACE
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

	char& at(unsigned x)
	{
		if (x < dlugosc - 1)
			return napis[x];
		else throw 1;
	}
};
