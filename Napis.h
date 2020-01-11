////////////////////////////////////
//    LIBRARY BY Micha³ Ha³daœ    //
///////////////////////////////////
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Napis
{
private:
	char* znaki;
	unsigned dlugosc{};
	
	// KONSTRUKTOR KOPIUJ¥CY
	Napis(unsigned size)
	{
		dlugosc = size;
		znaki = new char[dlugosc + 1];
	}

public:
	//////////////////////////////////////
	//
	//     KONSTRUKTORY I DESTRUKTOR
	//
	//////////////////////////////////////

	//explicit 
	Napis(const char* n = "")
	{
		dlugosc = strlen(n);
		znaki = new char[dlugosc + 1];
		strcpy(znaki, n);
	}

	Napis(const Napis& wzor)
	{
		dlugosc = wzor.dlugosc;
		//znaki = wzor.znaki;
		znaki = new char[dlugosc + 1];
		strcpy(znaki, wzor.znaki);
	}

	~Napis()
	{
		delete[] znaki;
	}

	//////////////////////////////////////
	//
	//   OPERATORY = NADPISUJ¥CE TABLICE
	//
	//////////////////////////////////////
	Napis& operator = (const Napis& wzor)
	{
		if (this != &wzor) // obj = obj;
		{
			delete[] znaki;
			dlugosc = wzor.dlugosc;
			znaki = new char[dlugosc + 1];
			strcpy(znaki, wzor.znaki);
		}
		return *this;
	}

	Napis& operator = (const char* znaki)
	{
		delete[] this->znaki;
		dlugosc = strlen(znaki);
		this->znaki = new char[dlugosc + 1];
		//this->znaki = znaki;
		strcpy(this->znaki, znaki);
		return *this;
	}

	//////////////////////////////////////
	//
	//    OPERATORY + DODAJ¥CE TABLICE
	//
	//////////////////////////////////////
	Napis& operator + (const Napis& n2)const
	{
		unsigned size = this->dlugosc + n2.dlugosc;
		Napis suma{ size };

		strcpy(suma.znaki, znaki);
		strcat(suma.znaki, n2.znaki);
		return suma;
	}

	friend Napis operator + (const char* znaki, Napis& n2)
	{
		Napis dodane;
		dodane = n2 + znaki;
		return dodane;
	}

	//////////////////////////////////////
	//
	//  OPERATORY += DOPISUJ¥CE DO TABLICY
	//
	//////////////////////////////////////
	Napis& operator += (const Napis& n2)
	{
		// obj1 = obj1 + obj2

		dlugosc += n2.dlugosc;
		char* copy = new char[dlugosc+1];

		strcpy(copy, this->znaki);
		strcat(copy, n2.znaki);
		delete[] znaki;
		znaki = copy;

		return *this;
	}

	Napis& operator += (const char* znaki)
	{
		dlugosc += strlen(znaki);
		char* copy = new char[dlugosc + 1];

		strcpy(copy, this->znaki);
		strcat(copy, znaki);
		delete[] this->znaki;
		this->znaki = copy;

		return *this;
	}

	//////////////////////////////////////
	//
	//        WYJŒCIE I WEJŒCIE
	//
	//////////////////////////////////////
	friend std::ostream& operator << (std::ostream& out, const Napis& n)
	{
		return out << n.znaki;
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
		in.get(); // wyci¹gamy ze strumienia '\n'

		return in;
	}

	//Napis(Napis&& wzor) {}
	//Napis& operator=(Napis&& wzor) {}
};