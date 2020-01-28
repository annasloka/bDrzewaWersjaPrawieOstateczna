#pragma once

#include <iostream>

using namespace std;

struct wezel;

struct potomkowie
{
	wezel* wezelPotomny;		//wska�nik na w�ze� potomny
	potomkowie* pNext;	//wska�nik na nast�pny element listy wska�nik�w
};
struct klucz
{
	double wartosc;	//warto�� znajduj�ca si� w kluczy
	klucz* pNext;	//wska�nik na nast�pny klucz
};
struct wezel
{
	klucz* pHeadKluczy;	//wska�nik na pocz�tek listy kluczy w w�le
	potomkowie* pHeadPotom;	//wska�nik na pocz�tek listy wska�nik�w do w�z��w potomnych
	int zapelnienie;	//zape�nienie w�z�a
	klucz* kluczPoprz;	//wska�nik na klucz rodzica, po kt�rym znajduje si� wska�nik na obecny w�ze�
	potomkowie* gdzieJestWsk;	//wska�nik na element listy wska�nik�w do w�z��w potomnych rodzica, w kt�rym znajduje si� wsk na ten weze�
	wezel* rodzic;	//wska�nik na rodzica
};
struct listaFunkcji
{
	string funkcja;	//nazwa funkcji
	klucz* dane;	//pocz�tek listy zawieraj�cej liczby do dodania/usuni�cia
	string nazwa_pliku;	//nazwa pliku do zapisu przy funkcji graph lub print
	bool czy_plus;	//zmienna, kt�ra informuje, czy zapisa� (0), czy nadpisa� (1) do pliku
	listaFunkcji* pNext; //wska�nik na nast�pny element listy funkcji
};
struct searchResult	//struktura u�ywana podczas wyznaczania wyniku wyszukiwania
{
	wezel* wezelMiejsca;	//w�ze� w kt�rym si� znajduje miejsce do wskawienia nowego klucza
	klucz* kluczPoprz;	//wska�nik na klucz, po kt�rym ma zosta� wstawiony nowy klucz
	potomkowie* potomPoprz;	//wska�nik na element listy wska�nik�w do potomk�w, po kt�rym ma zosta� wstawiony nowy klucz
};
struct podzial	//struktura u�ywana podczas wyznaczania efektu podzia�u w�z�a
{
	double wartosc;	//warto��, kt�ra ma zosta� wstawiona do rodzica
	wezel* prawy;	//wska�nik do w�z�a znajduj�cego sie po prawej stronie wstawianej warto�ci
	wezel* lewy;	// wska�nik do w�z�a znajduj�cego si� po lewej stronie wstawianej warto�ci
};