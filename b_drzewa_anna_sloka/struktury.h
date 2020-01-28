#pragma once

#include <iostream>

using namespace std;

struct wezel;

struct potomkowie
{
	wezel* wezelPotomny;		//wskaŸnik na wêze³ potomny
	potomkowie* pNext;	//wskaŸnik na nastêpny element listy wskaŸników
};
struct klucz
{
	double wartosc;	//wartoœæ znajduj¹ca siê w kluczy
	klucz* pNext;	//wskaŸnik na nastêpny klucz
};
struct wezel
{
	klucz* pHeadKluczy;	//wskaŸnik na pocz¹tek listy kluczy w wêŸle
	potomkowie* pHeadPotom;	//wskaŸnik na pocz¹tek listy wskaŸników do wêz³ów potomnych
	int zapelnienie;	//zape³nienie wêz³a
	klucz* kluczPoprz;	//wskaŸnik na klucz rodzica, po którym znajduje siê wskaŸnik na obecny wêze³
	potomkowie* gdzieJestWsk;	//wskaŸnik na element listy wskaŸników do wêz³ów potomnych rodzica, w którym znajduje siê wsk na ten weze³
	wezel* rodzic;	//wskaŸnik na rodzica
};
struct listaFunkcji
{
	string funkcja;	//nazwa funkcji
	klucz* dane;	//pocz¹tek listy zawieraj¹cej liczby do dodania/usuniêcia
	string nazwa_pliku;	//nazwa pliku do zapisu przy funkcji graph lub print
	bool czy_plus;	//zmienna, która informuje, czy zapisaæ (0), czy nadpisaæ (1) do pliku
	listaFunkcji* pNext; //wskaŸnik na nastêpny element listy funkcji
};
struct searchResult	//struktura u¿ywana podczas wyznaczania wyniku wyszukiwania
{
	wezel* wezelMiejsca;	//wêze³ w którym siê znajduje miejsce do wskawienia nowego klucza
	klucz* kluczPoprz;	//wskaŸnik na klucz, po którym ma zostaæ wstawiony nowy klucz
	potomkowie* potomPoprz;	//wskaŸnik na element listy wskaŸników do potomków, po którym ma zostaæ wstawiony nowy klucz
};
struct podzial	//struktura u¿ywana podczas wyznaczania efektu podzia³u wêz³a
{
	double wartosc;	//wartoœæ, która ma zostaæ wstawiona do rodzica
	wezel* prawy;	//wskaŸnik do wêz³a znajduj¹cego sie po prawej stronie wstawianej wartoœci
	wezel* lewy;	// wskaŸnik do wêz³a znajduj¹cego siê po lewej stronie wstawianej wartoœci
};