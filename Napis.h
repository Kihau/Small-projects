#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Napis
{
private:
	char* chars;
	unsigned chars_size{};

	Napis(unsigned size)
	{
		chars_size = size;
		chars = new char[chars_size + 1];
	}

public:
	//explicit 
	Napis(const char* n = "")
	{
		chars_size = strlen(n);
		chars = new char[chars_size + 1];
		strcpy(chars, n);
	}

	~Napis()
	{
		delete[] chars;
	}


	Napis(const Napis& wzor)
	{
		chars_size = wzor.chars_size;
		//chars = wzor.chars;
		chars = new char[chars_size + 1];
		strcpy(chars, wzor.chars);
	}

	Napis& operator=(const Napis& wzor)
	{
		if (this != &wzor) //a=a;
		{
			delete[] chars;
			chars_size = wzor.chars_size;
			chars = new char[chars_size + 1];
			strcpy(chars, wzor.chars);
		}
		return *this;
	}

	// Appending char array with a new one
	Napis& operator = (const char* chars)
	{
		delete[] this->chars;
		chars_size = strlen(chars);
		this->chars = new char[chars_size + 1];
		//this->chars = chars;
		strcpy(this->chars, chars);
		return *this;
	}

	Napis operator + (const Napis& n2)const
	{
		unsigned size = this->chars_size + n2.chars_size;
		Napis suma{ size };

		strcpy(suma.chars, chars);
		strcat(suma.chars, n2.chars);
		return suma;
	}

	friend std::ostream& operator<<(std::ostream& wy, const Napis& n)
	{
		return wy << n.chars;
	}

	// Wprowadzanie

	//Napis(Napis&& wzor) {}
	//Napis& operator=(Napis&& wzor) {}
};

